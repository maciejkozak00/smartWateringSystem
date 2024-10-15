#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

#include "PrivateDefinitions.h"
#include "MqttMessageObserver.h"

class IMqttPublisher
{
public:
  virtual void publish(const std::string& topic, const std::string& message) = 0;
  virtual ~IMqttPublisher() {}
};

class IMqttSubscriber
{
public:
  virtual void callback(char* topic, byte* message, unsigned int length) = 0;
  virtual void attach(std::shared_ptr<IMqttMessageObserver> observer) = 0;
  virtual ~IMqttSubscriber() {}
};

class MqttMessageHandler
{
    std::vector<IMqttMessageObserver*> observers;

  void handleMessage(char* topic, std::string& message);
public:
  void callback(char* topic, byte* message, unsigned int length);
  void attach(IMqttMessageObserver* observer);
};

class MqttPublisher : public IMqttPublisher
{
  WiFiClient wifiClient;
  PubSubClient client;
  std::string ssid = SSID;
  std::string password = WIFI_PASSWORD;
  std::string mqttBrokerIp = MQTT_BROKER_IP;
  int mqttBrokerPort = MQTT_PORT;

  std::vector<std::string> topics;
  MqttMessageHandler& messageHandler;
  void connect();
public:
  MqttPublisher(MqttMessageHandler& mqttMessageHandler);
  void init();
  void loop();
  void publish(const std::string& topic, const std::string& message) override;
};

#endif
