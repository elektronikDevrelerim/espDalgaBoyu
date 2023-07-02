#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Buraya Kendi WiFi Adınız";
const char* password = "Buraya Kendi WiFi Şifreniz";
const char* mqtt_server = "broker.hivemq.com";

#include <Wire.h>
#include "Adafruit_SI1145.h"

WiFiClient espClient;
PubSubClient client(espClient);

#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

Adafruit_SI1145 uv = Adafruit_SI1145();

void SETUP_WIFI() {
  
  delay(10);
  Serial.print("Baglaniyor ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi Baglandi");
  Serial.println("IP Adresi: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[");
  Serial.print(topic);
  Serial.print("] Adlı Topic'den Mesaj Geldi!");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT Broker'a Baglaniyor...");

    String clientId = "ESP8266_DALGABOYU_";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Baglandi!");
    } else {
      Serial.print("Baglanti Basarisiz!, rc=");
      Serial.print(client.state());
      Serial.println("5 Saniye Sonra Yeniden Denenecek!");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  SETUP_WIFI();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  if (!uv.begin())
  {
    Serial.println("SI1145 Bulunamadı!");
    while (1);
  }
  Serial.println("SI1145 Başlatıldı!");
}

char message[50];

void sendSensorData() {
  uint16_t vis = uv.readVisible();
  uint16_t ir = uv.readIR();
  uint16_t uvIndex = uv.readUV();

  float visibleLight = vis * 0.056; // Işık miktarını hesaplamak için kullanılır (istenirse düzenlenebilir).
  float irLight = ir * 0.056; // Kızılötesi ışık miktarını hesaplamak için kullanılır (istenirse düzenlenebilir).
  float uvIntensity = uvIndex / 100.0; // UV yoğunluğunu hesaplamak için kullanılır.

  float wavelength = calculateWavelength(uvIndex); // Dalga boyunu hesaplamak için bir fonksiyon kullanılır.

  Serial.print("Dalga Boyu: ");
  Serial.println(wavelength);
  snprintf(message,50,"%f",wavelength);
  client.publish("dalgaBoyu_ESP8266",message);

  delay(1000);
}
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sendSensorData();

  delay(100);
}

float calculateWavelength(uint16_t uvIndex) {
  // SI1145 sensörü UV yoğunluğunu 16-bit olarak ölçer.
  // Bu kod parçası, ölçülen UV yoğunluğundan dalga boyunu hesaplar.
  // Bu hesaplama, SI1145 datasheet'inde verilen formüllere dayanmaktadır.

  float wavelength;

  if (uvIndex < 227)
  {
    wavelength = 365 - ((float)uvIndex * 1024) / 227;
  }
  else if (uvIndex < 318)
  {
    wavelength = 296 - ((float)(uvIndex - 227) * 1024) / 91;
  }
  else if (uvIndex < 427)
  {
    wavelength = 269 - ((float)(uvIndex - 318) * 1024) / 109;
  }
  else if (uvIndex < 577)
  {
    wavelength = 240 - ((float)(uvIndex - 427) * 1024) / 150;
  }
  else if (uvIndex < 757)
  {
    wavelength = 203 - ((float)(uvIndex - 577) * 1024) / 180;
  }
  else if (uvIndex < 1027)
  {
    wavelength = 158 - ((float)(uvIndex - 757) * 1024) / 270;
  }
  else
  {
    wavelength = 118 - ((float)(uvIndex - 1027) * 1024) / 206;
  }

  return wavelength;
}
