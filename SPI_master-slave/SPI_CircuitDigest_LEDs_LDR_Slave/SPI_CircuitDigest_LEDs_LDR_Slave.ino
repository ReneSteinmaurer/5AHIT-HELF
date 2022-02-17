//https://circuitdigest.com/microcontroller-projects/arduino-spi-communication-tutorial
//SPI SLAVE (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO
//CIRCUIT DIGEST
//Pramoth.T
//Amended: Ferdinand Hell (HTL Wels, 2020-02-16)

#include<SPI.h>

#define PIN_LED    4
#define PIN_SWITCH 2
#define PIN_LDR    A1

#define LED_OFF     0x01
#define LED_ON      0x02
#define READ_SWITCH 0x03
#define READ_LDR    0x04
#define NO_ACTION   0xFF

volatile byte received;
volatile boolean jobAvailable;
volatile byte unsentData[2];
volatile int unsentCount;           // initialized to 0 to indicate no data belonging to previous command is unsent

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);               // setting LED pin as OUTPUT

  setupSpiComm();

  printInfo();                            // print usage message onto device connected to HW Serial
}

void loop() {
  if (jobAvailable) {                     // react to command received from master
    noInterrupts();
    jobAvailable = false;                 // indicate no message to process
    interrupts();

    doCommand();                          // process command received from master
  }
}

void doCommand() {
  static boolean prevLedState = false;
  int ldrValue;
  switch (received) {                           // distinquish command received
    case LED_ON:
      if (!prevLedState) {
        digitalWrite(PIN_LED, HIGH);            // sets LED pin HIGH to switch LED on
        Serial.println(F("Slave: LED on"));
        prevLedState = true;
      }
      break;
    case LED_OFF:
      if (prevLedState) {
        digitalWrite(PIN_LED, LOW);             // sets LED pin LOW to switch LED off
        Serial.println(F("Slave: LED off"));
        prevLedState = false;
      }
      break;
    case READ_SWITCH:
      //Serial.println(F("Slave: read switch"));
      writeSpiByte(digitalRead(PIN_SWITCH) ? LED_ON : LED_OFF);
      break;
    case READ_LDR:
      //Serial.println(F("Slave: read LDR"));
      ldrValue = analogRead(PIN_LDR);
      Serial.print(F("Slave: LDR: "));
      Serial.print('('); Serial.print((ldrValue >> 8) & 0xFF);
      Serial.print(' '); Serial.print(ldrValue & 0xFF);
      Serial.print(") ");
      Serial.println(ldrValue);
      writeSpiInt(ldrValue);
      break;
    case NO_ACTION:                           // with SPI: will be sent from master following READ_SWITCH to get button state
      break;
    default:
      Serial.print(F("Slave: undefined command 0x"));
      Serial.println(received, HEX);
  }
}

void printInfo() {
  Serial.println(F("SPI communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: MOSI-MOSI, MISO-MISO, SCK-SCK, SS-SS (pin 10 on UNO)"));
  Serial.println(F("Slave switches LED on/off according to command received (LED_ON, LED_OFF)"));
  Serial.println(F("       reads own switch if requested and prepares result for next transfer (READ_SWITCH)"));
  Serial.println(F("       reads LDR if requested, prepares 2 result bytes (MSB first) for next transfers (READ_LDR)"));
  Serial.println(F("       prints LDR value sent to master (2 bytes, MSB folowed by LSB) onto Serial"));
}

void setupSpiComm() {
  pinMode(MISO, OUTPUT);                  // sets MISO as OUTPUT (Have to Send data to Master IN)

  jobAvailable = false;                   // nothing received yet -> nothing to do
  SPCR |= _BV(SPE);                       // turn on SPI in Slave Mode

  SPI.attachInterrupt();                  // interrupt ON is set for SPI commnucation
}

void writeSpiByte(byte value) {
  noInterrupts();
  SPDR = value; // send the button state on next transfer to master via SPDR
  interrupts();
}

void writeSpiInt(int value) {
  noInterrupts();
  unsentData[0] = value & 0xFF;    // preserve high byte of LDR value in unsent data at index 0
  unsentCount = 1;                          // remember count of unsent bytes
  SPDR = (value >> 8) & 0xFF; // send the low byte of the LDR value on next transfer to master via SPDR
  interrupts();
}

ISR (SPI_STC_vect) {                      // interrupt service routine function
  received = SPDR;                        // value received from master is store in variable received
  if (unsentCount > 0) {
    SPDR = unsentData[--unsentCount];     // send first unsent byte and reduce counter of unsent bytes
  } else {
    SPDR = NO_ACTION;                     // indicate nothing to be done on master (will be sent at next transfer)
    jobAvailable = true;                  // trigger loop as new command to be processed is available
  }
}
