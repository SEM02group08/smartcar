
//#include <Smartcar.h>

#include <Wire.h>



#include <Ultrasonic.h>

#include <Servo.h>

#include <Smartcar.h>

//#include <NewPing.h>

//#include "Ultrasonic.h"




//implement thermometer left


Car car;
//attach components

const int fSpeed = 70; //70% of the full speed forward
const int bSpeed = -70; //70% of the full speed backward
const int lDegrees = -75; //degrees to turn left
const int rDegrees = 75;

Odometer encoderLeft, encoderRight;
Gyroscope gyro;
SR04 ultrasonicFront; // define Ultrasonic object
SR04 ultrasonicBack;//values
int speedValue, angle;
int frontObjEncountered, backObjEncountered;//read input for direction
const int TRIGGER_PIN =6;
const int ECHO_PIN=5;


char in;


int distance=0;
// set up the active buzzer

int speakerPin =A0;
int volume=0;



void setup() {
 Serial.begin(9600);  //initialise components
 gyro.attach();
 encoderLeft.attach(2);
 encoderRight.attach(3);
 encoderLeft.begin();
 encoderRight.begin();
 gyro.begin();
 car.begin(encoderLeft, encoderRight, gyro);
 ultrasonicFront.attach(6, 5);
 ultrasonicBack.attach(10,9);


//  ultrasonicfront ;
 in=0;
 speedValue=0;
 angle=0;
 frontObjEncountered=0;
 backObjEncountered=0;
 
 
 //int distance=0;

 pinMode (speakerPin, OUTPUT);
}

void loop()
{
   if(Serial3.available())
   {
     in=Serial3.read();
     handleInput();
 
   }
  else if
  {
   if(frontIsClear()==false)
   {  
       speedValue = 0;

 
   distance=ultrasonicFront.getDistance();
 //  distance=ultrasonicBack.Ranging(CM);

       if ( distance>15)
       {
        Serial.println(distance);
        speedValue=50;
        car.setSpeed(speedValue);
        
        volume=0;
       }

       else
       {
        Serial.println(distance);
        speedValue=0;
        car.setSpeed(speedValue);
        
       
         for( volume; volume<255; volume++)
        {
            analogWrite (speakerPin, volume);
            delay (10);
         }
     
       // volume=0;
     
      }
   
    else 
  {
   if(backIsClear()==false)
   {  
       speedValue = 0;

 
   distance=ultrasonicBack.getDistance();
 //  distance=ultrasonicBack.Ranging(CM);

       if ( distance>15)
       {
        Serial.println(distance);
        speedValue=50;
        car.setSpeed(speedValue);
        
        volume=0;
       }

       else
       {
        Serial.println(distance);
        speedValue=0;
        car.setSpeed(speedValue);
        
       
         for( volume; volume<255; volume++)
        {
            analogWrite (speakerPin, volume);
            delay (10);
         }
     
       // volume=0;
     
      }
   
 }
}
}
//handle serial input if there is any
void handleInput() {
 switch(in){
   //go front
 case 'f': 
        car.setSpeed(fSpeed);
        car.setAngle(0);
   break;
   
 //go back
 case 'b': 
        car.setSpeed(bSpeed);
        car.setAngle(0);
        break;
           //go right
 case 'r': 
        car.setSpeed(fSpeed);
        car.setAngle(rDegrees);
        break;
  case 'l': 
        car.setSpeed(fSpeed);
        car.setAngle(lDegrees);
        break;
   
 
 case 's': speedValue = 0;
           angle = 0;
           car.setAngle(angle);
           car.setSpeed(speedValue);
       
}
if(frontIsClear()==false){  
 speedValue = 0;
 angle = 0;
 car.setAngle(angle);
 car.setSpeed(speedValue);
}
} 
// check the distance given by the ultrasonic
//in order to see if the car encounters an object or not in front
boolean frontIsClear(){
frontObjEncountered =  ultrasonicFront.getDistance();
 if(frontObjEncountered > 50)
 return true;
if(frontObjEncountered == 0)
 return true; 
 return false;
}//check the distance given by the ultrasonic
//in order to see if the car encounters an object or not in the back
boolean backIsClear(){
backObjEncountered = ultrasonicBack.getDistance();
if (backObjEncountered > 50)
 return true;
if (backObjEncountered == 0)
 return true;  
 return false;
}

