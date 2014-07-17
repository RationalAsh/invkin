/* 
  Radical change of plan! We're going
  to use I2C instead of serial! So the
  whole file is going to be rewritten.
  Goodbye pesky serial communication!
*/

#include <Wire.h>
#define M1 1
#define M2 2
#define M3 3
#define M4 4
#define M5 5

//Declare all the angle variables
int th1 = 0;
int th2 = 0;
int th3 = 0;
int th4 = 0;
int th5 = 0;
int th6 = 0;

void setup() 
{
  // initialize serial
  Serial.begin(9600);
  //
  Wire.begin();
}

void loop() 
{
  // if there's any serial available, read it:
  while (Serial.available() > 0) 
  {

    // look for the first valid integer in the incoming serial stream:
    th1 = Serial.parseInt();
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M1);
    Wire.write(th1);
    Wire.endTransmission();
    
    //Look for the next integer
    th2 = Serial.parseInt();
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M2);
    Wire.write(th2);
    Wire.endTransmission();
    
    //Do it again
    th3 = Serial.parseInt();
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M3);
    Wire.write(th3);
    Wire.endTransmission();
    
    //And again
    th4 = Serial.parseInt();
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M4);
    Wire.write(th4);
    Wire.endTransmission();
    
    //And again and again
    th5 = Serial.parseInt();
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M5);
    Wire.write(th5);
    Wire.endTransmission();
    
    //Aaaaaaaand agaaaaain
    th6 = Serial.parseInt();
    

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') 
    {
      //Print all the angles that were received
      //For debugging.
      Serial.print("Got angles: (");
      Serial.print(th0);
      Serial.print(",");
      Serial.print(th1);
      Serial.print(",");
      Serial.print(th2);
      Serial.print(",");
      Serial.print(th3);
      Serial.print(",");
      Serial.print(th4);
      Serial.print(",");
      Serial.print(th5);
      Serial.println(")");
    }
  }
}
