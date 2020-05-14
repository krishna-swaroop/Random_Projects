# These scripts need to be running on the laptop
import paho.mqtt.client as mqtt
import time
import requests

# This is the Subscriber
url =
"http://localhost:9999/api/v2/write?org=iot_project&bucket=sensors&precision=s"

headers = {"Authorization":"Token ZfENj35c11xxbeNTd0fDh6F9PoQ-
pO3Ji1sClFFzXRv7tsgSWBFLkVMZ10RxQWfCigTBelTG20yicO1_1hp10g=="}

##data = &quot;temp,sensor=sensor1 temp_value=22 &quot; + str(int(time.time()))
##r = requests.post(url, data=data, headers=headers)

def on_connect(client, userdata, flags, rc):
  print("Connected with result code "+str(rc))
  ##print("name of client is " + client)
  client.subscribe("topic/temp")
  ##client.subscribe("topic/ph")
def on_message(client, userdata, msg):
  print("received temp" + msg.payload.decode())
  ##print(userdata.decode())
  ##print(msg.payload.decode())
  data = "temp,sensor=sensor1 temp_value=" + msg.payload.decode() + " "+ str(int(time.time()))
  r = requests.post(url, data=data, headers=headers)

client = mqtt.Client()
client.connect("localhost",1883,60)
client.on_connect = on_connect
client.on_message = on_message
client.loop_forever()
