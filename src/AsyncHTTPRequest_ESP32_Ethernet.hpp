/****************************************************************************************************************************
  AsyncHTTPRequest_ESP32_Ethernet.hpp
  
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

#ifndef ASYNC_HTTP_REQUEST_ESP32_ETHERNET_HPP
#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_HPP

////////////////////////////////////////

#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION            "AsyncHTTPRequest_ESP32_Ethernet v1.15.0"

#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MAJOR      1
#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_MINOR      15
#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_PATCH      0

#define ASYNC_HTTP_REQUEST_ESP32_ETHERNET_VERSION_INT        1015000

////////////////////////////////////////

#include <Arduino.h>

#include "AsyncHTTPRequest_Debug_Generic.h"


////////////////////////////////////////

#if !defined(NOT_SEND_HEADER_AFTER_CONNECTED)
	// Default is false
	#define NOT_SEND_HEADER_AFTER_CONNECTED				false
#endif

////////////////////////////////////////

#ifndef DEBUG_IOTA_PORT
  #define DEBUG_IOTA_PORT Serial
#endif

#ifdef DEBUG_IOTA_HTTP
  #define DEBUG_IOTA_HTTP_SET     true
#else
  #define DEBUG_IOTA_HTTP_SET     false
#endif

////////////////////////////////////////

// KH add
#define SAFE_DELETE(object)         if (object) { delete object;}
#define SAFE_DELETE_ARRAY(object)   if (object) { delete[] object;}

#define ASYNC_HTTP_PREFIX         "HTTP://"
#define ASYNC_HTTP_PORT           80

#define ASYNC_HTTPS_PREFIX        "HTTPS://"
#define ASYNC_HTTPS_PORT          443

////////////////////////////////////////

#include <AsyncTCP.h>

// KH mod
#define MUTEX_LOCK_NR           if (xSemaphoreTakeRecursive(threadLock,portMAX_DELAY) != pdTRUE) { return;}
#define MUTEX_LOCK(returnVal)   if (xSemaphoreTakeRecursive(threadLock,portMAX_DELAY) != pdTRUE) { return returnVal;}

#define _AHTTP_lock       xSemaphoreTakeRecursive(threadLock,portMAX_DELAY)
#define _AHTTP_unlock     xSemaphoreGiveRecursive(threadLock)
  
////////////////////////////////////////

#include <pgmspace.h>

// Merge xbuf
////////////////////////////////////////

struct xseg 
{
  xseg    *next;
  uint8_t data[];
};

////////////////////////////////////////

class xbuf: public Print 
{
  public:

    xbuf(const uint16_t segSize = 64);
    virtual ~xbuf();

    size_t      write(const uint8_t);
    size_t      write(const char*);
    size_t      write(const uint8_t*, const size_t);
    size_t      write(xbuf*, const size_t);
    size_t      write(const String& string);
    size_t      available();
    int         indexOf(const char, const size_t begin = 0);
    int         indexOf(const char*, const size_t begin = 0);
    uint8_t     read();
    size_t      read(uint8_t*, size_t);
    String      readStringUntil(const char);
    String      readStringUntil(const char*);
    String      readString(int);
    
    String      readString() 
    {
      return readString(available());
    }
    
    void        flush();

    uint8_t     peek();
    size_t      peek(uint8_t*, const size_t);
    
    String      peekStringUntil(const char target) 
    {
      return peekString(indexOf(target, 0));
    }
    
    String      peekStringUntil(const char* target) 
    {
      return peekString(indexOf(target, 0));
    }
    
    String      peekString() 
    {
      return peekString(_used);
    }
    
    String      peekString(int);

    /* In addition to the above functions, the following inherited functions from the Print class are available.
    
    size_t printf(const char * format, ...)  __attribute__ ((format (printf, 2, 3)));
    size_t printf_P(PGM_P format, ...) __attribute__((format(printf, 2, 3)));
    size_t print(const __FlashStringHelper *);
    size_t print(const String &);
    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);
    size_t print(const Printable&);
    
    size_t println(const __FlashStringHelper *);
    size_t println(const String &s);
    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
    size_t println(const Printable&);
    size_t println(void);
    */

  protected:

    xseg        *_head;
    xseg        *_tail;
    uint16_t     _used;
    uint16_t     _free;
    uint16_t     _offset;
    uint16_t     _segSize;

    void        addSeg();
    void        remSeg();

};

////////////////////////////////////////

#define DEBUG_HTTP(format,...)  if(_debug){\
    DEBUG_IOTA_PORT.printf("Debug(%3ld): ", millis()-_requestStartTime);\
    DEBUG_IOTA_PORT.printf_P(PSTR(format),##__VA_ARGS__);}

#if !defined(DEFAULT_RX_TIMEOUT)
	#define DEFAULT_RX_TIMEOUT 					3					// Seconds for timeout
#endif

////////////////////////////////////////

#define HTTPCODE_CONNECTION_REFUSED  (-1)
#define HTTPCODE_SEND_HEADER_FAILED  (-2)
#define HTTPCODE_SEND_PAYLOAD_FAILED (-3)
#define HTTPCODE_NOT_CONNECTED       (-4)
#define HTTPCODE_CONNECTION_LOST     (-5)
#define HTTPCODE_NO_STREAM           (-6)
#define HTTPCODE_NO_HTTP_SERVER      (-7)
#define HTTPCODE_TOO_LESS_RAM        (-8)
#define HTTPCODE_ENCODING            (-9)
#define HTTPCODE_STREAM_WRITE        (-10)
#define HTTPCODE_TIMEOUT             (-11)

////////////////////////////////////////

typedef enum
{
  readyStateUnsent      = 0,            // Client created, open not yet called
  readyStateOpened      = 1,            // open() has been called, connected
  readyStateHdrsRecvd   = 2,            // send() called, response headers available
  readyStateLoading     = 3,            // receiving, partial data available
  readyStateDone        = 4             // Request complete, all data available.
} reqStates;

////////////////////////////////////////

class AsyncHTTPRequest
{
  struct header
  {
    header*   next;
    char*     name;
    char*     value;
    
    header(): next(nullptr), name(nullptr), value(nullptr)
    {};
    
    ~header() 
    {
      SAFE_DELETE_ARRAY(name)
      SAFE_DELETE_ARRAY(value)
      SAFE_DELETE(next)
    }
  };

  struct  URL 
  {
    char     *buffer;
    char    *scheme;
    char    *host;
    int     port;
    char    *path;
    char    *query;
    
    URL():  buffer(nullptr), scheme(nullptr), host(nullptr),
            port(80), path(nullptr), query(nullptr)
    {};
      
    ~URL()
    {
      SAFE_DELETE_ARRAY(buffer)
      SAFE_DELETE_ARRAY(scheme)
      SAFE_DELETE_ARRAY(host)
      SAFE_DELETE_ARRAY(path)
      SAFE_DELETE_ARRAY(query)
    }
  };

  typedef std::function<void(void*, AsyncHTTPRequest*, int readyState)> readyStateChangeCB;
  typedef std::function<void(void*, AsyncHTTPRequest*, size_t available)> onDataCB;
    
  ////////////////////////////////////////
    
  public:
    AsyncHTTPRequest();
    ~AsyncHTTPRequest();


    //External functions in typical order of use:
    
    ////////////////////////////////////////

    void        setDebug(bool);                                         // Turn debug message on/off
    bool        debug();                                                // is debug on or off?

    bool        open(const char* /*GET/POST*/, const char* URL);        // Initiate a request
    void        onReadyStateChange(readyStateChangeCB, void* arg = 0);  // Optional event handler for ready state change or you can simply poll readyState()
    void        setTimeout(int);                                        // overide default timeout (seconds)

    void        setReqHeader(const char* name, const char* value);      // add a request header
    void        setReqHeader(const char* name, int32_t value);          // overload to use integer value
    
    void        setReqHeader(const char* name, const __FlashStringHelper* value);
    void        setReqHeader(const __FlashStringHelper *name, const char* value);
    void        setReqHeader(const __FlashStringHelper *name, const __FlashStringHelper* value);
    void        setReqHeader(const __FlashStringHelper *name, int32_t value);

    bool        send();                                                 // Send the request (GET)
    bool        send(const String& body);                               // Send the request (POST)
    bool        send(const char* body);                                 // Send the request (POST)
    bool        send(const uint8_t* buffer, size_t len);                // Send the request (POST) (binary data?)
    bool        send(xbuf* body, size_t len);                           // Send the request (POST) data in an xbuf
    void        abort();                                                // Abort the current operation

    reqStates   readyState();                                           // Return the ready state

    int         respHeaderCount();                                      // Retrieve count of response headers
    char*       respHeaderName(int index);                              // Return header name by index
    char*       respHeaderValue(int index);                             // Return header value by index
    char*       respHeaderValue(const char* name);                      // Return header value by name
    
    bool        respHeaderExists(const char* name);                     // Does header exist by name?
    
    char*       respHeaderValue(const __FlashStringHelper *name);
    bool        respHeaderExists(const __FlashStringHelper *name);
    
    String      headers();                                              // Return all headers as String

    void        onData(onDataCB, void* arg = 0);                        // Notify when min data is available
    size_t      available();                                            // response available
    size_t      responseLength();                                       // indicated response length or sum of chunks to date
    int         responseHTTPcode();                                     // HTTP response code or (negative) error code
    String      responseHTTPString();
    String      responseText();                                         // response (whole* or partial* as string)
    
    char*       responseLongText();                                     // response long (whole* or partial* as string)
    
    size_t      responseRead(uint8_t* buffer, size_t len);              // Read response into buffer
    uint32_t    elapsedTime();                                          // Elapsed time of in progress transaction or last completed (ms)
    String      version();                                              // Version of AsyncHTTPRequest
    
    ////////////////////////////////////////

  private:

    bool _requestReadyToSend;

    typedef enum  
    { 
      HTTPmethodGET, 
      HTTPmethodPOST, 
      HTTPmethodPUT, 
      HTTPmethodPATCH, 
      HTTPmethodDELETE, 
      HTTPmethodHEAD, 
      HTTPmethodMAX 
    } HTTPmethod;
    
    HTTPmethod _HTTPmethod;
    
    const char* _HTTPmethodStringwithSpace[HTTPmethodMAX] = {"GET ", "POST ", "PUT ", "PATCH ", "DELETE ", "HEAD "};
    //////
    
    reqStates       _readyState;

    int16_t         _HTTPcode;                  // HTTP response code or (negative) exception code
    bool            _chunked;                   // Processing chunked response
    bool            _debug;                     // Debug state
    uint32_t        _timeout;                   // Default or user overide RxTimeout in seconds
    uint32_t        _lastActivity;              // Time of last activity
    uint32_t        _requestStartTime;          // Time last open() issued
    uint32_t        _requestEndTime;            // Time of last disconnect
    URL*            _URL;                       // -> URL data structure
    char*           _connectedHost;             // Host when connected
    int             _connectedPort;             // Port when connected
    AsyncClient*    _client;                    // ESPAsyncTCP AsyncClient instance
    size_t          _contentLength;             // content-length header value or sum of chunk headers
    size_t          _contentRead;               // number of bytes retrieved by user since last open()
    readyStateChangeCB  _readyStateChangeCB;    // optional callback for readyState change
    void*           _readyStateChangeCBarg;     // associated user argument
    onDataCB        _onDataCB;                  // optional callback when data received
    void*           _onDataCBarg;               // associated user argument

    SemaphoreHandle_t threadLock;

    // request and response String buffers and header list (same queue for request and response).

    xbuf*       _request;                       // Tx data buffer
    xbuf*       _response;                      // Rx data buffer for headers
    xbuf*       _chunks;                        // First stage for chunked response
    header*     _headers;                       // request or (readyState > readyStateHdrsRcvd) response headers

    // Protected functions

    header*     _addHeader(const char*, const char*);
    header*     _getHeader(const char*);
    header*     _getHeader(int);
    bool        _buildRequest();
    bool        _parseURL(const char*);
    bool        _parseURL(const String& url);
    void        _processChunks();
    bool        _connect();
    size_t      _send();
    void        _setReadyState(reqStates);
    
    char*       _charstar(const __FlashStringHelper *str);

    // callbacks

    void        _onConnect(AsyncClient*);
    void        _onDisconnect(AsyncClient*);
    void        _onData(void*, size_t);
    void        _onError(AsyncClient*, int8_t);
    void        _onPoll(AsyncClient*);
    bool        _collectHeaders();
};

////////////////////////////////////////

#endif    // ASYNC_HTTP_REQUEST_ESP32_ETHERNET_HPP
