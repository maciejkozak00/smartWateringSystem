#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <array>

#include "PrivateDefinitions.h"
#include "MqttMessageRx.h"

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
  virtual ~IMqttSubscriber() {}
};

class MqttPublisher : public IMqttPublisher, public IMqttSubscriber
{
  WiFiClient wifiClient;
  PubSubClient client;
  std::string ssid = SSID;
  std::string password = WIFI_PASSWORD;
  std::string mqttBrokerIp = MQTT_BROKER_IP;
  int mqttBrokerPort = MQTT_PORT;

  IMqttMessageRx& itsRx;

  std::vector<std::string> topics;

  void connect();
  void handleMessage(char* topic, std::string& message);
public:
  MqttPublisher(IMqttMessageRx& rx);
  void init();
  void loop();
  void publish(const std::string& topic, const std::string& message) override;
  void callback(char* topic, byte* message, unsigned int length) override;
};


#endif
