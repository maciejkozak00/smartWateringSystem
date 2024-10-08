#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <Sensor.h>

#include "MqttMessageRx.h"

class IDevice
{
public:
  virtual void init() = 0;
  virtual void on() = 0;
  virtual void off() = 0;
  virtual ~IDevice() {};
};

class Pump : public IDevice
{
  uint16_t pin;
  bool isOn;
public:
  Pump(uint16_t pin) : pin(pin) {};
  void init() override
  {
    Serial.println("Pump init");
    pinMode(pin, OUTPUT);
  }
  void on() override
  {
    if(isOn)
    {
      return;
    }
    Serial.println("Pump on");
    digitalWrite(pin, HIGH);
    isOn = true;
  }
  void off() override
  {
    if(!isOn)
    {
      return;
    }
    Serial.println("Pump off");
    digitalWrite(pin, LOW);
    isOn = false;
  }

};

class DeviceController : public IMqttMessageRx
{
  IDevice& itsDevice_;
  ISensor& itsSensor_;
  IStrategyOwner& itsStrategy_;
public:
  DeviceController(IDevice& device, ISensor& sensor, IStrategyOwner& strategyOwner) : itsDevice_(device), itsSensor_(sensor), itsStrategy_(strategyOwner) {};
  void run()
  {
    Serial.println("Checking device");
    if (itsStrategy_.getItsStrategy().isAboveTreshold(itsSensor_.readValue()))
    {
      Serial.println("Above Strategy!");
      itsDevice_.off();
    }
    if (itsStrategy_.getItsStrategy().isBelowTreshold(itsSensor_.readValue()))
    {
      itsDevice_.on();
    }
  }
  void onPumpChange(std::string& msg)
  {
    bool onOff = (msg == "true");
    onOff ? itsDevice_.on() : itsDevice_.off();
  }
};

#endif
