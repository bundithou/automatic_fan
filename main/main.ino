///////////////////////////////////
int state = 1;



///////////////////////////////////
#include <ESP32Servo.h>
#define SERVO_PIN 18
Servo sv;  // create servo object to control a servo
int pos = 0;      // position in degrees

//////////////////////////////////
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_PIN 19
int max_pos = 100;
int min_pos = 0;

//RC codes
#define ON_0 0x00FF6897
#define ON_1 0x00FF30CF
#define ON_2 0x00FF18E7
#define ON_3 0x00FF7A85
#define ON_4 0x00FF10EF
#define ON_5 0x00FF38C7
#define ON_6 0x00FF5AA5
#define ON_7 0x00FF42BD
#define ON_8 0x00FF4AB5
#define ON_9 0x00FF52AD
#define ON_LEFT 0x00FF22DD
#define ON_RIGHT 0x00FF02FD

IRrecv ir_recv (IR_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  ir_recv.enableIRIn (); // Start the receiver
  sv.setPeriodHertz(50);      // Standard 50hz servo
}

void loop() { 
  if(ir_recv.decode(&results)){
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    switch(results.value){
      case ON_0:
        Serial.println("Zero");
        break;
      case ON_1:
        Serial.println("One");
        state = 1;
        break;
      case ON_2:
        Serial.println("Two");
        state = 2;
        break;
      case ON_3:
        Serial.println("Three");
        break;
      case ON_LEFT:
        Serial.println("left");
        if(state == 2) manual_swing(2);
        
        break;
      case ON_RIGHT:
        Serial.println("right");
        if(state == 2) manual_swing(1);
        break;
    }
    ir_recv.resume();
    delay(100);
  }

  //Serial.println("pos: "+(pos));
  //auto_swing();
  
}


void auto_swing() {
  // put your main code here, to run repeatedly:
    sv.attach(SERVO_PIN);

  for (pos = 0; pos <= 135; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    sv.write(pos);
    delay(50);             // waits 20ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    sv.write(pos);
    delay(50);             // waits 20ms for the servo to reach the position
  }

  sv.detach();
  delay(500);
}

void manual_swing(int direction) {
  // put your main code here, to run repeatedly:
    sv.attach(SERVO_PIN);
    int p = pos;
    if(direction == 1){
      for (p = pos; p <= pos+10 && p <= max_pos ; p += 1) { // sweep from 0 degrees to 180 degrees
        // in steps of 1 degree
        sv.write(p);
        delay(10);             // waits 20ms for the servo to reach the position
      }
    }  
    else if (direction == 2){
      for (p = pos; p >= pos-10 && p >= min_pos; p -= 1) { // sweep from 0 degrees to 180 degrees
        // in steps of 1 degree
        sv.write(p);
        delay(10);             // waits 20ms for the servo to reach the position
      }
    } 
    pos = p;
    Serial.println((pos));
    sv.detach();
    delay(500);
}
