#include <LiquidCrystal.h>
#include "DHT.h"


/*
LED
pin 1 gnd
pin 2 5v
pin 3 gnd, you can control contrast with this
pin 4 RS pin 12
pin 5 gnd RW, LOW means write
pin 6 E 11
piny 7,8,9,10 not connected
pin 11,12,13,14 data d4-d7
pin 15 through resistor 220 ohm into pin 8 (backlight vdd)
pin 16 gnd (backlight ground)
*/
const int registerSelectPin = 12; 
const int enablePin = 11; 
const int backLightPin = 8;
const int d4pin = 5;
const int d5pin = 4;
const int d6pin = 3;
const int d7pin = 2;
LiquidCrystal lcd(registerSelectPin, enablePin, d4pin, d5pin, d6pin, d7pin);

const int switchPin = 7;

const int dhtPin = 6;

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


//DHT  https://plot.ly/arduino/dht22-temperature-tutorial/
// Connect red pin  to +5V
// Connect yellow pin to dhtPin
// Connect black pin GROUND
// Connect a 10K resistor from data pin to power pin

long lastTimeSwitchPushed = -1;
DHT dht(dhtPin, DHTTYPE);

void setup()
{
  
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(backLightPin, OUTPUT);
  lcd.begin(16,2); //parameters are size of the screen
  digitalWrite(backLightPin, LOW);
    dht.begin();
}

void loop()
{
  int switchPushed = digitalRead(switchPin);
  
  if (switchPushed == HIGH)
  {
    lastTimeSwitchPushed = millis();
    Serial.print("switch pushed in");
    Serial.println(lastTimeSwitchPushed);
  }
  long now = millis();
  long difference = now - lastTimeSwitchPushed;
  Serial.println(difference);
  if (difference < 5000 && lastTimeSwitchPushed != -1)
  {
   // Serial.println("switch pushed less than 5s ago");
   lcd.display();
   digitalWrite(backLightPin, HIGH); 
  // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
         lcd.setCursor(0,0);
         lcd.print("Neuspech");
    } 
    else 
    {
        lcd.setCursor(0,0);
        lcd.print("Teplota: ");
        lcd.print(t);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print("Vlhkost: ");
        lcd.print(h);
        lcd.print("%");
  
    }
  }
  else 
  {
    
    lcd.noDisplay();
    digitalWrite(backLightPin, LOW);
  }
 
  
 
}

