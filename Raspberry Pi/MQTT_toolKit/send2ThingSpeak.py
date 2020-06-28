from time import time, sleep
from urllib.request import urlopen
import random as rnd
import sys

WRITE_API = "34USF4CA0N27P9JA" # Replace your ThingSpeak API key here
BASE_URL = "https://api.thingspeak.com/update?api_key={}".format(WRITE_API)

SensorPrevSec = 0
SensorInterval = 1 # 2 seconds
ThingSpeakPrevSec = 0
ThingSpeakInterval = 5 # 20 seconds

try:
    while True:
        
        if time() - SensorPrevSec > SensorInterval:
            SensorPrevSec = time()           
            
            humidity = rnd.randint(1,100)
            temperature = rnd.randint(1,100)
            print("Humidity = {:.2f}%\tTemperature = {:.2f}C".format(humidity, temperature))
        
        if time() - ThingSpeakPrevSec > ThingSpeakInterval:
            ThingSpeakPrevSec = time()
            
            thingspeakHttp = BASE_URL + "&field3={:.2f}&field2={:.2f}".format(temperature, humidity)
            print(thingspeakHttp)
            
            conn = urlopen(thingspeakHttp)
            print("Response: {}".format(conn.read()))
            conn.close()
            
            sleep(1)
            
except KeyboardInterrupt:
    conn.close()