
#define TRIGGER D3
#define ECHO    D4
#define LED     D2
//Blynk Fire Alert system
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

#define FIREBASE_HOST "smart-irrigation-system-444f8.firebaseio.com"
#define FIREBASE_AUTH "5V7B0gzRHSL3sP6KSFjvEjVn7E3p4ap8b1utIMe6"
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
WiFi.begin(ssid, pass);
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
   Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
Blynk.begin(auth, ssid, pass);
pinMode(D1,INPUT_PULLUP);
timer.setInterval(1000L,notifyOnFire); 

//part of distance
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LED, OUTPUT);
}
void loop()
{
  Blynk.run();
  timer.run();

  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

if (distance>=10)
  {
 Serial.print("water needs to fill");
digitalWrite(LED, HIGH); // turn the LED on.
 // wait for 1 second.
  }
  else
{
  Serial.print(distance);
  digitalWrite(LED, LOW);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
            // wait for 1 second.
//  digitalWrite(enable2, LOW); 
  }
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  Firebase.setInt("distance",distance);
  delay(1000);
}
