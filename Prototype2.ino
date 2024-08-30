#include <DHT.h>

#include "thingProperties.h"
const int DHTPIN = 32;
const int DHTTYPE = DHT11;
float temperatura = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicia o monitor serial
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Conecta com o arduíno cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  // Inicia o sensor
  dht.begin();
}
// Inicia a leitura da temperatura
float lerTemperatura() {
  float temperature = dht.readTemperature();
  return temperature;
}

void loop() {
  // atualiza os dados no cloud
  ArduinoCloud.update();
  delay(1000);
  // Chama a variável criada no cloud para o envio das leituras do sensor
  temperatura = lerTemperatura();
  tempH = temperatura;
  // Imprime a temperatura
  Serial.print("Temperature (C): ");
  Serial.println(temperatura);
  
  
}
