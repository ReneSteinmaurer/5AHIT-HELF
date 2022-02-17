#include<SPI.h>

#define PIN_LED       4
#define PIN_SWITCH    2
#define PIN_LDR       A1

#define LED_OFF     0x01
#define LED_ON      0x02
#define READ_SWITCH 0x03
#define READ_LDR    0x04
#define WRITE_LDR   0x05
#define NO_ACTION   0xFF

#define READ_SWITCH_DELAY 2000
#define WRITE_LDR_DELAY   2500
#define READ_LDR_DELAY    2000

#define COMM_WRITE_READ_DELAY 1

unsigned long now = 0;
unsigned long lastWrite = 1500L;

void setup(void) {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);

  setupSpiComm();

  printInfo();
}

void loop(void) {
  now = millis();
  
  if(now - WRITE_LDR_DELAY > lastWrite){
    int sensValue = analogRead(PIN_LDR);
    writeSPILDR(sensValue);
    lastWrite = now;
 }
}

void readSlaveSwitch() {
  static unsigned long prevReadSwitchCmd = 2000L;
  byte received = 0;
  unsigned long now = millis();

  if (now - READ_SWITCH_DELAY > prevReadSwitchCmd) {
    prevReadSwitchCmd = now;
    requestSpiByte(READ_SWITCH, &received);
    doCommand(received);
  }
}

void readSlaveLDR() {
  static unsigned long prevReadLDRCmd = 2000L;
  byte received[2];
  unsigned int ldrValue;
  unsigned long now = millis();

  if (now - READ_LDR_DELAY > prevReadLDRCmd) {
    prevReadLDRCmd = now;
    requestSpiInt(READ_LDR, &ldrValue);
    Serial.println(ldrValue);
  }
}

void doSwitch() {
  static boolean prevSwitchState = false;
  boolean switchState = digitalRead(PIN_SWITCH);
  if (switchState != prevSwitchState) {
    prevSwitchState = switchState;
    writeSpiByte(switchState ? LED_ON : LED_OFF);
  }
}

void doCommand(byte received) {
  static boolean prevLedState = false;
  
  switch (received) {
    case LED_ON:
      if (!prevLedState) {
        digitalWrite(PIN_LED, HIGH);
        Serial.println(F("Master: LED on"));
        prevLedState = true;
      }
      break;
    case LED_OFF:
      if (prevLedState) {
        digitalWrite(PIN_LED, LOW);
        Serial.println(F("Master: LED off"));
        prevLedState = false;
      }
      break;
    case NO_ACTION:
          Serial.print(F("Master: COMMAND NO ACTION executed!"));
      break;
    default:
      Serial.print(F("Master: undefined command 0x"));
      Serial.println(received, HEX);
  }
}

void printInfo() {
  Serial.println(F("SPI communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: MOSI-MOSI, MISO-MISO, SCK-SCK, SS-SS (pin 10 on UNO)"));
  Serial.println(F("Master eagerly reads own tactile switch and sends changes to slave (LED_ON, LED_OFF)"));
  Serial.println(F("       requests tactile switch of slave every second (READ_SWITCH)"));
  Serial.println(F("       requests LDR value of slave every 2 and a half second (READ_LDR)"));
  Serial.println(F("       fetches values from slave (>= 1 byte) by sending according number of NO_ACTION commands"));
  Serial.println(F("       builds result from multiple byte responses (MSB first) (LDR)"));
  Serial.println(F("       switches own LED according to slaves answer (LED_ON, LED_OFF)"));
  Serial.println(F("       prints LDR value received from slave (2 bytes, MSB followed by LSB) onto Serial"));
}

void setupSpiComm() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS, HIGH);
}

void writeSpiByte(byte value) {
  digitalWrite(SS, LOW);
  SPI.transfer(value);
  digitalWrite(SS, HIGH);
}

void requestSpiByte(byte command, byte *value) {
  digitalWrite(SS, LOW);
  SPI.transfer(command);
  digitalWrite(SS, HIGH);
  delay(1);
  digitalWrite(SS, LOW);
  *value = SPI.transfer(NO_ACTION);
  digitalWrite(SS, HIGH);
}

void requestSpiInt(byte command, int *value) {
  byte received[2];
  digitalWrite(SS, LOW);
  SPI.transfer(command);
  digitalWrite(SS, HIGH);
  delay(COMM_WRITE_READ_DELAY);
  digitalWrite(SS, LOW);
  received[0] = SPI.transfer(NO_ACTION);
  delay(COMM_WRITE_READ_DELAY);
  received[1] = SPI.transfer(NO_ACTION);
  digitalWrite(SS, HIGH);
  *value = received[0] * 256 + received[1];
  Serial.print(F("Master: LDR: "));
  Serial.print('('); Serial.print(received[0]);
  Serial.print(' '); Serial.print(received[1]);
  Serial.print(") ");
}

void writeSPILDR(int value) {
  Serial.print("LDR beim Master:  " );
  
  Serial.println(value);
  writeSpiByte(WRITE_LDR);
  writeSpiByte((value >> 8) & 0xFF);
  writeSpiByte((value & 0xFF));
}
