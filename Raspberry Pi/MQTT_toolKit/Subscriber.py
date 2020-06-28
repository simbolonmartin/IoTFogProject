#mosquitto_pub -d -u user1 -P ivam -t test -m "Hello, World!"
#mosquitto_sub -d -u username -P password -t test

import paho.mqtt.client as mqtt
# 當地端程式連線伺服器得到回應時，要做的動作
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # 將訂閱主題寫在on_connet中
    # 如果我們失去連線或重新連線時 
    # 地端程式將會重新訂閱
    client.subscribe("EMG")
    

# 當接收到從伺服器發送的訊息時要進行的動作
def on_message(client, userdata, msg):
    # 轉換編碼utf-8才看得懂中文
    print(msg.topic+" "+ msg.payload.decode('utf-8'))

# 連線設定
# 初始化地端程式
client = mqtt.Client()
#__database=_Database()
# 設定連線的動作
client.on_connect = on_connect
#__database.input_pred_data('11')

# 設定接收訊息的動作
client.on_message = on_message

# 設定登入帳號密碼
client.username_pw_set("username","password")

# 設定連線資訊(IP, Port, 連線時間)
client.connect("192.168.43.109", 1883, 60)

client.loop_forever()