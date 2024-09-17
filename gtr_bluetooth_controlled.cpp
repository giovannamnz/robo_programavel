#include <ESP32Servo.h>
#include <WiFi.h>

const char* ssid = "SSID da sua rede";
const char* password = "Senha da sua rede";
WiFiServer server(80);

Servo servo;
int i = 90;
const int motor_frente = 13;
const int motor_re = 12;
const int trigPin = 22;
const int echoPin = 18;
const int servoPin = 35;
long unsigned duration;
float distance;
const float distanciaSegura = 20.0; // Definir a distância mínima segura (em cm)
const int infra_vermelho1 = 34;

void setup() {
  Serial.begin(9600); // Inicialize a comunicação serial
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
  pinMode(infra_vermelho1, INPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Aguarda um cliente conectar
  if (client) {
    Serial.println("Novo cliente conectado.");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // Mostra o caractere recebido no monitor serial

        if (c == '\n') {
          // Se a linha estiver vazia, envia uma resposta HTML
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("Click <a href='/W'>aqui</a> para ir para frente");
            client.println("Click <a href='/S'>aqui</a> para ir para trás");
            client.println("Click <a href='/A'>aqui</a> para virar à esquerda");
            client.println("Click <a href='/D'>aqui</a> para virar à direita");
            client.println("Click <a href='/X'>aqui</a> para ajustar as rodas na posição neutra");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Verifica os comandos recebidos pela URL
        if (currentLine.endsWith("GET /W")) {
          moverParaFrente();
        }
        if (currentLine.endsWith("GET /S")) {
          moverParaTras();
        }
        if (currentLine.endsWith("GET /A")) {
          virarEsquerda();
        }
        if (currentLine.endsWith("GET /D")) {
          virarDireita();
        }
        if (currentLine.endsWith("GET /X")) {
          ajustarPosicaoNeutra();
        }
        verificarDistancia();
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.");
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

  Serial.print("Distância: ");
  Serial.println(distance);

  if (distance <= distanciaSegura) {
    pararMovimento(); // Para o movimento se um obstáculo estiver muito perto
  }
}

void moverParaFrente() {
  if (distance > distanciaSegura) {
    digitalWrite(motor_frente, HIGH);
    delay(600);
    digitalWrite(motor_frente, LOW);
  } else {
    pararMovimento();
  }
}

void moverParaTras() {
  if (digitalRead(infra_vermelho1) == HIGH){
    pararMovimento();
  } else{
  digitalWrite(motor_re, HIGH);
  delay(600);
  digitalWrite(motor_re, LOW);
  }
}

void virarEsquerda() {
  for (int i = 90; i < 180; i++) {
    servo.write(i);
    delay(8);
  }
}

void virarDireita() {
  for (int i = 90; i > 0; i--) {
    servo.write(i);
    delay(8);
  }
}

void ajustarPosicaoNeutra() {
  for (int i = 90; i < 180; i++) {
    servo.write(i);
    delay(8);
  }
  for (int i = 180; i > 90; i--) {
    servo.write(i);
    delay(8);
  }
}

void pararMovimento() {
  // Função para parar todos os movimentos
  digitalWrite(motor_frente, LOW);
  digitalWrite(motor_re, LOW);
  Serial.println("Obstáculo detectado! Movimento interrompido.");
}