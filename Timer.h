#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer
{
  unsigned long previousTime;
  unsigned long interval;
  std::function<void()> callback;
public:
  Timer(unsigned long interval, std::function<void()> onTimerElapsed) : interval(interval), previousTime(millis()), callback(onTimerElapsed) {}

  void hasElapsed()
  {
    unsigned long currentTime = millis();
    if (currentTime - previousTime >= interval)
    {
      previousTime = currentTime;
      callback();
      Serial.println("Callback called");
    }
  }
};

#endif