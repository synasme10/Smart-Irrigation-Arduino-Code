#define BLYNK_PRINT Serial

#include "FirebaseArduino.h" 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define FIREBASE_HOST "smart-irrigation-system-444f8.firebaseio.com" 
#define FIREBASE_AUTH "5V7B0gzRHSL3sP6KSFjvEjVn7E3p4ap8b1utIMe6" 
char auth[] = "aCpoTATMXBkKJTrd6ghqiZib6lxjwTpC";

char ssid[] = "Sujan";
char pass[] = "sujan123";
const int lightPin=D4;
void setup()  
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  Serial.println ();
  Serial.print ("Connected to");
  Serial.print (" ");
  Serial.println (ssid);
  Serial.print ("IP Address is:");
  Serial.println (WiFi.localIP ()); 
  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  Blynk.run();

 int n = Firebase.getInt("light_status");
Serial.print(n);
if (n==1) {
Serial.println("Light ON");
digitalWrite(lightPin,LOW);  
return;
}
else {
Serial.println("Light OFF");
digitalWrite(lightPin,HIGH);  
}
}
