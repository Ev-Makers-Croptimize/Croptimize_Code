// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to


#define DHTTYPE DHT22   // DHT 22  (AM2302)

int sensorPin = A0; // select the input pin for LDR

int sensorValue = 0; // variable to store the value coming from the sensor


// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

#define SensorPin 0 //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00 //deviation compensate
unsigned long int avgValue; //Store the average value of the sensor feedback

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  pinMode(13,OUTPUT);
  dht.begin();
}
void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  t = t * 1.8 + 32;

  
  int buf[10]; //buffer for read analog
  for(int i=0;i<10;i++) //Get 10 sample value fromthe sensor for smooth the value
  {
    buf[i]=analogRead(SensorPin);
    //delay(1000);
  }
  for(int i=0;i<9;i++) //sort the analog fromsmall to large
  {
   for(int j=i+1;j<10;j++)
   {
      if(buf[i]>buf[j])
        {
         int temp=buf[i];
         buf[i]=buf[j];
         buf[j]=temp;
        }
    }
  avgValue=0;
for(int i=2;i<8;i++) //take the average value of 6 center sample
  avgValue+=buf[i];
float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
phValue=14-3.5*phValue+Offset; //convert the millivolt into pH value
// check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {


        
        Serial.print(t);

        Serial.print(",");
        
        Serial.print(phValue);
        Serial.print(",");
        Serial.print(sensorValue); //prints the values coming from the sensor on the screen

        Serial.print("\n");

        //Serial.println(" ");
        //Serial.println(" *F");


        Serial.flush();
 




  }

delay(1000);
}
}
