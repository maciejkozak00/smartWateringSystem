#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <memory>

class TresholdStrategy
{
  float lowTreshold_ = 0;
  float highTreshold_ = 0;
public:
  bool isAboveTreshold(float value) {return value > highTreshold_ && highTreshold_ != 0;};
  bool isBelowTreshold(float value) {return value < lowTreshold_ && highTreshold_ != 0;};
  void setTresholds(float valueLow, float valueHigh) {lowTreshold_ = valueLow; highTreshold_ = valueHigh;};
};

class IStrategyOwner
{
public:
  virtual TresholdStrategy& getItsStrategy() = 0;
};

class ISensor
{
public:
  virtual float readValue() = 0;
  virtual void init() = 0;
  virtual ~ISensor() {}
};

class SoilMoistureSensor : public ISensor, public IStrategyOwner
{
  uint16_t pin_;
  TresholdStrategy tresholdStrategy;
public:
  SoilMoistureSensor(uint16_t pin);
  void init() override;
  float readValue() override;
  TresholdStrategy& getItsStrategy() {return tresholdStrategy;};
};

class PressureSensor : public ISensor
{
  Adafruit_BMP280& bmp_;
public:
  PressureSensor(Adafruit_BMP280& bmp);
  void init() override;
  float readValue() override;
};

class TemperatureSensor : public ISensor, public IStrategyOwner
{
  Adafruit_BMP280& bmp_;
  TresholdStrategy tresholdStrategy;
public:
  TemperatureSensor(Adafruit_BMP280& bmp);
  void init() override;
  float readValue() override;
  TresholdStrategy& getItsStrategy() {return tresholdStrategy;};
};

class TemperatureAndPressureSensor
{
  Adafruit_BMP280 bmp_;

  PressureSensor pressureSensor;
  TemperatureSensor temperatureSensor;
public:
 TemperatureAndPressureSensor();
 void init();
 PressureSensor& getPressureSensor() { return pressureSensor; };
 TemperatureSensor& getTemperatureSensor() { return temperatureSensor; };

};

#endif