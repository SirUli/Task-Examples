#include <Arduino.h>
#include <Task.h>
#include "taskTSL2561.h"

#define pinSDA 2 // GPIO0 on ESP-01 module / GPIO4 on ESP-12E
#define pinSCL 5 // GPIO2 on ESP-01 module / GPIO5 on ESP-12E

/*************************************************/
/* Variables for Light Sensor TSL2561            */
/*************************************************/
int varLux;

/*************************************************/
/* Setup for the TaskManager                     */
/*************************************************/
TaskManager taskManager;

// Handles the retrival of the TSL2561 Sensor data
void taskHandleGetTSL2561();
TSL2561Task taskGetTSL2561(taskHandleGetTSL2561, pinSDA, pinSCL, &varLux, MsToTaskTime(20000));

// Handles the TSL2561 Sensor
void taskHandleGetTSL2561()
{
  // Other ideas: Push the values to MQTT or switch a blind based on the light intensity
  Serial.print("Lux: ");
  Serial.println(varLux);
}

/*************************************************/
/* Setup                                         */
/*************************************************/
void setup()   {
	Serial.begin(115200);

  Serial.println("Starting timers");
  // Timer initialization
  taskManager.StartTask(&taskGetTSL2561);
}

/*************************************************/
/* Loop                                          */
/*************************************************/
void loop() {
  taskManager.Loop();
}
