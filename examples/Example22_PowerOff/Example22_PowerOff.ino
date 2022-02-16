/**
 **************************************************
 *
 * @file        Example22_PowerOff.ino
 *
 * @brief       Powering off a ublox GNSS module
 * By: bjorn
 * unsurv.org
 * Date: July 20th, 2020
 * License: MIT. See license file for more information but you can
 * basically do whatever you want with this code.
 *
 * This example shows you how to turn off the ublox module to lower the power consumption.
 * There are two functions: one just specifies a duration in milliseconds the other also specifies a pin on the GNSS device to wake it up with.
 * By driving a voltage from LOW to HIGH or HIGH to LOW on the chosen module pin you wake the device back up.
 * Note: Doing so on the INT0 pin when using the regular powerOff(durationInMs) function will wake the device anyway. (tested on SAM-M8Q)
 * Note: While powered off, you should not query the device for data or it might wake up. This can be used to wake the device but is not recommended.
 *       Works best when also putting your microcontroller to sleep.
 *
 * Feel like supporting open source hardware?
 * Buy a board from SparkFun!
 * ZED-F9P RTK2: https://www.sparkfun.com/products/15136
 * NEO-M8P RTK: https://www.sparkfun.com/products/15005
 * SAM-M8Q: https://www.sparkfun.com/products/15106
 *
 * Hardware Connections:
 * Connect the U-Blox serial port to Serial1
 * If you're using a Uno or don't have a 2nd serial port (Serial1), use SoftwareSerial instead (see below)
 * Open the serial monitor at 115200 baud to see the output
 *
 *
 *              product : www.soldered.com/333099
 *              
 *              Modified by soldered.com
 * 
 * @authors     SparkFun
 ***************************************************/

#include <GNSS-ZOE-M8B-SOLDERED.h>
SFE_UBLOX_GNSS myGNSS;

// define a digital pin capable of driving HIGH and LOW
#define WAKEUP_PIN 5

// Possible GNSS interrupt pins for powerOffWithInterrupt are:
// VAL_RXM_PMREQ_WAKEUPSOURCE_UARTRX  = uartrx
// VAL_RXM_PMREQ_WAKEUPSOURCE_EXTINT0 = extint0 (default)
// VAL_RXM_PMREQ_WAKEUPSOURCE_EXTINT1 = extint1
// VAL_RXM_PMREQ_WAKEUPSOURCE_SPICS   = spics
// These values can be or'd (|) together to enable interrupts on multiple pins

void wakeUp() {

  Serial.print("-- waking up module via pin " + String(WAKEUP_PIN));
  Serial.println(" on your microcontroller --");

  digitalWrite(WAKEUP_PIN, LOW);
  delay(1000);
  digitalWrite(WAKEUP_PIN, HIGH);
  delay(1000);
  digitalWrite(WAKEUP_PIN, LOW);
}


void setup() {

  pinMode(WAKEUP_PIN, OUTPUT);
  digitalWrite(WAKEUP_PIN, LOW);

  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal
  Serial.println("SparkFun u-blox Example");

  Wire.begin();

  //myGNSS.enableDebugging(); // Enable debug messages

  if (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  // Powering off for 20s, you should see the power consumption drop.
  Serial.println("-- Powering off module for 20s --");

  myGNSS.powerOff(20000);
  //myGNSS.powerOffWithInterrupt(20000, VAL_RXM_PMREQ_WAKEUPSOURCE_EXTINT0);

  delay(10000);

  // After 10 seconds wake the device via the specified pin on your microcontroller and module.
  wakeUp();
}

void loop() {
  //Do nothing
}
