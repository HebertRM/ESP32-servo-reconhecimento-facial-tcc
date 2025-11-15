#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);

Servo servoMotor;

void handleAcao() { // acao ao receber a requisicao
  Serial.println("✅ Requisição recebida em /acao!");

  String nome = ""; 

  if (server.hasArg("nome")) { // caso envie algum parametro com noem para testar
    nome = server.arg("nome");
  }

  Serial.print("📩 Recebido parâmetro nome: ");
  Serial.println(nome);

  // Movimento do servo
  servoMotor.write(0);
  delay(500);
  servoMotor.write(90);
  delay(500);
  servoMotor.write(180);
  delay(500);

  //retorno request
  server.send(200, "text/plain", "Ação recebida com sucesso!");
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  // Conectando no WiFi real
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password,6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Liga o servo no pino 18 (pode mudar)
  servoMotor.attach(18);

  // Rota GET
  server.on("/acao", HTTP_GET, handleAcao);

 // Inicia o servidor
  server.begin();
  Serial.println("Servidor iniciado!"); 
}

void loop() {
  server.handleClient(); // Trata requisições
}
