#include<SoftwareSerial.h>
#include<Servo.h>


Servo exit_servo , entry_servo ;                   //Servo setup.


SoftwareSerial esp82(0,1);                         //Communicate with nodeMCU.

//slot IR pin number
int slot_1A = 11 ;
int slot_1B = 10 ;
int slot_1C = 9 ;
int slot_2A = 6 ;
int slot_2B = 8 ;
int slot_2C = 7 ;

//gate IR pin setup
int ir_entry = 4 ;
int ir_exit = 12 ;

//Senser value variable
String status_1A ;
String status_1B ;
String status_1C ;
String status_2A ;
String status_2B ;
String status_2C ;

//Complete Data
String datastream = "" ;

int pos_exit = 90 ;
int pos_entry = 90 ;
 
void setup() {

  Serial.begin(9600) ;
  esp82.begin(9600) ; 

  //Setup Pinmode
  pinMode(slot_1A , INPUT);
  pinMode(slot_1B , INPUT);
  pinMode(slot_1C , INPUT);
  pinMode(slot_2A , INPUT);
  pinMode(slot_2B , INPUT);
  pinMode(slot_2C , INPUT);

  pinMode(ir_entry , INPUT);
  pinMode(ir_exit , INPUT);

  entry_servo.attach(3);
  exit_servo.attach(13);
  
}

void loop() {

}

void slotStatus_1A()
{
  if(digitalRead(slot_1A) == LOW )
  {
    status_1A = "255";
    delay(300);
  }
  else
  {
    status_1A = "0";
    delay(300);
  }
}

void slotStatus_1B()
{
  if(digitalRead(slot_1B) == LOW )
  {
    status_1B = "255" ;
    delay(300);
  }
  else
  {
    status_1B = "0" ;
    delay(300);
  }
}

void slotStatus_1C()
{
  if(digitalRead(slot_1C) == LOW )
  {
    status_1C = "255";
    delay(300);
  }
  else
  {
    status_1C = "0" ;
    delay(300);
  }
}

void slotStatus_2A()
{
  if(digitalRead(slot_2A) == LOW )
  {
    status_2A = "255";
    delay(300);
  }
  else
  {
    status_2A = "0";
    delay(300);
  }
}

void slotStatus_2B()
{
  if(digitalRead(slot_2B) == LOW )
  {
    status_2B = "255" ;
    delay(300);
  }
  else
  {
    status_2B = "0";
    delay(300);
  }
}

void slotStatus_2C()
{
  if(digitalRead(slot_2C) == LOW )
  {
    status_2C ="255" ;
    delay(300);
  }
  else
  {
    status_2C ="0" ;
    delay(300);
  }
}

void gates()
{
  if(digitalRead(ir_exit) == LOW)
  {
    for(pos_exit = 90 ; pos_exit <= 180 ; pos_exit += 1)
    {
      exit_servo.write(pos_exit);
      delay(30);
    }
    delay(1000);
    for(pos_exit = 180 ; pos_exit >= 90 ; pos_exit -= 1)
    {
      exit_servo.write(pos_exit);
      delay(30); 
    }
  }

  if(digitalRead(ir_entry) == LOW && 
    (digitalRead(slot_1A) == HIGH ||
     digitalRead(slot_1B) == HIGH ||
     digitalRead(slot_1C) == HIGH ||
     digitalRead(slot_2A) == HIGH ||
     digitalRead(slot_2B) == HIGH ||
     digitalRead(slot_2C) == HIGH ))
     {
      for(pos_entry = 90 ; pos_entry <= 180 ; pos_entry += 1)
      {
        entry_servo.write(pos_entry);
        delay(30);
      }
      delay(1000);

      for(pos_entry = 180 ; pos_entry >= 90 ; pos_entry -= 1 )
      {
        entry_servo.write(pos_entry);
        delay(30);
      }
      
     }
    
}
