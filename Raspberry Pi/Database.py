from time import time, sleep
from urllib.request import urlopen
import random as rnd
import sys
import datetime
#mosquitto_pub -d -u username -P password -t test -m "Hello, World!"
#mosquitto_sub -d -u username -P password -t test

class ThingSpeeak:
    def __init__(self):   
                
        self.WRITE_API = "34USF4CA0N27P9JA" # Replace your ThingSpeak API key here
        self.BASE_URL = "https://api.thingspeak.com/update?api_key={}".format(self.WRITE_API)

        self.SensorPrevSec = 0
        self.SensorInterval = 1 # 2 seconds
        self.ThingSpeakPrevSec = 0
        self.ThingSpeakInterval = 5 # 20 seconds
        
    def send(self,EMG):
        try:
            

            
            
            
            datetime_object = datetime.datetime.now()
            print("time={} EMG = {:.2f}%\t".format(datetime_object,EMG))
            
            
            ThingSpeakPrevSec = time()
            
            thingspeakHttp = self.BASE_URL + "&field1={:.2f}".format(EMG)
            #print(thingspeakHttp)
            
            conn = urlopen(thingspeakHttp)
#            print("Response: {}".format(conn.read()))
            #conn.close()
            
           
                
        except KeyboardInterrupt:
            conn.close()
        
        
import MySQLdb
import datetime
import requests

class MySQL:
    def __init__(self):
        
        self.IP_host = '140.118.206.174'
        self.Port='8000'
        self.User = 'IVAM'
        self.password = 'IVAM'
        self.database = 'face_database'
        
    def input_pred_data(self,data):
        db = MySQLdb.connect(host=self.IP_host,user=self.User,passwd=self.password,db=self.database)
        cursor = db.cursor()
        # input_time = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S") 
        sql = "INSERT INTO `face_table`(`data`) VALUES ('"+str(data)+"')"
        cursor.execute(sql)
        db.commit()
    def Upload_Image(self,select_img,fence):
        my_data={'btn-upload': fence}
        my_files = {'file': open(select_img, 'rb')}
        r = requests.post('http://'+self.IP_host+':'+self.Port+'//upload.php', files = my_files , data=my_data)
        print( r.text)


