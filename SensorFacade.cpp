#include "SensorFacade.h"

#include <memory>

SensorManager::SensorManager() : soilMoistureSensor(6)
{

}

void SensorManager::initSensors()
{
  bmp280.init();
  soilMoistureSensor.init();
}
