// some functions to manipulate Yun's time using REST
// modified from:
// https://physicslight.wordpress.com/2014/07/02/arduino-yun-time-synchronization/

#ifndef yun_ap_time_h
#define yun_ap_time_h

#include <Arduino.h>
#include <Bridge.h>
#include <YunClient.h>

// return whether or not the time has been set by this sketch
bool isTimeSet();

// set Yun's Linux time based on client input (assumes the next available data is a Unix timestamp)
void setBoardTime(YunClient client);

// returns a string with the Yun's date/timestamp in human readable format
String getTimeStamp();

// returns a string with the Yun's Unix timestamp
String getUnixTimeStamp();

#endif
