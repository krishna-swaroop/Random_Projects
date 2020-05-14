#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DallasTemperature.h>

#define SensorPin A0     //pH meter Analog output to Arduino Analog
Input 0
#define Offset 0.00      //deviation compensate
#define LED 13
#define samplingInterval 2000
#define printInterval 8000
#define ArrayLenth 40    //times of collection

const char* ssid = "swaroop";
const char* password = "***********";          // Replace with correct details of your network
const char* mqttServer = "192.168.xx.xxx";     // Replace with your IP
const int mqttPort = 1883;
int pHArray[ArrayLenth]; //Store the average value of the sensor feedback
int pHArrayIndex=0;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);
float temperatureF;
float temperatureC;

void setup() {

  // Start the Serial Monitor
  Serial.begin(9600);

  // Start the DS18B20 sensor
  sensors.begin();

  pinMode(LED,OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
}
Serial.println("Connected to the WiFi network");

client.setServer(mqttServer, mqttPort);
client.setCallback(callback);
while (!client.connected()) {
  Serial.println("Connecting to MQTT...");
  if (client.connect("ESP8266Client")) {
    Serial.println("Connected");
    } else {
    Serial.print("failed with state ");
    Serial.print(client.state());
    delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i &lt; length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println(&quot;-----------------------&quot;);
}
void loop() {
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();

  static float pHValue,voltage;
  if(millis()-samplingTime &gt; samplingInterval)
  {
    pHArray[pHArrayIndex++]=analogRead(SensorPin);
    if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
    voltage = avergearray(pHArray, ArrayLenth)*5.0/1024; //ph_call
    sensors.requestTemperatures();
    temperatureC = sensors.getTempCByIndex(0);
    temperatureF = sensors.getTempFByIndex(0);
    pHValue = 3.5*voltage+Offset;
    pHValue = pHValue/2;
    samplingTime=millis();
  }
  if(millis() - printTime &gt; printInterval) //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    Serial.print(temperatureC);
    Serial.println(&quot;ºC&quot;);
    Serial.print(temperatureF);
    Serial.println(&quot;ºF&quot;);
    Serial.print(&quot;Voltage:&quot;);
    Serial.print(voltage,2);
    Serial.print(&quot; pH value: &quot;);
    Serial.println(pHValue,2);
    digitalWrite(LED,digitalRead(LED)^1);
    printTime=millis();
    client.publish(&quot;topic/ph&quot;, String(pHValue).c_str());
    client.subscribe(&quot;topic/ph&quot;);
    client.publish(&quot;topic/temp&quot;, String(temperatureC).c_str());
    client.subscribe(&quot;topic/temp&quot;);
  }

}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;

  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to averaging!/n");
    return 0;
  }
  if(number<5){ //less than 5, calculated directly statistics
    for(i=0;i&lt;number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
    }else{
      if(arr[0]&lt;arr[1]){
        min = arr[0];max=arr[1];
      }
      else{
        min=arr[1];max=arr[0];
      }
      for(i=2;i&lt;number;i++){
        if(arr[i]&lt;min){
          amount+=min; //arr&lt;min
          min=arr[i];
        }
        else {
          if(arr[i]&gt;max){
            amount+=max; //arr&gt;max
            max=arr[i];
          }
          else{
            amount+=arr[i]; //min&lt;=arr&lt;=max
          }
        }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
