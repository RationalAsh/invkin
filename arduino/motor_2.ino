

double potcurval;    // variable to read the value from the analog pin 
int angel; //Integer value of angle
 double angle =0;

 double curangle,kP=28.00,kI=42,kD=4,Last=0;
 double P=0,I=0,D=0,Drive,Error=0,Integral=0;
 

 void backward() {
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
  Serial.begin(9600);
} 
 void Errorcalc()
 {
   potcurval=(double)analogRead(A0)+1;
   potcurval=(potcurval/1024)*5;
    curangle=(potcurval/5)*270;
   
                Error = curangle-angle;
 }
void loop() 
{             if(Serial.available()>0)
{
   angle=(double)Serial.parseInt()+85;
 
}
               
  
                 Errorcalc();
                if (abs(Error) <.8){ // prevent integral 'windup'
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
                
                
                if (abs(Drive)>255) {
                Drive=(Drive/abs(Drive)) *235;
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
