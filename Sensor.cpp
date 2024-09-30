#include "esp32-hal-adc.h"
#include "Sensor.h"
#include "Arduino.h"

SoilMoistureSensor::SoilMoistureSensor(uint16_t pin) : pin_(pin)
{

}

void SoilMoistureSensor::init()
{

}

float SoilMoistureSensor::readValue()
{
  return analogRead(pin_);
}

TemperatureSensor::TemperatureSensor(Adafruit_BMP280& bmp) : bmp_(bmp)
{

}

void TemperatureSensor::init() {}

float TemperatureSensor::readValue()
{
  return bmp_.readTemperature();
}

PressureSensor::PressureSensor(Adafruit_BMP280& bmp) : bmp_(bmp)
{

}

void PressureSensor::init() {}

float PressureSensor::readValue()
{
  return bmp_.readPressure() / 100.0f; //convert Pa to hPa
}

TemperatureAndPressureSensor::TemperatureAndPressureSensor() : pressureSensor(bmp_), temperatureSensor(bmp_)
{

}

void TemperatureAndPressureSensor::init()
{
  Wire.begin(4, 5);
  bool started = false;
  for (uint8_t retryCounter = 0; retryCounter < 3; ++retryCounter)
  {
    Serial.print("Starting BMP280 (Temperature and pressure sensor): ");
    Serial.print(retryCounter+1);
    Serial.println("/3");
    if (bmp_.begin(0x76))
    {
      bmp_.setSampling( Adafruit_BMP280::MODE_NORMAL,
                        Adafruit_BMP280::SAMPLING_X2,
                        Adafruit_BMP280::SAMPLING_X16,
                        Adafruit_BMP280::FILTER_X16,
                        Adafruit_BMP280::STANDBY_MS_500);
      break;
    }
    Serial.println("Failed to init BMP280");
    delay(1000);
  }
}
