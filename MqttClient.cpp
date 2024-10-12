#include "MqttClient.h"

MqttPublisher::MqttPublisher(MqttMessageHandler& mqttMessageHandler) : client(wifiClient), messageHandler(mqttMessageHandler)
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
    this->messageHandler.callback(topic, message, length);
  });
}

void MqttPublisher::connect()
{
    if (!client.connected()) {
        Serial.print("Connecting to MQTT broker...");
        uint8_t retryCount = 0;
        while (!client.connected() && retryCount < 3)
        {
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
        if (retryCount == 3)
        {
          Serial.println("Failed to connect");
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

void MqttMessageHandler::handleMessage(char* topic, std::string& message)
{
  for (auto observer : observers)
  {
    const std::string tempTopic(topic);
    observer->onMessageReceived(tempTopic, message);
  }
}

void MqttMessageHandler::callback(char* topic, byte* message, unsigned int length)
{
  std::string messageTemp;
  for (int i = 0; i < length; i++) 
  {
    messageTemp += (char)message[i];
  }
  handleMessage(topic, messageTemp);
}

void MqttMessageHandler::attach(std::shared_ptr<IMqttMessageObserver> observer)
{
  observers.push_back(observer);
}
