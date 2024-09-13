#include <Servo.h>
Servo servo;
int i = 90;
char INBYTE;
const int led1 = 4;
const int led2 = 5;
const int led3 = 6;
const int led4 = 7;
const int trigPin = 12;
const int echoPin = 11;
long unsigned duration;
float distance;

void setup() {
  servo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);  
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.344/2;
  Serial.println(distance);
  delay(200);
  if(distance <=100){
    digitalWrite(led1, HIGH);
  } else{
    digitalWrite(led1, LOW);
  }
  while(Serial.available()){
    INBYTE = Serial.read();        // read next available byte
    if(INBYTE == 'W' || INBYTE == 'w'){
    digitalWrite(led1, HIGH);
    digitalWrite(led3, HIGH);
    delay(600);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);
    }
    if(INBYTE == 'S' || INBYTE == 's'){
      digitalWrite(led2, HIGH);
      digitalWrite(led4, HIGH);
      delay(600);
      digitalWrite(led2, LOW);
      digitalWrite(led4, LOW);
    }
    if(INBYTE == 'A' || INBYTE == 'a'){
      for(i; i < 180; i++){
        servo.write(i);
        delay(8);
      }
    }
    if(INBYTE == 'D' || INBYTE == 'd'){
      for(i; i > 0; i--){
        servo.write(i);
        delay(8);
      }
    }
    if(INBYTE == 'X' || INBYTE == 'x'){
      for(i; i<90; i++){
        servo.write(i);
        delay(8);
      }
      for(i; i>90; i--){
        servo.write(i);
        delay(8);
      }
    }
  }
}