#ifndef SENSORS_LOGGER_H
#define SENSORS_LOGGER_H

#include <map>
#include <string>
#include <Arduino.h>

#include "Sensor.h"

class SensorsLogger
{
  std::map<std::string, ISensor*> sensors;
public:
  void addSensor(const std::string& key, ISensor* sensor)
  {
    sensors[key] = sensor;
  }
  void printAllValues()
  {
    for (const auto& [sensorName, sensor]: sensors)
    {
      Serial.print(sensorName.c_str());
      Serial.print(": ");
      Serial.println(sensor->readValue());
    }
  }
};

#endif