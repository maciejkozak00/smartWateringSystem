#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

#include "PrivateDefinitions.h"

class IMqttPublisher
{
public:
  virtual void publish(const std::string& topic, const std::string& message) = 0;
  virtual ~IMqttPublisher() {}
};

class MqttPublisher : public IMqttPublisher
{
  WiFiClient wifiClient;
  PubSubClient client;
  std::string ssid = SSID;
  std::string password = WIFI_PASSWORD;
  std::string mqttBrokerIp = MQTT_BROKER_IP;
  int mqttBrokerPort = MQTT_PORT;

  void connect();
public:
  MqttPublisher();
  void init();
  void publish(const std::string& topic, const std::string& message) override;
};


#endif
