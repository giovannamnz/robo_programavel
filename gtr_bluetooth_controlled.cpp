#include <ESP32Servo.h>
#include <WiFi.h>
const char* ssid = "SSID da sua rede";
const char* password = "Senha da sua rede";
WiFiServer server(80);

Servo servo;
int i = 90;
char INBYTE;
const int motor_frente = 13;
const int motor_re = 12;
const int trigPin = 22;
const int echoPin = 18;
const int servoPin = 35;
long unsigned duration;
float distance;

void setup() {

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo.setPeriodHertz(50);
	servo.attach(servoPin, 500, 2400);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor_frente, OUTPUT);
  pinMode(motor_re, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.begin(9600);
}

void loop(){
  WiFiClient client = server.available();
  if(cliet){
    Serial.println("New Client.");
    String currentLine = "";
  
      while(Serial.available()){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = duration*0.344/2;
      INBYTE = Serial.read();
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
  
}