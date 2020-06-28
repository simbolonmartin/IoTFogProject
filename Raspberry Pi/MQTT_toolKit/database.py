import MySQLdb
import datetime
import requests

class _Database:
    def __init__(self):
        
        self.IP_host = '140.118.206.174'
        self.Port='8000'
        self.User = 'IVAM'
        self.password = 'IVAM'
        self.database = 'fog'
        
    def input_pred_data(self,data):
        db = MySQLdb.connect(host=self.IP_host,user=self.User,passwd=self.password,db=self.database)
        cursor = db.cursor()
        # input_time = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S") 
        sql = "INSERT INTO `health_data`(`EMG`) VALUES ('"+str(data)+"')"
        cursor.execute(sql)
        print('--')
        db.commit()
        
    def Upload_Image(self,select_img,fence):
        my_data={'btn-upload': fence}
        my_files = {'file': open(select_img, 'rb')}
        r = requests.post('http://'+self.IP_host+':'+self.Port+'//upload.php', files = my_files , data=my_data)
        print( r.text)




