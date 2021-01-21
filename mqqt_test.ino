



#include <MQTT.h>
#include <MQTTClient.h>
// initialize the library with the numbers of the interface pins
#include <WiFiManager.h>
#include<ESP8266WiFi.h>WiFiClient client
#include<DNSServer.h>
#include<ESP8266WebServer.h>

#include <PubSubClient.h>


const char* mqttServer = "m10.cloudmqtt.com";
const int mqttPort = 15755;
const char* User = "ycyocysl";
const char* Password = "XeskyfA54TOG";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  reconnect();
}
void setup_wifi()
{
  WiFiManager wifimanager;

  Serial.println("Connecting.");
  wifimanager.autoConnect("Device02", "Tengku1234");
  while (WiFi.status() != WL_CONNECTED) {

    Serial.println("Connecting to WiFi..");
    delay(500);
  }
  Serial.println("Connected to the WiFi network");
}
void reconnect()
{
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", User, Password )) {

      Serial.println("connected");
     

      client.publish("Device/1/", "1");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(4000);

    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}



//float getBattery() {
//  pinMode(A0, INPUT);
//  int sensorValue = analogRead(A0);
//  float voltage = sensorValue * (3.3 / 1024.0);
//  return voltage;
//}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected())
  {
    reconnect();

  }

  client.loop();
  delay(1500);

  ESP.deepSleep(20e6);
}
