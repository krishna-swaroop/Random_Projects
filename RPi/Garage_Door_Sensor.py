# Basic RPi project using a distance sensor and some LEDs.
# The values are arbitrary. change accordingly.
import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.cleanup()
GPIO.setmode(GPIO.BCM)

Trig = 4    # For trigger function. Sends out a pulse through the distance sensor
Echo = 18   # Listens for the triggered pulse to return.

# Pin declarations for coloured LEDs
Green  = 17     # the numbers mentioned are pin number on RPi. Change them accordingly based on your circuit
Yellow = 27
Red    = 22

# pin declarations
GPIO.setup(Trig,GPIO.OUT)
GPIO.setup(Echo,GPIO.OUT)

GPIO.setup(Green,GPIO.OUT)
GPIO.setup(Yellow,GPIO.OUT)
GPIO.setup(Red,GPIO.OUT)

# Function declarations
def green_light():
  GPIO.output(Green, GPIO.HIGH)
  GPIO.output(Yellow, GPIO.LOW)
  GPIO.output(Red, GPIO.LOW)
  

def yellow_light():
  GPIO.output(Green, GPIO.LOW)
  GPIO.output(Yellow, GPIO.HIGH)
  GPIO.output(Red, GPIO.LOW)
  

def red_light():
  GPIO.output(Green, GPIO.LOW)
  GPIO.output(Yellow, GPIO.LOW)
  GPIO.output(Red, GPIO.HIGH)  
  
def get_distance():
  GPIO.output(Trig, True)
  time.sleep(0.0001)
  GPIO.output(Trig, False)
  
  while GPIO.input(Echo) == False
    start = time.time()
  while GPIO.input(Echo) == True
    end = time.time()
  sig_time = end-start
  
  #distance in cm
  distance = sig_time/(0.000058)
  
  print('Distance: {} cm'.format(distance))
  return distance

while True:
  distance = get_distance()
  time.sleep(0.05)
  
  if distance >= 9:
    green_light()
  elif 9>distance>6
    yellow_light()
  elif distance <= 6:
  red_light()

  
  
  
  
