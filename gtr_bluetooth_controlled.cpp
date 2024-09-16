#include <Servo.h>
Servo servo;
int i = 90;
char INBYTE;
const int motor_acelerar = 4;
const int motor_ré = 5;
const int IR1 = 6;
const int IR2 = 7;
const int trigPin = 12;
const int echoPin = 11;
long unsigned duration;
float distance;

void setup() {
  servo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(motor_acelerar, OUTPUT);
  pinMode(motor_ré, OUTPUT);
  
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

  while(Serial.available()){
    INBYTE = Serial.read();
    if(distance <= 100 || digitalRead(IR1) == HIGH || digitalRead(IR2) == HIGH){
      digitalWrite(motor_acelerar, LOW);
      digitalWrite(motor_ré, LOW)
    } else {
      if(INBYTE == 'W' || INBYTE == 'w'){
      digitalWrite(motor_acelerar, HIGH);
      delay(600);
      digitalWrite(motor_acelerar, LOW);
      }
    }
    if(INBYTE == 'S' || INBYTE == 's'){
      digitalWrite(motor_ré, HIGH);
      delay(600);
      digitalWrite(motor_ré, LOW);
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
