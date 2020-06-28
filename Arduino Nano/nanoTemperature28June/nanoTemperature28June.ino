#include <Wire.h>
#include "Adafruit_MLX90614.h"
#include <SoftwareSerial.h>

#define IR1 0x5A
Adafruit_MLX90614 mlx;
float sum_IR1=0.0;
float average_IR1=0.0;
float var_IR1=0.0;
int count=0;
SoftwareSerial mySerial(A0, A1); // RX, TX

const int sampling = 50;
const float b = 0.37798106473679; //0.39298106473679;
const float a = 24.530960642411;

void setup() {
  mlx.begin(); 
//  Serial.begin(115200);  
  Serial.begin(9600);
  mySerial.begin(9600);
//  digitalWrite(13,HIGH);
}

void loop() {
  ReadTemperature();
  delay(10);
}

void ReadTemperature(){
  if(count==sampling){
    average_IR1=sum_IR1/sampling;
    //float adjtemp = average_IR1*b+a;;
    
    long val;
    val = (long) (average_IR1 * 10L);  
    //    int a = val;
    int H_byte=val/256;
    int L_byte=val%256;
//    Serial.print("==");
//    Serial.println(val);

    mySerial.write("S");
    mySerial.write(H_byte);
    mySerial.write(L_byte);
    mySerial.write("E");

//    Serial1.write(average_IR1);
    //Serial.print(" | ");
//    Serial.println(average_IR1,1);
//    Serial1.println(average_IR1,1);
    
    sum_IR1=0;
    count = 0;
    }
  else{
    mlx.AddrSet(IR1);
    //var_IR1=mlx.readObjectTempC();
    var_IR1=mlx.readObjectTempC();
    sum_IR1=sum_IR1+var_IR1;
    delay(1);
    }
    count++; 
}
