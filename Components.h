
#include "PreCompilerOptions.h"
#include "PinLayout.h"

#ifdef UNIT_TEST
 #include "FakeSdFat.h"
#else
 #if defined ESP8266 || defined ESP32
  #include "SD.h"
 #else
  #include "SdFat.h"
 #endif
#endif
#include "fstream_headers.h"
#include "Logger.h"

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
extern Adafruit_PCD8544 lcd;

#ifdef ACCELEROMETER_ON
 #include "ADXL345.h"
 extern ADXL345 accMeter;
#endif

#if defined ESP8266
typedef struct SDClass SD_TYPE;
#elif defined ESP32
typedef struct fs::SDFS SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif
extern SD_TYPE sdFat;
extern Logger logger;
extern StatusIndicator statusIndicator;
#ifdef GPS_ON
 #ifdef UNIT_TEST
  #include "FakeSoftwareSerial.h"
  #include "FakeTinyGPS.h"
 #else
  #include "TinyGPS.h"
 #endif
 extern TinyGPS gps;
#endif
extern unsigned long prevTimeTiltHandled;
extern unsigned long prevTimeGpsHandled;
#include "AverageSpeed.h"
extern AverageSpeed averageSpeed;
#include "Distance.h"
extern Distance distance_;
