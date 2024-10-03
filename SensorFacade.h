#ifndef SENSOR_FACADE_H
#define SENSOR_FACADE_H

#include "Sensor.h"

class SensorManager
{
  SoilMoistureSensor soilMoistureSensor;
  TemperatureAndPressureSensor bmp280;
public:
  SensorManager();
  TemperatureSensor& getTemperatureSensor() { return bmp280.getTemperatureSensor(); };
  SoilMoistureSensor& getSoilMoistureSensor() { return soilMoistureSensor; };
  PressureSensor& getPressureSensor() { return bmp280.getPressureSensor(); };


  void initSensors();
};

#endif