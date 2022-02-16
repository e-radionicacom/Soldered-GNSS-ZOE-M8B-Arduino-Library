/**
 **************************************************
 *
 * @file        Example8_GetProtocolVersion.ino
 *
 * @brief       Reading the protocol version of a u-blox module
 * By: Nathan Seidle
 * SparkFun Electronics
 * Date: January 3rd, 2019
 * License: MIT. See license file for more information but you can
 * basically do whatever you want with this code.
 *
 * This example shows how to query a u-blox module for its protocol version.
 *
 * Various modules have various protocol version. We've seen v18 up to v27. Depending
 * on the protocol version there are different commands available. This is a handy
 * way to predict which commands will or won't work.
 *
 * Leave NMEA parsing behind. Now you can simply ask the module for the datums you want!
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

#include <Wire.h> //Needed for I2C to GNSS

#include <GNSS-ZOE-M8B-SOLDERED.h>
SFE_UBLOX_GNSS myGNSS;

long lastTime = 0; //Simple local timer. Limits amount if I2C traffic to u-blox module.

void setup()
{
  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal
  Serial.println("SparkFun u-blox Example");

  Wire.begin();

  if (myGNSS.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  Serial.print(F("Version: "));
  byte versionHigh = myGNSS.getProtocolVersionHigh();
  Serial.print(versionHigh);
  Serial.print(".");
  byte versionLow = myGNSS.getProtocolVersionLow();
  Serial.print(versionLow);
}

void loop()
{
  //Do nothing
}
