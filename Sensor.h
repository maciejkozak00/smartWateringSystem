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
  TresholdStrategy() = default;

  bool isAboveTreshold(float value);
  bool isBelowTreshold(float value);
  void setTresholdLow(float valueLow);
  void setTresholdHigh(float valueHigh);
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
  TresholdStrategy itsTresholdStrategy;
public:
  SoilMoistureSensor(uint16_t pin);
  void init() override;
  float readValue() override;
  TresholdStrategy& getItsStrategy() {return itsTresholdStrategy;};
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