/****************************************************************************************************************************
  multiFileProject.ino
  For ESP32 using LwIP W5500 / ENC28J60 / LAN8720 Ethernet

  AsyncHTTPRequest_ESP32_Ethernet is a library for ESP32 using LwIP W5500 / ENC28J60 / LAN8720 Ethernet

  Based on and modified from asyncHTTPrequest Library (https://github.com/boblemaire/asyncHTTPrequest)

  Built by Khoi Hoang https://github.com/khoih-prog/AsyncHTTPRequest_ESP32_Ethernet
  Licensed under GPLv3 license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !defined(ESP32)
  #error This code is intended to run on the ESP32 using LwIP Ethernet W5500 or ENC28J60 ! Please check your Tools->Board setting.
#endif

#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MIN_TARGET      "AsyncHTTPRequest_ESP32_Ethernet v1.14.0"
#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MIN             1014000

#include "multiFileProject.h"

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncHTTPRequest_ESP32_Ethernet.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  Serial.println("\nStart multiFileProject");
  Serial.println(ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION);

#if defined(ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MIN)

  if (ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_INT < ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MIN_TARGET);
  }

#endif
}

void loop()
{
  // put your main code here, to run repeatedly:
}
