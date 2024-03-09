#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>
#include<Wire.h>
#include<BH1750.h>
#define DHTPIN 7
#define DHTTYPE DHT22

#define RX 2
#define TX 3
BH1750 lightMeter;
int moistureValue;
int temp;
float incelcius;
int humidity;
DHT dht(DHTPIN, DHTTYPE); 

String AP = "konoha";             // AP NAME
String PASS = "anirudhsk02";       // AP PASSWORD
String API = "KFNGHFTG4UYBM01A3";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";

int countTrueCommand;
int countTimeCommand;
boolean found = false;

SoftwareSerial esp8266(RX, TX);


void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  lightMeter.begin();
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, INPUT);
  esp8266.begin(115200);

  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
   if (temperature >28)
  {
   Serial.print("Fan on");
   digitalWrite(3,HIGH);
  }
   else
  {
    Serial.print("Fan off");
    digitalWrite(3,LOW);
  }
   if (humidity<70)
  {
    Serial.print("led on");
    digitalWrite(10,HIGH);
  }
   else
  {   
    Serial.print("led off");
    digitalWrite(10,LOW);
  }


  int soilMoisture = analogRead(A0);
  Serial.print("\n MoistureValue :");
  Serial.print(moistureValue);
  Serial.print("%");
     if(moistureValue>500)
    {
      Serial.print("Motor On");
        digitalWrite(13,HIGH);
    }
     else
    {
      Serial.print("Motor off");
        digitalWrite(13,LOW);
    }

  float lux=lightMeter.readLightLevel();
  Serial.print("light: ");
  Serial.print(lux);
  delay(1000);
   if(lux<50)
  {
    Serial.print("led on");
    digitalWrite(12,HIGH);
  }
   else
  {
    Serial.print("led off");
    digitalWrite(12,LOW);
  }


  String getData = "GET /update?api_key=" + API + "&field1=" + String(temperature) +
                  "&field2=" + String(humidity) +
                  "&field3=" + String(soilMoisture) +
                  "&field4=" + String(lux);

  sendCommand("AT+CIPMUX = 1", 5, "OK");
  sendCommand("AT+CIPSTART = 0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND = 0," + String(getData.length() + 4), 4, ">");
  esp8266.println(getData);
  delay(1500);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");

  while (countTimeCommand < (maxTime * 1)) {
    esp8266.println(command);
    if (esp8266.find(readReplay)) {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if (found == true) {
    Serial.println("OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false) {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}
