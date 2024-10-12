#ifndef MQTT_MESSAGE_OBSERVER_H
#define MQTT_MESSAGE_OBSERVER_H

class IMqttMessageObserver
{
public:
  virtual void onMessageReceived(const std::string& topic, const std::string& message) = 0;
  virtual ~IMqttMessageObserver() {}
};

#endif
