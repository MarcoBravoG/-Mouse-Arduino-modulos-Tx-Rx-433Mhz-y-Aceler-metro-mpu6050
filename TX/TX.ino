// transmitter.ino

// include libraries: 
#include <RH_ASK.h>
#include <SPI.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>


// Create an instance of the RadioHead ASK handler:
// -> Default pins for the RF modules:
//    Pin 11: Data input from receiver
//    Pin 12: Data output to transmitter
RH_ASK radio;

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;

int button1 = 6;
int button2 = 7;
int buttonState1 = 0; 
int buttonState2 = 0; 


// Create and initialize three 8-bit variables for our RGB values:
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

void setup() {
    Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  // initialize the RadioHead library:
  radio.init();
    Wire.begin();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  mpu.initialize();
  if (!mpu.testConnection()) { while (1); }
}



void loop() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 uint8_t iz = analogRead(A1);
  vx = (gx+15)/150;  
  vy = (gz-100)/150;

  Serial.print("        | izq = ");
  Serial.print(iz);
  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);
    // put the individual 8-bit RGB values into an array:
  uint8_t dataArray[] = {iz, vx, vy};
  // RadioHead requires the pointer to the array as a parameter, so let's obtain the pointer first:
  const uint8_t *data = dataArray;

  // push the pointer to the data as well as the length of the data (= 3 Bytes) to the RadioHead instance:
  radio.send((uint8_t *)data, 3);
  // wait until RadioHead has sent the entire data packet to the receiver:
  radio.waitPacketSent();

delay(100);
  }
  