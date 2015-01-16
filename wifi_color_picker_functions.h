#ifndef wifi_color_picker_functions_h
#define wifi_color_picker_functions_h

#include <Arduino.h>
#include <YunClient.h>
#include <Bridge.h>
#include "yun_ap_time.h"

struct rgb {
  int r;
  int g;
  int b;
};

//rgb led hooked up as follows:
#define R 9
#define G 10
#define B 11

// delay between analog writes (10-25ms seems to help keep things stable)
#define AWRITEDELAY 10

// really ugly conversion function with no error checking
rgb storgb(String s);

// sets LED color based on HEX formatted string (e.g., 0f0f0f
void setcolor(String color);

// flashes leds
void alert(String color, int interval, int numTimes);

// expects "echo", "atq", or "atrm" and then:
// identify the controller to the client and return current led state
// or show atq output - for coding simplicity, it's a raw shell dump
//   a custom script on the Yun's Linux system could afford prettier output
// or clear the atq (queue) via atrm - ugly/forced removal of all jobs
//   assumes the Linux system is not using "at" for any other purpose
void echoResponse(YunClient client);

// returns a HEX formatted string corresponding to the color previously set
String getLEDState();

// set led color based on client input (assumes HEX formatted string as the next data available)
// e.g., "ffffff"
void setLEDState(YunClient client);

// set led color based on client input
// (assumes HEX formatted string and Unix time stamp are the next data available)
// e.g., "ffffff/1421441616"
void setLEDStateAt(YunClient client);

#endif
