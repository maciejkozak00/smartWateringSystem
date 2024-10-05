#include "MqttClient.h"

MqttPublisher::MqttPublisher() : client(wifiClient) {}

void MqttPublisher::init()
{
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi");
  uint8_t retryCounter = 5;
  while (WiFi.status() != WL_CONNECTED && retryCounter)
  {
    delay(1000);
    Serial.print(".");
  }
  client.setServer(mqttBrokerIp.c_str(), mqttBrokerPort);
}

void MqttPublisher::connect()
{
    if (!client.connected()) {
        Serial.print("Connecting to MQTT broker...");
        while (!client.connected()) {
            if (client.connect("ESP32Client")) {
                Serial.println("connected");
            } else {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                delay(2000);
            }
        }
    }
}

void MqttPublisher::publish(const std::string& topic, const std::string& message)
{
    if (!client.connected()) {
        connect();
    }
    client.publish(topic.c_str(), message.c_str());
}
