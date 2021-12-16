#include <Servo.h>
#include <Encoder.h>  
#include <Stepper.h>
//  Auto Generated Code for Arduino IDE
//  Created using keuwlsofts Bluetooth Electronics App
//  www.keuwl.com

//  Steps: 
//  1) Upload code and power your Arduino project 
//  2) Run Bluetooth Electronics App and connect to your device 
//  3) Press the reset button on your Arduino 

//  This auto generated code template is only a suggestion to get you started.
//  It is incomplete and will need modification specific to your project.

int update_interval=100; // time interval in ms for updating panel indicators 
unsigned long last_time=0; // time of last update
char data_in; // data received from serial link
int slider_value_red; // Received Slider Values
int slider_value_blue;
int slider_value_green;
int slider_value_servo;
int val;

// Stepper values
Stepper stepper(STEPS, 8, 9, 10, 11);
int previous = 0;

String text; // String for text elements

int red_light_pin= 3;
int green_light_pin = 5;
int blue_light_pin = 6;

Servo servoMain;
long altePosition = -999;

void setup() {

  Serial.begin(115200); //Change baud rate as required!

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  servoMain.attach(9);
  stepper.setSpeed(30);

///////////// Build panel in app

Serial.println("*.kwl");
delay(2);
Serial.println("clear_panel()");
delay(2);
Serial.print("set_grid_size(17,7)");
delay(2);
Serial.println("");
delay(2);
Serial.print("add_text(1,0,xlarge,");
delay(2);
Serial.print("L,Led Brightness Con");
delay(2);
Serial.print("troller,250,245,240,");
delay(2);
Serial.println("0)");
delay(2);
Serial.print("add_text(3,2,xlarge,");
delay(2);
Serial.print("R,Red LED,250,115,11");
delay(2);
Serial.println("0,0)");
delay(2);
Serial.print("add_text(3,3,xlarge,");
delay(2);
Serial.print("R,Green LED,110,245,");
delay(2);
Serial.println("110,0)");
delay(2);
Serial.print("add_text(3,4,xlarge,");
delay(2);
Serial.print("R,Blue LED,90,110,24");
delay(2);
Serial.println("5,0)");
delay(2);
Serial.print("add_slider(4,3,1,0,2");
delay(2);
Serial.println("55,0,G,A,0)");
delay(2);
Serial.print("add_slider(4,4,1,0,2");
delay(2);
Serial.println("55,0,B,A,0)");
delay(2);
Serial.print("add_slider(4,2,1,0,2");
delay(2);
Serial.println("55,0,R,A,0)");
delay(2);
Serial.print("set_panel_notes(LED ");
delay(2);
Serial.print("Brightness,Control t");
delay(2);
Serial.print("he Red, Green and Bl");
delay(2);
Serial.print("ue Brightness,with S");
delay(2);
Serial.print("liders that adjust t");
delay(2);
Serial.print("he PWM.,Requires: Ar");
delay(2);
Serial.print("udino, HC-06, LEDs, ");
delay(2);
Serial.println("Resistors)");
delay(2);
Serial.println("run()");
delay(2);
Serial.println("*");
delay(2);

}

void loop() {

  /////////////   Receive and Process Data

  if (Serial.available()){
    data_in=Serial.read();  //Get next character 

    if(data_in=='G'){ //  Slider
      slider_value_green=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
    }

    if(data_in=='B'){ //  Slider
      slider_value_blue=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
    }

    if(data_in=='R'){ //  Slider
      slider_value_red=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
    }

    if (data_in=='A') {
      long neuePosition = Serial.parseInt();
      if (neuePosition != altePosition && neuePosition % 4 == 0){

    
      altePosition = neuePosition;
      Serial.println(neuePosition / 4);
      servoMain.write(neuePosition);
      delay(1000);
     }
   }

   if (data_in=='C') {
      int val = Serial.parseInt();
      // dreht den Motor ja nach Sensorwert (Potentiometer)
      stepper.step(val - previous);
      previous = val;
   }
   
    setColor(slider_value_red, slider_value_green, slider_value_blue);
  }

  /////////////  Send Data to Android device

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("*0"+text+"*");
delay(2);

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("*0"+text+"*");
delay(2);

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("*0"+text+"*");
delay(2);

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("*0"+text+"*");
delay(2);

  }
}


void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(red_light_pin, redValue);
  analogWrite(green_light_pin, greenValue);
  analogWrite(blue_light_pin, blueValue);
}
