#include <Arduino.h>
#include <Task.h>
#include "taskWittyCloudLDR.h"


#define pinLDR A0

/*************************************************/
/* Variables for the WittyCloud LDR              */
/*************************************************/
int varLDR;

/*************************************************/
/* Setup for the TaskManager                     */
/*************************************************/
TaskManager taskManager;

// Handles the internal LDR of the WittyCloud Module
void taskHandleGetWittyCloudLDR();
WittyCloudLDRTask taskGetWittyCloudLDR(taskHandleGetWittyCloudLDR, pinLDR, &varLDR, MsToTaskTime(60000));

// Handles the TSL2561 Sensor
void taskHandleGetWittyCloudLDR()
{
  // Other ideas: Push the values to MQTT or switch a blind based on the light intensity
  Serial.print("LDR: ");
  Serial.println(varLDR);
}

/*************************************************/
/* Setup                                         */
/*************************************************/
void setup()   {
	Serial.begin(115200);

  Serial.println("Starting timers");
  // Timer initialization
  taskManager.StartTask(&taskGetWittyCloudLDR);
}

/*************************************************/
/* Loop                                          */
/*************************************************/
void loop() {
  taskManager.Loop();
}
