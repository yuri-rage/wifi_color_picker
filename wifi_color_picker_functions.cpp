#include "wifi_color_picker_functions.h"

rgb ledState = {0, 0, 0};

// really ugly conversion function with no error checking
rgb storgb(String s) {
  rgb val = {0, 0, 0};
  char hex[2] = {s[0], s[1]};
  val.r = (int)strtol(&hex[0], NULL, 16);
  hex[0] = s[2];
  hex[1] = s[3];
  val.g = (int)strtol(&hex[0], NULL, 16);
  hex[0] = s[4];
  hex[1] = s[5];
  val.b = (int)strtol(&hex[0], NULL, 16);
  return val;
}

void setcolor(String color) {
  ledState = storgb(color);
  #ifdef INVERTRGB
    analogWrite(R, 255 - ledState.r);
    delay(AWRITEDELAY);
    analogWrite(G, 255 - ledState.g);
    delay(AWRITEDELAY);
    analogWrite(B, 255 - ledState.b);
  #else
    analogWrite(R, ledState.r);
    delay(AWRITEDELAY);
    analogWrite(G, ledState.g);
    delay(AWRITEDELAY);
    analogWrite(B, ledState.b);
  #endif
}

void alert(String color, int interval, int numTimes) {
  for (int i = 0; i < numTimes; i++) {
    setcolor(color);
    delay(interval);
    setcolor("000000");
    delay(interval);
  }
}

void echoResponse(YunClient client) {
  String command = client.readStringUntil('\r');
  
  if (command == "atq") {
    Process atq;
    String result;
    
    atq.begin("atq");
    atq.run(); // run the command
    // read the output of the command
    while (atq.available() > 0) {
      char c = atq.read();
      //if (c != '\n')
      result += c;
    }
    
    client.println("Raw atq output:<br><pre>");
    client.println(result);
    client.println("</pre>");
    
  }
  
  else if (command == "atrm") {
    Process atrm;
    
    atrm.runShellCommand("atrm $(atq | cut -f1)");
    client.print("Schedule deleted.");
  }
  
  else {
    client.print("Arduino Yun - timestamp:" + getUnixTimeStamp() + " - ledstate:#" + getLEDState());
  }
}

String getLEDState() {
  String result;
  
  if (ledState.r < 0x10) {
    result = "0" + String(ledState.r, HEX);
  } else {
    result = String(ledState.r, HEX);
  }
  
  if (ledState.g < 0x10) {
    result += "0" + String(ledState.g, HEX);
  } else {
    result += String(ledState.g, HEX);
  }

  if (ledState.b < 0x10) {
    result += "0" + String(ledState.b, HEX);
  } else {
    result += String(ledState.b, HEX);
  }
 
  return result;
}

void setLEDState(YunClient client) {
    String color = client.readStringUntil('\r');
    setcolor(color);
    client.print("LED color set to: #" + getLEDState());
    // client.print("<br>" + getTimeStamp()); // useful for debugging
}

void setLEDStateAt(YunClient client) {
  
  // need a Process to access a shell via the Bridge
  Process setStateAt;
  
  String color = client.readStringUntil('/');
  String timeStamp = client.readStringUntil('\r');
  String command = "echo 'curl http://localhost/arduino/rgb/" + color;
  String result;
  
  command += "' | at `date -d @";
  command += timeStamp;
  command += " '+%H:%M %D'`";  
  
  setStateAt.runShellCommand(command);
  
  // format the timestamp to a human readable date for output using the `date` shell command
  setStateAt.begin("date");
  setStateAt.addParameter("-d");
  setStateAt.addParameter("@" + timeStamp);
  setStateAt.addParameter("+%T %D");
  setStateAt.run();
  while (setStateAt.available() > 0) {
    char c = setStateAt.read();
    if (c != '\n')
      result += c;
  }
  client.print("LED color will be set to: #" + color + " at " + result);
}
