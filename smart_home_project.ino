#define BLYNK_PRINT Serial
 
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 

char auth[] = "TE0bJ9Xf-_2W-DHBRFY__uGO_02nLZP";
char my_name[] = "S.VIGNESH";
char password[] = "MY WIFI PASSWORD";
 

#define DHTTYPE DHT11
#define DHTPIN 0          
const int R1  = 5;            
const int R2  = 4;            
 

     
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}
 
void setup()
{
  
  Serial.begin(9600);
 
  Blynk.begin(auth,my_name, password);
  
  dht.begin();
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
 
  
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
