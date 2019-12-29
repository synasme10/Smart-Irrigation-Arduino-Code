#include <DHT.h>
#include "SPI.h"
#include "TFT_22_ILI9225.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT22


#define TFT_RST A4
#define TFT_RS  A3
#define TFT_CS  A5  // SS
#define TFT_SDI A2  // MOSI
#define TFT_CLK A1  // SCK
#define TFT_LED 0   // 0 if wired to +5V directly

// Use software SPI (slower)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED);
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

float hum;  //Stores humidity value
float temp; //Stores temperature 

void setup() 
{
  Serial.begin(9600);
  tft.begin();
  dht.begin();  
}

void loop() 
{ 
    float convertedF = 0.00;
    float convertedK = 0.00;
    float convertedR = 0.00;
    
    
    hum = dht.readHumidity();
    temp= dht.readTemperature();

    Serial.print("Celsius = ");
    Serial.print(temp);
    Serial.println("*C");

    convertedF = ( temp * 1.8 ) + 32;
    Serial.print("Fahrenheit = ");
    Serial.print(convertedF);
    //Print degree symbol 
    Serial.println("*F");

    convertedK = temp + 273.15;
    Serial.print("Kelvin = ");
    Serial.print(convertedK);
    Serial.println("*K");
           
    convertedR = (convertedK * 1.8);
    Serial.print("Rankin = ");
    Serial.print(convertedR);
    //Print degree symbol   
    Serial.println("*R");
    

    Serial.print("Humidity =");
    Serial.println(hum);

    tft.setBackgroundColor(COLOR_BLACK);
    tft.setFont(Terminal12x16);
    tft.drawText(0,0,"Weather Station",COLOR_WHITE);
    

    
    tft.setFont(Terminal6x8);
    tft.drawText(0, 30, "Humidity :", COLOR_CYAN);
    tft.drawText(100, 30, String(hum), COLOR_CYAN);
    
    tft.drawText(0, 60, "Celcius :", COLOR_CYAN);
    tft.drawText(100, 60, String(temp), COLOR_CYAN);
    tft.drawText(140, 60, "*C", COLOR_CYAN);
    
    tft.drawText(0, 90, "Fahrenheit :", COLOR_CYAN);
    tft.drawText(100, 90, String(convertedF), COLOR_CYAN);
    tft.drawText(140, 90, "*F", COLOR_CYAN);
    
    tft.drawText(0, 120, "Kelvin :", COLOR_CYAN);
    tft.drawText(100, 120, String(convertedK), COLOR_CYAN);
    tft.drawText(150, 120, "*K", COLOR_CYAN);
    
    tft.drawText(0, 150, "Rankin :", COLOR_CYAN);
    tft.drawText(100, 150, String(convertedR), COLOR_CYAN);
    tft.drawText(150, 150, "*R", COLOR_CYAN);

}
