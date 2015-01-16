/* 
 HTML page with a custom color picker that controls an RGB led.
 The html page is located into the "www" folder of this sketch. 
 Open the sketch folder from the top menu: Sketch->Show Sketch Folder

 You can then go to http://arduino.local/sd/color_picker
 to see the output of this sketch, where "arduino" is your 
 board name. 	

 09/2013 - Matteo Loglio (matlo.me)

 yuri - modified Jan 2015 	   
*/

// uncomment to invert RGB values (common anode configuration)
//#define INVERTRGB

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include "wifi_color_picker_functions.h"
#include "yun_ap_time.h"

YunServer server;
String startString;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  alert("ff0000", 100, 3);
  
}

void loop() {
  YunClient client = server.accept();

  if(client) {  
    String command = client.readStringUntil('/');
    
    if (command =="echo") {
      echoResponse(client);
    }
    
    else if (command == "rgb") {
      setLEDState(client);
    }
    
    else if (command == "rgbat") {
      setLEDStateAt(client);
    }
    
    else if (command == "clock") {
      setBoardTime(client);
    }
    
    client.stop();
  }
}




