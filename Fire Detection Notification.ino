
//Sujan Maharjan
//Blynk Fire alarm notification
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIGGERPIN D2
#define ECHOPIN    D3

BlynkTimer timer;
char auth[] = "aCpoTATMXBkKJTrd6ghqiZib6lxjwTpC"; //Auth code sent via Email
char ssid[] = "Sujan"; //Wifi name
char pass[] = "sujan123";  //Wifi Password
int flag=0;
void notifyOnFire()
{
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Field on fire");
    Blynk.notify("Alert : Field on Fire");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(D1,INPUT_PULLUP);
timer.setInterval(1000L,notifyOnFire);
}
void loop()
{
  Blynk.run();
  timer.run();

 
}
