#ifndef SENSOR_FACADE_H
#define SENSOR_FACADE_H

#include "Sensor.h"

class SensorManager
{
  TemperatureSensor temperatureSensor;
  SoilMoistureSensor soilMoistureSensor;
  PressureSensor pressureSensor;
  TemperatureAndPressureSensor bmp280;
public:
  SensorManager();
  TemperatureSensor& getTemperatureSensor() { return temperatureSensor; };
  SoilMoistureSensor& getSoilMoistureSensor() { return soilMoistureSensor; };
  PressureSensor& getPressureSensor() { return pressureSensor; };

  void initSensors();
};

#endif