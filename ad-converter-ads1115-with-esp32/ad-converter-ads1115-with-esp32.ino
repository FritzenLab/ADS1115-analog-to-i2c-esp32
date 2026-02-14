#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#define LED D0 // This is pin 0 (first one) of my Xiao ESP32-C3
Adafruit_ADS1115 ads;
const float multiplier = 0.125F; // write here the value in mV of the ads.setGain you uncomment below
int16_t adc0, adc1, adc2, adc3;
long readTime= 0;
long LEDtime= 0;

void setup(void) 
{
  Wire.begin(6,7); // This is only necessary to some Arduinos and ESP32's, like
  // for example my Xiao ESP32-C3, which does not map the i2c in pins 4 and 5,
  // but on pins 6 and 7
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
 
  // This is important. It defines the max voltage you are going to read in all analog channels
  // For example I uncommented GAIN_ONE, meaning I can only read signals up to +/- 4.096V

  // ads.setGain(GAIN_TWOTHIRDS);  //+/- 6.144V  1 bit = 0.1875mV (default)
  ads.setGain(GAIN_ONE);        //+/- 4.096V  1 bit = 0.125mV
  // ads.setGain(GAIN_TWO);        //+/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);       //+/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      //+/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    //+/- 0.256V  1 bit = 0.0078125mV 
  ads.begin();
}
 
void loop(void) 
{
  if(millis() - readTime > 1000){ // do analog readings every 1000ms (1 second)
    readTime+= 1000;
    
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    //adc2 = ads.readADC_SingleEnded(2); // Uncomment to read this channel
    //adc3 = ads.readADC_SingleEnded(3); // Uncomment to read this channel
    
    // You use the "multiplier" variable below to convert from integer to milivolts,
    // so instead of showing for example 65535 integers it shows 4096mV
    Serial.print("AIN0: "); Serial.println(adc0 * multiplier);
    Serial.print("AIN1: "); Serial.println(adc1 * multiplier);
    //Serial.print("AIN2: "); Serial.println(adc2 * multiplier); // Uncomment to use this input
    //Serial.print("AIN3: "); Serial.println(adc3 * multiplier); // Uncomment to use this input
    Serial.println(" ");
  }  
  if(millis() - LEDtime > 200){ // Just blinking an LED at 0,4 seconds full cycle
    LEDtime+= 200;
    digitalWrite(LED, !digitalRead(LED));
  }  
}