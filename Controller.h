#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Sensor.h"
#include "SensorFacade.h"
#include "SensorsLogger.h"
#include "Timer.h"
#include "Device.h"
#include "MqttClient.h"

class Controller
{
  MqttPublisher mqttPublisher;
  MqttMessageHandler mqttMessageHandler;
  SensorManager manager;
  SensorsLogger logger;
  Pump pump;
  DeviceController deviceController;

  std::vector<Timer> timers;
public:
  Controller();
  void initDevice();
  void run();
};

#endif