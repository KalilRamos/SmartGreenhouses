#include <DHT.h> // Inclui biblioteca para o funcionamento do sensor

#include "thingProperties.h" // Inclui a biblioteca para que a integração do código com a plataforma funcione
const int DHTPIN = 32;
const int DHTTYPE = DHT11;
float temperatura = 0;

DHT dht(DHTPIN, DHTTYPE); // Define o tipo do sensor DHT11

void setup() {
  // Inicia o monitor serial
  Serial.begin(9600);
  delay(1500); // Intervalo de 1 segundo e meio entre as impressões no monitor serial

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
  float temperature = dht.readTemperature(); // Sensor lê a temperatura
  return temperature; // Sernsor devolve a temperatura obtida
}

void loop() {
  // atualiza os dados no cloud
  ArduinoCloud.update();
  delay(1000); // Intervalo de 1 segundo para a atualização na plataforma de monitoramento
  // Chama a variável criada no cloud para o envio das leituras do sensor
  temperatura = lerTemperatura();
  tempH = temperatura;
  // Imprime a temperatura
  Serial.print("Temperature (C): ");
  Serial.println(temperatura);

  delay(1000); // Intervalo de 1 segundo para o loop do código
  
  
}
