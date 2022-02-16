/**
 **************************************************
 *
 * @file        Example6_EnableNMEASentences.ino
 *
 * @brief       Turn on/off various NMEA sentences.
 * By: Nathan Seidle
 * SparkFun Electronics
 * Date: January 3rd, 2019
 * License: MIT. See license file for more information but you can
 * basically do whatever you want with this code.
 *
 * This example shows how to turn on/off the NMEA sentences being output
 * over UART1. We use the I2C interface on the u-blox module for configuration
 * but you won't see any output from this sketch. You'll need to hook up
 * a Serial Basic or other USB to Serial device to UART1 on your u-blox module
 * to see the output.
 *
 * This example turns off all sentences except for the GPGGA and GPVTG sentences.
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

unsigned long lastGNSSsend = 0;

void setup()
{
  Serial.begin(115200); // Serial debug output over USB visible from Arduino IDE
  Serial.println("Example showing how to enable/disable certain NMEA sentences");

  Wire.begin();

  if (myGNSS.begin() == false)
  {
    Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
    while (1)
      ;
  }

  //Disable or enable various NMEA sentences over the UART1 interface
  myGNSS.disableNMEAMessage(UBX_NMEA_GLL, COM_PORT_UART1); //Several of these are on by default on ublox board so let's disable them
  myGNSS.disableNMEAMessage(UBX_NMEA_GSA, COM_PORT_UART1);
  myGNSS.disableNMEAMessage(UBX_NMEA_GSV, COM_PORT_UART1);
  myGNSS.disableNMEAMessage(UBX_NMEA_RMC, COM_PORT_UART1);
  myGNSS.enableNMEAMessage(UBX_NMEA_GGA, COM_PORT_UART1); //Only leaving GGA & VTG enabled at current navigation rate
  myGNSS.enableNMEAMessage(UBX_NMEA_VTG, COM_PORT_UART1);

  //Here's the advanced configure method
  //Some of the other examples in this library enable the PVT message so let's disable it
  myGNSS.configureMessage(UBX_CLASS_NAV, UBX_NAV_PVT, COM_PORT_UART1, 0); //Message Class, ID, and port we want to configure, sendRate of 0 (disable).

  myGNSS.setUART1Output(COM_TYPE_NMEA); //Turn off UBX and RTCM sentences on the UART1 interface

  myGNSS.setSerialRate(57600); //Set UART1 to 57600bps.

  //myGNSS.saveConfiguration(); //Optional: Save these settings to NVM

  Serial.println(F("Messages configured. NMEA now being output over the UART1 port on the u-blox module at 57600bps."));
}

void loop()
{
  if (millis() - lastGNSSsend > 200)
  {
    myGNSS.checkUblox(); //See if new data is available, but we don't want to get NMEA here. Go check UART1.
    lastGNSSsend = millis();
  }
}
