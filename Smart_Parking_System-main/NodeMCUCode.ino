#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

SoftwareSerial arduino(0,1);
SimpleTimer timer ;

char auth[] = "";
char ssid[] = "Connection";
char password[]="12345678";

String data ;
char rdata ;
int ir1 , ir2 , ir3 , ir4 , ir5 , ir6 ;

void timerEvent()
{
  Blynk.virtualWrite(V1, millis()/1000);
}

void setup() {

  Serial.begin(9600);
  Blynk.begin(auth,ssid,password);

  timer.setInterval(1000L,irvalue1A);
  timer.setInterval(1000L,irvalue1B);
  timer.setInterval(1000L,irvalue1C);
  timer.setInterval(1000L,irvalue2A);
  timer.setInterval(1000L,irvalue2B);
  timer.setInterval(1000L,irvalue2C);
}

void loop() {
  if(Serial.available() == 0 )
  {
    Blynk.run();
    timer.run();
  }

  if(Serial.available() > 0 )
  {
    rdata = Serial.read();
    data = data + rdata ;
    if(rdata == '\n')
    {
      Serial.println(data);

      String S_1A = getValue(data , ',' , 0);
      String S_1B = getValue(data , ',' , 1);
      String S_1C = getValue(data , ',' , 2);
      String S_2A = getValue(data , ',' , 3);
      String S_2B = getValue(data , ',' , 4); 
      String S_2C = getValue(data , ',' , 5);

      ir1 = S_1A.toInt();
      ir2 = S_1B.toInt();
      ir3 = S_1C.toInt();
      ir4 = S_2A.toInt();
      ir5 = S_2B.toInt();
      ir6 = S_2C.toInt();

      data = "" ;
      
    }
  }
}

void irvalue1A()
{
  int val = ir1 ;
  Blynk.virtualWrite(V10 , val);
}

void irvalue1B()
{
  int val = ir2 ;
  Blynk.virtualWrite(V11 , val);
}

void irvalue1C()
{
  int val = ir3 ;
  Blynk.virtualWrite(V12 , val);
}

void irvalue2A()
{
  int val = ir4 ;
  Blynk.virtualWrite(V13 , val);
}

void irvalue2B()
{
  int val = ir5 ;
  Blynk.virtualWrite(V14 , val);
}

void irvalue2C()
{
  int val = ir6 ;
  Blynk.virtualWrite(V15 , val);
} 

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
