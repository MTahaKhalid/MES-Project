#include <Ultrasonic.h>

Ultrasonic ultrasonic(A2, A3);
int distance;
#define LS A1      // left sensor
#define RS A0      // right sensor

#define LM1 7       // left motor
#define LM2 6       // left motor
#define RM1 9       // right motor
#define RM2 8       // right motor
void setup() {
  Serial.begin(9600);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  if(distance>=10){
  if((digitalRead(LS)==1)&&(digitalRead(RS)==1))     // When Both Sensors are on Black Surface Move Forward sesnor light off
  {
    
    digitalWrite(LM1,HIGH);
    digitalWrite(LM2, LOW);
    analogWrite(5,90);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(10,90);
  }
  else if((digitalRead(LS)==0)&&(digitalRead(RS)==1))     
  { 
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    analogWrite(5,90);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(10,90);
  }
  else if((digitalRead(LS)==1)&&(digitalRead(RS)==0))     
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    analogWrite(5,90);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(10,90);
  }
  else if((digitalRead(LS)==0)&&(digitalRead(RS)==0))     
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  }
  else if(distance<10){
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    analogWrite(5,90);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(10,90);
  }
}