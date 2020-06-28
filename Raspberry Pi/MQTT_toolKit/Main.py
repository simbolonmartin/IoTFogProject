


import paho.mqtt.client as mqtt
#from Database import ThingSpeeak
import threading
import time
client = mqtt.Client()
client_EMG = mqtt.Client()
#_ThingSpeeak=ThingSpeeak()
count=0
def on_connect(client, userdata, flags, rc):
    #print("**Connected with result code "+str(rc))
    client.subscribe("EMG")

def on_connect_EMG(client, userdata, flags, rc):
    #print("**Connected with result code "+str(rc))
    client.subscribe("Temp")
    
def on_message(client, userdata, msg):
    
    
    client.on_connect = on_connect_EMG
    print(msg.topic+" "+ msg.payload.decode('utf-8'))
    
    #_ThingSpeeak.send(msg.topic,float(msg.payload.decode('utf-8')))



client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set("username","password")

client.connect("192.168.43.109", 1883, 60)

client.loop_forever()




  






