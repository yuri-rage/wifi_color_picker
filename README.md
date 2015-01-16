##wifi_color_picker##

Control an RGB LED strip with the Arduino Yun.

I created this project because I added high intensity RGB LED exterior lighting to my RV (a "Cyclone" model, hence the code references), and the supplied RF controller conked out after only a week's use.  The strip was permanently installed and still worked with 12VDC applied.  In order to preserve remote control, I added an Arduino Yun and some transistors to control 12VDC using PWM output from the Arduino.  The result is a rather flexible remote control that includes rudimentary scheduling for automatic control.  The webpage includes some optimization for mobile devices.

Code documentation is sparse in some places, but you should get a feel for the intent by loading the index.html webpage in the www directory and browsing the wifi_color_picker.ino sketch.

PWM output is on pins 9, 10, and 11 for R, G, and B, respectively.  I used TIP3055 transistors to sink the 12VDC control current to ground.  100ohm resistors between the PWM pins and transistor bases work to saturate (or nearly saturate) the transistors without overloading the Atmega chip.  Power is supplied via a cigarette lighter-style power port and USB-micro cell phone charger.

The webpage communicates with the Yun via REST calls.  Set REST to open access on the Yun configuration page.  Behavior should be identical whether then Yun is in access point or client mode.  Because some of the REST calls invoke shell commands as root, this code cannot be considered secure by any means - user beware.

Enjoy!

