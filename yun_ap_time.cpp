#include "yun_ap_time.h"

bool isSet = false;

bool isTimeSet() {
  return isSet;
}

void setBoardTime(YunClient client) {

  // read time from browser, format: seconds since 1 Jan 1970
  // after point there are milliseconds, eliminated
  String time = client.readStringUntil('.');
  time.trim();
  
  Process setTime;
  // Linux command line to set time
  // command date
  // parameters %s seconds since 1 Jan 1970
  // -s set command
  // @ time in seconds since 1 Jan 1970
  String cmdTimeStrg = "date +%s -s @" + time;
  setTime.runShellCommand(cmdTimeStrg);
  isSet = true;
}

// this function returns a string with the Arduino YUN time stamp
String getTimeStamp() {
  String result;
  Process time;
  
  // Linux command line to get time
  // command date
  // parameters D for the complete date mm/dd/yy
  // T for the time hh:mm:ss
  time.begin("date");
  time.addParameter("+%T %D");
  time.run(); // run the command
  // read the output of the command
  while (time.available() > 0) {
    char c = time.read();
    if (c != '\n')
      result += c;
  }
  return result;
}

String getUnixTimeStamp() {
  String result;
  Process time;
  
  time.begin("date");
  time.addParameter("+%s");
  time.run();
  while (time.available() > 0) {
    char c = time.read();
    if (c != '\n')
    result += c;
  }
  return result;
}

