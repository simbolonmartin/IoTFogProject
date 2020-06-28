import thingspeak
import time
 
channel_id = 1081417 # PUT CHANNEL ID HERE
write_key  = '34USF4CA0N27P9JA' # PUT YOUR WRITE KEY HERE
read_key   = 'M96LURADMKN93JQQ' # PUT YOUR READ KEY HERE
 
def measure(channel):
    try:
        humidity = rnd.randint(1,100)
        temperature = rnd.randint(1,100)
        # write
        response = channel.update({'field1': temperature, 'field2': humidity})
        
        # read
        read = channel.get({})
        print("Read:", read)
        
    except:
        print("connection failed")
 
 
if __name__ == "__main__":
    channel = thingspeak.Channel(id=channel_id, write_key=write_key, api_key=read_key)
    while True:
        measure(channel)
        # free account has an api limit of 15sec
        time.sleep(15)