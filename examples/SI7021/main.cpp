#include <Arduino.h>
#include <Task.h>
#include "taskSI7021.h"

#define pinSDA 2 // GPIO0 on ESP-01 module / GPIO4 on ESP-12E
#define pinSCL 5 // GPIO2 on ESP-01 module / GPIO5 on ESP-12E

/*************************************************/
/* Settings for Humidity & Temperature           */
/* Measurements via SI7021                       */
/*************************************************/
float varTemperature;
int varHumidity;

/*************************************************/
/* Setup for the TaskManager                     */
/*************************************************/
TaskManager taskManager;

// Handles the retrival of the SI7021 Sensor data
void taskHandleGetSI7021();
SI7021Task taskGetSI7021(taskHandleGetSI7021, pinSDA, pinSCL, &varTemperature, &varHumidity, MsToTaskTime(20000));

// Handles the SI7021 Sensor
void taskHandleGetSI7021()
{
  // Other ideas: Push the values to MQTT or switch a ventilator based on temperature & humidity
  Serial.print("Temperature: ");
  Serial.println(varTemperature);

  Serial.print("Humidity: ");
  Serial.println(varHumidity);
}

/*************************************************/
/* Setup                                         */
/*************************************************/
void setup()   {
	Serial.begin(115200);

  Serial.println("Starting timers");
  // Timer initialization
  taskManager.StartTask(&taskGetSI7021);
}

/*************************************************/
/* Loop                                          */
/*************************************************/
void loop() {
  taskManager.Loop();
}
