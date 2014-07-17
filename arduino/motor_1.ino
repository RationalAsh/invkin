#include <Wire.h> 
double potcurval;    // variable to read the value from the analog pin 
int angel; //Integer value of angle
 double angle =0;

 double curangle,kP=30.00,kI=0,kD=0,Last=0;
 double P=0,I=0,D=0,Drive,Error=0,Integral=0;
 
 String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

 void backward()
 {
   digitalWrite(12,HIGH);
   digitalWrite(9,LOW);
 }
  void forward()
 {
   digitalWrite(12,LOW);
   digitalWrite(9,HIGH);
 }
 void halt()
 {
    digitalWrite(12,LOW);
    digitalWrite(9,LOW);
 }
void setup() 
{ 
  // myservo.attach(6);  // attaches the servo on pin 9 to the servo object 
  pinMode(9,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(13, OUTPUT);
  inputString.reserve(5);
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
} 
 void Errorcalc()
 {
   potcurval=(double)analogRead(A0)+1;
   potcurval=(potcurval/1024)*5;
    curangle=(potcurval/5)*270;
   
                Error = curangle-angle;
 }
void loop() 
{ 
	   
                 Errorcalc();
                if (abs(Error) <2.2){ // prevent integral 'windup'
                Integral = Integral + Error; // accumulate the error integral
                }
                else {
                Integral=0; // zero it if out of bounds
                }
                P = Error*kP; // calc proportional term
                I = Integral*kI; // integral term
                D = (Last-curangle)*kD; // derivative term
                
                Drive = P + I + D; // Total drive = P+I+D
                
                //Drive = (Drive/550)*255; // scale Drive to be in the range 0-255
                
                if(abs(Drive) < 60)
                {
                  Drive += (Drive/abs(Drive)) *60;
                }
                if (abs(Drive)>255) {
                Drive=(Drive/abs(Drive)) *255;
                }
                
                
                Serial.println(Error);
                if (Error < 0){ // Check which direction to go.
                forward();
                
                }
                else if(Error >=0){ // depending on the sign of Error
                 backward();
                 
                }
                
                if(abs(Error)<2)
                {
                  halt();
                }
                
                analogWrite (11,abs(Drive)); // send PWM command to motor board
                Last=curangle;
   /*
    Serial.println("P :");
    Serial.println(P);
    Serial.println("I :");
    Serial.println(I);
    Serial.println("D :");
    Serial.println(D);
    */

}

void receiveEvent(int howMany)
{
  int x = Wire.read();
  angle = (double) x;
  Serial.print("got: ");
  Serial.println(angle);
  if(angle == 40) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
}
