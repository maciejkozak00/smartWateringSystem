#ifndef MQTT_MESSAGE_RX_H
#define MQTT_MESSAGE_RX_H

class IMqttMessageRx
{
public:
  virtual void onPumpChange(std::string& msg) = 0;
};

#endif
