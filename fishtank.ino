#include<Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
Servo servo1;
float temperature, voltage;
int reading;
int tempPin = 2;
int pH = A0;
int phVal[10];
int pos = 0;
int counter;
int redPin = 6;
int greenPin = 5;
int bluePin = 4;
const float MAX_PH = 0;//FILL THIS IN
const float MIN_PH = 0;//FILL THIS IN
const int LOWEST_TEMP = 18;//FILL THIS IN
//OneWire oneWire(7); // Digital Pin 7
//DallasTemperature dTemp(oneWire);
OneWire oneWire(2);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  servo1.attach(13);
  sensors.begin();
  counter =0;
}

void loop(){
  //Serial.print(counter);
  //Serial.print("\n"); 
  if(counter==10){//86400){
    counter = 3;
    servo1.write(50);              
    delay(1000);
    servo1.write(90);
    delay(1000);
    servo1.write(130);
    delay(1000);   
    servo1.write(90);         
  }
  sensors.requestTemperatures();
  if(sensors.getTempFByIndex(0)<LOWEST_TEMP){
    //turn on light
    RGB_color(0,0,255);
    delay(1000);
  }else{
    RGB_color(0,255,0);
    delay(1000);
  }
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("\n");
  //STOLEN CODE
  for(int i=0;i<10;i++){ 
    phVal[i]=analogRead(pH);
    delay(100);
  }
  double temp;
  double buf[10];
  for(int i=0;i<10;i++){
    for(int j=0;j<10-1-i;j++){
      if(buf[i]>buf[j]){
        temp=phVal[i];
        phVal[i]=phVal[j];
        phVal[j]=temp;
      }
    }
  }
  int avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=phVal[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;  
  Serial.print(phValue);
  Serial.print("\n");
  //END OF COPIED CODE
// if(phValue>MAX_PH||phValue<MIN_PH){
    //turn on warning light
 //}else{
    //turn off warning light
 //}
  //Serial.print(counter);
  counter++;
}

void RGB_color(int redLightValue, int greenLightValue, int blueLightValue)
 {
  analogWrite(redPin, redLightValue);
  analogWrite(greenPin, greenLightValue);
  analogWrite(bluePin, blueLightValue);
}
