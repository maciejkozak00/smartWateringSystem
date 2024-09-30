#include "SensorFacade.h"

#include <memory>

SensorManager::SensorManager() : temperatureSensor(bmp280.getTemperatureSensor()), soilMoistureSensor(soilMoistureSensor), pressureSensor(bmp280.getPressureSensor())
{

}

void SensorManager::initSensors()
{
  bmp280.init();
  soilMoistureSensor.init();
}
