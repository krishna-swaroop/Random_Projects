# These scripts need to be running on the laptop 
import paho.mqtt.client as mqtt
import time
import requests

# This is the Subscriber
url =
"http://localhost:9999/api/v2/write?org=iot_project&amp;bucket=sensors&amp;precision=s"

headers ={"Authorization&quot;:&quot;Token ZfENj35c11xxbeNTd0fDh6F9PoQ-pO3Ji1sClFFzXRv7tsgSWBFLkVMZ10RxQWfCigTBelTG20yicO1_1hp10g=="}
##data = &quot;ph,sensor=sensor1 ph_value=22 &quot; + str(int(time.time()))
##r = requests.post(url, data=data, headers=headers)
def on_connect(client, userdata, flags, rc):
  print("Connected with result code" +str(rc))
  client.subscribe(&quot;topic/val&quot;)

def on_message(client, userdata, msg):
  print("received ph"+msg.payload.decode())
  data = "ph,sensor=sensor1 ph_value="+msg.payload.decode()+" "; + str(int(time.time()))
  r = requests.post(url, data=data, headers=headers)

client = mqtt.Client()
client.connect("localhost",1883,60)

client.on_connect = on_connect
client.on_message = on_message
client.loop_forever()
