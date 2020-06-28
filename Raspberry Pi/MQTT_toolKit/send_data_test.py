import sys
import urllib
from time import sleep
import random as rnd

key = '34USF4CA0N27P9JA'
baseURL = "https://api.thingspeak.com/update?api_key=%s" % key

def dummy():
    #rnd.seed(100)
    temp = rnd.randint(1,20)
    emg = rnd.randint(1,10)
    #print temp,emg
    return temp,emg

while True: 
    try:
        temp, emg = dummy()
        if isinstance(temp, int) and isinstance(emg, int):
            #temp = '%.2f' % temp
            #emg = '%.2f' % emg
            url = baseURL + "&field1=%s&field2=%s" % (temp, emg)
            print (url)
            conn = urllib.urlopen(url)
            print (conn.read())
            conn.close()
        else:
            print ("fail connection")
        

        sleep(2)

    except:
        break
