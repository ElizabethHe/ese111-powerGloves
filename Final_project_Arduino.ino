// control LED and buzzer using the accelerometer

// a good punch includes a significant acceleration
// followed by massive deceleration at the end
// happens within failly small amount of time
// shoudl be easy to distinguish a punch from normal gestures

// NodeMCU-Ping-IO.ino
// For M&TSI 2021

//#include "config.h"

//// set up the 'colors' and 'acceleration' feed
//AdafruitIO_Feed *accelerations = io.feed("accelerations");
//AdafruitIO_Feed *colors = io.feed("colors");

// these correspond to the pins on your NodeMCU
//const int redPin2 = 5;
//const int bluePin2 = 7;
//const int greenPin2 = 6;
//const int buzzer2 = 8;

#include<Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;
unsigned long punchStart = 0;//variable for non-blocking punch timeframe check
const long punchInterval = 200;//timeframe of a punch in ms, from max acceleration to max deceleration, 200 is very generous
int punchAccel = 20;//the beginning of a punch in m/s^2, could be over 50m/s^2 depending on the puncher
const int redPin = 3;
const int bluePin = 6;
const int greenPin = 5;
//const int LED = 8;
const int buzzer = 9;
int punchDecel = -40;//the end of a punch in m/s^2, could be less than -100m/s^2 depending on the puncher
int midPunchDecel = -70;
int highPunchDecel = -120;

//// Add NodeMCU
//uint8_t redPin2 = D5;
//uint8_t greenPin2 = D6;
//uint8_t bluePin2 = D7;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int color;
int acceleration;
// now, we will send this value to the cloud to tell it which color we want to show
// blue = 0, green = 1, and red = 2


void setup(){
  
Serial.begin(115200);


  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
    Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G); // for good range
  Serial.print("Range = "); Serial.print(2 << mpu.getAccelerometerRange());  
  Serial.println("G");
  pinMode(redPin, OUTPUT); // (LED)
  pinMode(bluePin, OUTPUT); // (LED)
  pinMode(greenPin, OUTPUT); // (LED)
  pinMode(buzzer, OUTPUT); 

 Wire.begin(8);                 // join i2c bus with address 8 
 //Wire.onReceive(receiveEvent); // register receive event 
 Wire.onRequest(requestEvent);
  
//  pinMode(LED,OUTPUT); // Single LED testing 
//  digitalWrite(LED,LOW);
//  pinMode(buzzer,OUTPUT);

//  // wait for serial monitor to open
//  while(! Serial);
//
//  Serial.print("Connecting to Adafruit IO");
//
//  // connect to io.adafruit.com
//  io.connect();
//
//  // wait for a connection
//  while(io.status() < AIO_CONNECTED) {
//    Serial.print(".");
//    delay(500);
//  }
//  // we are connected
//  Serial.println();
//  Serial.println(io.statusText());
}


void loop() {
  // put your main code here, to run repeatedly:

  /* Get new sensor events with the readings */
  
  sensors_event_t a,g,temp;
  mpu.getEvent(&a, &g, &temp);

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
//  io.run();
  acceleration = a.acceleration.x;
  analogWrite(redPin,0);
  analogWrite(bluePin,0);
  analogWrite(greenPin,0);
  
   //look for punch starting, at least 20 m/s^2
  if (acceleration > punchAccel){
     Serial.println(acceleration);
     punchStart = millis();
  }
  
  unsigned long currentMillis = millis();

  //look for low punch ending, less than -40 m/s^2
  // LED is green
  if (acceleration < punchDecel && currentMillis - punchStart < punchInterval 
  && acceleration > midPunchDecel){
      Serial.println(acceleration);
      Serial.println("Low Punch");
      color = 1;
      analogWrite(redPin, 0);
      analogWrite(bluePin,0);
      analogWrite(greenPin, 255);
      delay(2000);
      analogWrite(redPin, 0);
      analogWrite(bluePin,0);
      analogWrite(greenPin, 0); 


  tone(buzzer,1000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  }  
  
    //look for mid punch ending, less than -40 m/s^2
    //LED is blue
  if (currentMillis - punchStart < punchInterval && acceleration < midPunchDecel 
  && acceleration > highPunchDecel){
      Serial.println(acceleration);
      Serial.println("Medium Punch");
      color = 0;
      analogWrite(redPin, 0);
      analogWrite(bluePin,255);
      analogWrite(greenPin, 0);
      delay(2000);
      analogWrite(redPin, 0);
      analogWrite(bluePin,0);
      analogWrite(greenPin, 0); 

  tone(buzzer,3000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  } 

      // LED is red
      //look for high punch ending, less than -40 m/s^2
  if (currentMillis - punchStart < punchInterval && acceleration < highPunchDecel){
      Serial.println(acceleration);
      Serial.println("High Punch");
      color = 2;
      analogWrite(redPin, 255);
      analogWrite(bluePin,0);
      analogWrite(greenPin, 0);
      delay(2000);
      analogWrite(redPin, 0);
      analogWrite(bluePin,0);
      analogWrite(greenPin, 0); 

//      digitalWrite(LED,HIGH);
//      delay(1000);
//      digitalWrite(LED,LOW);
//      Light( );

  tone(buzzer,5000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  }      
    }
  
  //Uncomment this to send some information to Arduino
// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      // receive byte as a character
    Serial.print(c);           // print the character
  }
 Serial.println();             // to newline
}


  // function that executes whenever data is requested from master
void requestEvent() {
// Wire.write("Hello NodeMCU");  /*send string on request */
 Wire.write(color);  /*send string on request */
  Wire.write(acceleration);
}
