#include <Servo.h>
Servo servo;
int i = 90;
char INBYTE;
const int motor_frente = 3;
const int motor_re = 5;
const int infra_vermelho = 10;
const int trigPin = 13;
const int echoPin = 12;
long unsigned duration;
float distance;
const float distanciaSegura = 20.0;

void setup() {
  servo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(infra_vermelho, INPUT);
  pinMode(motor_frente, OUTPUT);
  pinMode(motor_re, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  verificarDistancia();
  while(Serial.available()){
    INBYTE = Serial.read();
    if(INBYTE == 'W' || INBYTE == 'w'){
      Serial.println("Movendo para frente");
      moverParaFrente();
    }
    if(INBYTE == 'S' || INBYTE == 's'){
      Serial.println("Movendo para tras");
       moverParaTras();
    }
    if(INBYTE == 'A' || INBYTE == 'a'){
      Serial.println("Movendo para esquerda");
      virarEsquerda();
    }
    if(INBYTE == 'D' || INBYTE == 'd'){
      Serial.println("Movendo para direita");
      virarDireita();
    }
    if(INBYTE == 'X' || INBYTE == 'x'){
      Serial.println("Movendo para posicao neutra");
      ajustarPosicaoNeutra();
    }
  }
}

void verificarDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2; // Calcula a distância em cm

  if (distance <= distanciaSegura) {
    pararMovimento(); // Para o movimento se um obstáculo estiver muito perto
  }
}

void moverParaFrente() {
  if (distance > distanciaSegura) {
    digitalWrite(motor_frente, HIGH);
    delay(500);
    digitalWrite(motor_frente, LOW);
  } else {
    pararMovimento();
  }
}

void moverParaTras() {
  if (digitalRead(infra_vermelho) == LOW){
    digitalWrite(motor_re, LOW);
  } else{
    digitalWrite(motor_re, HIGH);
    delay(500);
    digitalWrite(motor_re, LOW);
  }
}

void virarEsquerda() {
  for (i; i < 180; i++) {
    servo.write(i);
    delay(10);
  }
}

void virarDireita() {
  for (i; i > 0; i--) {
    servo.write(i);
    delay(10);
  }
}

void ajustarPosicaoNeutra() {
  if(i < 90){
    for (i; i < 90; i++) {
      servo.write(i);
      delay(10);
    }
  } else if(i>90){
    for (i; i > 90; i--) {
      servo.write(i);
      delay(10);
    }
  }else{
      servo.write(i);
      delay(5);
  }
}

void pararMovimento() {
  // Função para parar todos os movimentos
  digitalWrite(motor_frente, LOW);
  Serial.println("Obstáculo detectado! Movimento interrompido.");
}
