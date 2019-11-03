#include "DHT.h"
#define DHT_PIN 21     // what digital pin we're connected to
#define DHT_TYPE DHT11   // DHT 11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float tem = dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.println(String(tem)+" "+String(hum));
  delay(100);
}

void printTemHum(){
  
}
