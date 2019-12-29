

#include "ESP8266WiFi.h" 
#include "FirebaseArduino.h" 
#include "DHT.h" 

#define FIREBASE_HOST "smart-irrigation-system-444f8.firebaseio.com" 
#define FIREBASE_AUTH "5V7B0gzRHSL3sP6KSFjvEjVn7E3p4ap8b1utIMe6" 

#define WIFI_SSID "Sujan" 
#define WIFI_PASSWORD "sujan123"
#define DHTPIN D5 
#define DHTTYPE DHT11 
DHT dht (DHTPIN, DHTTYPE);
#define SOIL      600
#define WET_SOIL      500
#define TEMP          30
#define HUMIDITY      75

const int moisturePin = A0;           
const int motorPin = D0;

void setup () {
  Serial.begin (9600);
  delay (1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD); 
  Serial.print ("Connecting to");
  Serial.print (WIFI_SSID);
  while (WiFi.status()!= WL_CONNECTED) {
    Serial.print (".");
    delay (500);
  }
  Serial.println ();
  Serial.print ("Connected to");
  Serial.print (" ");
  Serial.println (WIFI_SSID);
  Serial.print ("IP Address is:");
  Serial.println (WiFi.localIP ()); 
  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH); 
  dht.begin (); 
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW); 
  pinMode (moisturePin,INPUT);
  Serial.begin(9600);

  Firebase.set("pump_status", 0);
  
}

int n=0;
void loop () 
{
 int moisture=analogRead(A0);
//int moisture=500;
 Serial.println("moisture");
  Serial.println(moisture);
  delay(2000);

  
  float h = dht.readHumidity ();  //Reading temperature or humidity takes about 250 millisecond
  float t = dht.readTemperature ();  //Reading temperature as Celsius 
   
  if (isnan (h) || isnan (t)) {      //check if any reads failed and exist early to try again.
    Serial.println ("Failed to read from DHT sensor!");
    return;
  }  
  Serial.print ("Humidity: "); Serial.print (h);
  String firebaseHumid = String (h) + String ("%");   //convert integer humidity to string humidity
  Serial.print ("% ; Temperature: "); Serial.print (t); Serial.println ("°C");
  String firebaseTemp = String (t) + String ("°C"); 
  delay (5000);
 if (moisture < SOIL) {
  digitalWrite(motorPin, HIGH);         // tun on motor 
}
  if (800 > SOIL) {
  digitalWrite(motorPin, LOW);          // turn off mottor
}

 if (t < TEMP) {                     //if temperature is above 30 high
  digitalWrite(motorPin, HIGH);         // tun on motor
}

if (t > TEMP) {
  digitalWrite(motorPin, LOW);          // turn off mottor
}

 if (h < HUMIDITY) {                     //if temperature is above 30 high
  digitalWrite(motorPin, HIGH);         // tun on motor
}

if (h > HUMIDITY) {
  digitalWrite(motorPin, LOW);          // turn off mottor
}

n = Firebase.getInt("pump_status");
Serial.print(n);
if (n==1) {
Serial.println("PUMP ON");
digitalWrite(motorPin,LOW);  
return;
}
else {
Serial.println("PUMP OFF");
digitalWrite(motorPin,HIGH);  
}

  Firebase.setInt ("soilmoisture",moisture);
  Firebase.setString ("humidity", firebaseHumid); 
  Firebase.setString ("temperature", firebaseTemp);   
   Firebase.pushString ("humiditydata", firebaseHumid); 
  Firebase.pushString ("temperaturedata", firebaseTemp);   
} 
