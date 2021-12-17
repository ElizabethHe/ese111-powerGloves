# ese111-powerGloves
ese 111 final project
## Inspiration
Every student suffers from midterm and finals a lot, but there is no way to relieve the stress other than going to parties. To help students relieve their stress when there is no party, we create power gloves.
## What it does
Power gloves will assess your punch strength based on decelerations and produce different LED colors and sounds based on the strength. It will produce green color and low pitch sound when the punch is light, yellow color and medium pitch when the punch is medium, and red color and a high pitch sound when the punch is really hard. It will upload your punch intensity and frequency to the cloud with the respective LED color indicator so that it is available to view online. In the Adafruit dashboard, students can also view their punch intensity history to see how stressful they have been recently. 
## How we built it
We will use Arduino Uno, accelerometer, piezo-buzzer, and LED light to build the circuit. We will upload the data to Adafruit cloud using NodeMCU.
We will use a punching glove to attach everything to it. 
## Challenges we ran into
We originally tried to use Blynk, but we ran into a problem using blynk so we switched to Adafruit. But the UI of Adafruit actually looks better.
We had a problem with connecting RGB LED to different resister values but eventually fixed it.
## Accomplishments that we're proud of
We are proud of the fact we serve student communities and add more fun to our penn life. Also It feels so good to build a project from scratch.
## What we learned
Arduino, Arduino Code, how to connect NodeMCU and upload data, more about RGB LED
## what's on github
two folders included. Frist one is the code run on NodeMCU, including how data is requested and wifi is configured. Second one is run on Arduino, including how accelerometer integrates with RGB LED light.
## Hardware implementations
Hardware part shoudl be really simple, a picture is included below for reference. Note that resisters value should be different for each prang of the RGB LED light because the red color requires least share of voltage.
![glove](https://user-images.githubusercontent.com/80422017/146493342-d8d055f9-4dfd-42fa-b49c-8f8669660668.jpg)
