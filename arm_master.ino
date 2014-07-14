/* 
  1. Six numbers separated by some separator
  2. Get each number and store it in a variable
  3. Display these numbers over the serial monitor.
  4. Try using SerialEvent
  
  Steps:
  1. Get SerialEvent working with Hello World String
  3. Get Serial Event working with integer string
  4. Figure out how to parse each int.
  5. Store ints in variable and display.
*/

#include <SoftwareSerial.h>

SoftwareSerial m0(2,3);
SoftwareSerial m1(4,5);
SoftwareSerial m2(6,7);
SoftwareSerial m3(8,9);
SoftwareSerial m4(10,11);

int th0 = 0;
int th1 = 0;
int th2 = 0;
int th3 = 0;
int th4 = 0;
int th5 = 0;

void setup() {
  // initialize serials:
  Serial.begin(9600);
  m0.begin(9600);
  m1.begin(9600);
  m2.begin(9600);
  m3.begin(9600);
  m4.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    th0 = Serial.parseInt(); 
    m0.write(th0);
    m0.write('\n');
    // do it again:
    th1 = Serial.parseInt();
    m1.write(th1);
    m1.write('\n');
    // do it again:
    th2 = Serial.parseInt();
    m2.write(th2); 
    m2.write('\n');
    // do it yet again
    th3 = Serial.parseInt();
    m3.write(th3);
    m3.write('\n');
    //And again
    th4 = Serial.parseInt();
    m4.write(th4);
    m4.write('\n');
    //And again and again and again
    th5 = Serial.parseInt();

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      // print the three numbers in one string as hexadecimal:
      Serial.print("Got angles: (");
      Serial.print(th0);
      Serial.print(",");
      Serial.print(th1);
      Serial.print(",");
      Serial.print(th2);
      Serial.print(",");
      Serial.print(th3);
      Serial.println(")");
    }
  }
}
