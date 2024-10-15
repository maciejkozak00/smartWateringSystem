#include "SensorFacade.h"

#include <memory>

SensorManager::SensorManager(MqttPublisher& mqttPublisher) : soilMoistureSensor(6), mqttPublisher(mqttPublisher)
{

}

void SensorManager::initSensors()
{
  bmp280.init();
  soilMoistureSensor.init();
}
  
float SensorManager::getTemperature()
{
  return getTemperatureSensor().readValue();
}
  
float SensorManager::getPressure()
{
  return getPressureSensor().readValue();
}
  
float SensorManager::getSoilMoisture()
{
  return getSoilMoistureSensor().readValue();
}

void SensorManager::onMessageReceived(const std::string& topic, const std::string& message)
{
  Serial.print("New request:");
  Serial.println(topic.c_str());
  if (topic == "garden/temperatureRequest")
  {
    mqttPublisher.publish("garden/temperature", std::to_string(getTemperature()));
  }

  if (topic == "garden/pressureRequest")
  {
    mqttPublisher.publish("garden/pressure", std::to_string(getPressure()));
  }

  if (topic == "garden/soilMoistureRequest")
  {
    mqttPublisher.publish("garden/soilMoisture", std::to_string(getSoilMoisture()));
  }

  if (topic == "garden/setSoilMoistureTresholdLow")
  {
    getSoilMoistureSensor().getItsStrategy().setTresholdLow(std::stoi(message));
    Serial.print("Treshold Low:");
    Serial.println(message.c_str());
  }

  if (topic == "garden/setSoilMoistureTresholdHigh")
  {
    getSoilMoistureSensor().getItsStrategy().setTresholdHigh(std::stoi(message));
        Serial.print("Treshold High:");
    Serial.println(message.c_str());
  }
}
