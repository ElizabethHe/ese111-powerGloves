/***************************************************************************
 * Created by: Bhagath Cheela, 2021-12-03
  All instructions are on the github repo. https://github.com/ese-detkin-lab/
 ***************************************************************************/
#include <Wire.h>

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

// Adafruit Feeds
AdafruitIO_Feed *acceleration = io.feed("acceleration");
AdafruitIO_Feed *color = io.feed("color");

static const uint8_t D1   = 5;
static const uint8_t D2   = 4;

void setup() {
 Serial.begin(9600); /* begin serial for debug */
 Wire.begin(5, 4); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

 // connect to io.adafruit.com
 io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
 // io.run(); is required for all sketches.
 // it should always be present at the top of your loop
 // function. it keeps the client connected to
 // io.adafruit.com, and processes any incoming data.
 io.run();

 //Uncomment this to send some information to Arduino
 
 Wire.beginTransmission(8); // begin with device address 8 
 Wire.write("Hello Arduino");  // sends hello string 
 Wire.endTransmission();    // stop transmitting

 Wire.requestFrom(8, 2); /* request & read data of size 13 from Node MCU */
 while(Wire.available()){
    int in_color = Wire.read();
     //Send the received data to cloud
    color->save(in_color);
    Serial.print(in_color);
    delay(1000);

     int in_acceleration = Wire.read();
     //Send the received data to cloud
    acceleration->save(in_acceleration);
    Serial.print(in_acceleration);
    delay(1000);
 }
 
 Serial.println();
 delay(1000);
}
