
#include <ESP8266WiFi.h>           // Header file for Wifi Module 
#include <BlynkSimpleEsp8266.h>  // header file for blynk 
#include <RBDdimmer.h>           // header file for robodyn dimmer

char auth[] = "y77QpXu7Fn1sYoKQpQrJq0GIgx_jd14u";  // blynk auth key 

char ssid[] = "Botics";   // Wifi Name
char pass[] = "king@321";  // Wifi Password

#define outputPin  D2  // PWM pin for dimmer
#define zerocross  D1 // for boards with CHANGEBLE input pins

dimmerLamp dimmer(outputPin, zerocross); //initialase port for dimmer for ESP8266, ESP32, Arduino due boards

int outVal = 0; // Intialisation value for dimmer
int dim_val; // dimmer value to dim the appliance

void setup()
{
  Serial.begin(9600); // begin serial communication
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE)
  Blynk.begin(auth, ssid, pass); // begin blynk server
}

void loop()
{
  Blynk.run(); // Run blynk server
}


BLYNK_WRITE(V0)  {  // Set to your virtual pin  
  outVal = param.asInt(); // Get State of Virtual Button
  dim_val = map(outVal, 0, 1023, 0, 100); // mapped the value for dimmer
  dimmer.setPower(dim_val);               // Set dimmer power
  Blynk.virtualWrite(V1, dim_val); //sending to Blynk
}
