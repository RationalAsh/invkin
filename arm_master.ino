/* 
  Radical change of plan! We're going
  to use I2C instead of serial! So the
  whole file is going to be rewritten.
  Goodbye pesky serial communication!
  
  Test with 0,0,0,0,0,0 and
  40,40,40,40,40,40
*/

#include <Wire.h>
#define M1 1  
#define M2 2
#define M3 3
#define M4 4
#define M5 5

//Declare all the angle variables
char th1 = 0;
char th2 = 0;
char th3 = 0;
char th4 = 0;
char th5 = 0;
char th6 = 0;

void setup() 
{
  // initialize serial
  Serial.begin(9600);
  //I2C communication
  Wire.begin();
}

void loop() 
{
  // if there's any serial available, read it:
  while (Serial.available() > 0) 
  {

    // look for the first valid integer in the incoming serial stream:
    th1 = (char)Serial.parseInt();
        
    //Look for the next integer
    th2 = (char)Serial.parseInt();
        
    //Do it again
    th3 = (char)Serial.parseInt();
        
    //And again
    th4 = (char)Serial.parseInt();
       
    //And again and again
    th5 = (char)Serial.parseInt();
       
    //Aaaaaaaand agaaaaain
    th6 = (char)Serial.parseInt();
    
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M1);
    Wire.write(th1);
    Wire.endTransmission();
    
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M2);
    Wire.write(th2);
    Wire.endTransmission();
    
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M3);
    Wire.write(th3);
    Wire.endTransmission();
    
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M4);
    Wire.write(th4);
    Wire.endTransmission();
    
    //Transmit the angle to the correct I2C slave
    Wire.beginTransmission(M5);
    Wire.write(th5);
    Wire.endTransmission();
    

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') 
    {
      //Print all the angles that were received
      //For debugging.
      Serial.print("Got angles: (");
      Serial.print((byte)th1);
      Serial.print(",");
      Serial.print((byte)th2);
      Serial.print(",");
      Serial.print((byte)th3);
      Serial.print(",");
      Serial.print((byte)th4);
      Serial.print(",");
      Serial.print((byte)th5);
      Serial.print(",");
      Serial.print((byte)th6);
      Serial.println(")");
      //Serial.println("Got angles!");
    }
  }
  
  delay(1);
}
