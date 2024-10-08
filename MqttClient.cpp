#include "MqttClient.h"

MqttPublisher::MqttPublisher(IMqttMessageRx& rx) : client(wifiClient), itsRx(rx)
{
  topics.reserve(4);
  topics.push_back("garden/pump");
  topics.push_back("garden/temperatureRequest");
  topics.push_back("garden/pressureRequest");
  topics.push_back("garden/soilMoistureRequest");
}

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
  client.setCallback([this](char* topic, byte* message, unsigned int length)
  {
    this->callback(topic, message, length);
  });
}

void MqttPublisher::connect()
{
    if (!client.connected()) {
        Serial.print("Connecting to MQTT broker...");
        while (!client.connected()) {
            if (client.connect("ESP32Client")) 
            {
              for (std::string topic: topics)
              {
                client.subscribe(topic.c_str());
              }
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

void MqttPublisher::loop()
{
  client.loop();
}

void MqttPublisher::handleMessage(char* topic, std::string& message)
{
  if (strcmp(topic, "garden/pump") == 0) 
  {
      itsRx.onPumpChange(message);
  } 
}

void MqttPublisher::callback(char* topic, byte* message, unsigned int length)
{
  std::string messageTemp;
  for (int i = 0; i < length; i++) 
  {
    messageTemp += (char)message[i];
  }
  handleMessage(topic, messageTemp);
}
