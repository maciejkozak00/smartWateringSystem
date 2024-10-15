#ifndef SENSOR_FACADE_H
#define SENSOR_FACADE_H

#include "Sensor.h"
#include "MqttMessageObserver.h"
#include "MqttClient.h" 

class SensorManager : public IMqttMessageObserver
{
  SoilMoistureSensor soilMoistureSensor;
  TemperatureAndPressureSensor bmp280 {};

  MqttPublisher& mqttPublisher;
public:
  SensorManager(MqttPublisher& mqttPublisher);
  TemperatureSensor& getTemperatureSensor() { return bmp280.getTemperatureSensor(); };
  SoilMoistureSensor& getSoilMoistureSensor() { return soilMoistureSensor; };
  PressureSensor& getPressureSensor() { return bmp280.getPressureSensor(); };

  float getTemperature();
  float getPressure();
  float getSoilMoisture();

  void onMessageReceived(const std::string& topic, const std::string& message);

  void initSensors();
};

#endif