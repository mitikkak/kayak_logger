
#include "Loop.h"
#include "Arduino.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"
#include "TiltReport.h"
#include "GpsReport.h"

int hallSwitchState = 0;
bool activity = false;
int loggingOn = 0;
unsigned long prevTimeActivityChecked = 0;
const unsigned long activityTimeCheckThreshold = 2000;
bool isActive()
{
   hallSwitchState = analogRead(HALL_SWITCH);
   const int activityLowThreshold = 750;
   const int activityHighThreshold = 850;
   if ((hallSwitchState < activityLowThreshold) || (hallSwitchState > activityHighThreshold) )
   {
      return activity ? false : true;
   }
   return activity;
}
void loop()
{
  unsigned long timeNow = millis();
#ifdef HALL_SWITCH_ON
  if (timeNow > (prevTimeActivityChecked + activityTimeCheckThreshold))
  {
    activity = isActive();
    prevTimeActivityChecked = timeNow;
  }

  if (!activity)
  {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print(hallSwitchState);
     delay(100);
     return;
  }
#endif
#ifdef ACCELEROMETER_ON
  if (timeNow - prevTimeTiltHandled > TILT_MEASUREMENT_PERIOD)
  {
    TiltReport tiltReport(accMeter);
    StatusIndicator::Status const reportStatus = tiltReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeTiltHandled = timeNow;
  }
#endif
#ifdef GPS_ON
  GpsReport gpsReport(gps);
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {
    StatusIndicator::Status const reportStatus = gpsReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
    SpeedMessage msg = gpsReport.speedMessage();
    if (gpsReport.HDOP < HDOP_UNRELIABLE)
    {
        averageSpeed.add(msg.value);
        StatusIndicator::Status const averageSpeedStatus = averageSpeed.write(logger);
        statusIndicator.newEvent(averageSpeedStatus, timeNow);
        distance_.add(msg.value);
        StatusIndicator::Status const distanceStatus = distance_.write(logger);
        statusIndicator.newEvent(distanceStatus, timeNow);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(gpsReport.HDOP);
    lcd.print("|");
    lcd.print(loggingOn);
    lcd.setCursor(0, 1);
    lcd.print(msg.value, 3);
    lcd.print("|");
    lcd.print(averageSpeed.value(), 3);
    lcd.print("|");
    lcd.print(distance_.value(), 3);
    lcd.setCursor(0, 2);
    lcd.print(gpsReport.hour());
    lcd.print(":");
    lcd.print(gpsReport.minute());
    lcd.print(":");
    lcd.print(gpsReport.second());
    lcd.print("|");
    lcd.print(hallSwitchState);
  }
  else
  {
      gpsReport.readGps();
  }
#endif
  statusIndicator.continueCurrentState(timeNow);
}
