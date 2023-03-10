/****************************************************************************************************************************
  AsyncHTTPRequest_ESP32_Ethernet.h

  For ESP32 using LwIP W5500 / ENC28J60 / LAN8720 Ethernet

  AsyncHTTPRequest_ESP32_Ethernet is a library for ESP32 using LwIP W5500 / ENC28J60 / LAN8720 Ethernet

  Based on and modified from asyncHTTPrequest Library (https://github.com/boblemaire/asyncHTTPrequest)

  Built by Khoi Hoang https://github.com/khoih-prog/AsyncHTTPRequest_ESP32_Ethernet
  Licensed under GPLv3 license

  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.
  If not, see <https://www.gnu.org/licenses/>.

  Version: 1.15.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.12.0   K Hoang     16/12/2022 Initial coding to port to ESP32S3 boards using LwIP W5500 or ENC28J60 Ethernet
  1.13.0   K Hoang     21/12/2022 Add support to ESP32S2/C3 boards using LwIP W5500 or ENC28J60 Ethernet
  1.14.0   K Hoang     09/01/2023 Add support to `ESP32` and `ESP32S2/S3/C3` boards using `LwIP W6100 Ethernet`
  1.15.0   K Hoang     01/02/2023 Fix _parseURL() bug
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNC_HTTP_REQUEST_ESP32_ETHERNET_H
#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_H

#include "AsyncHTTPRequest_ESP32_Ethernet.hpp"
#include "AsyncHTTPRequest_ESP32_Ethernet_Impl.h"

#endif    // ASYNC_HTTP_REQUEST_ESP32_ETHERNET_H
