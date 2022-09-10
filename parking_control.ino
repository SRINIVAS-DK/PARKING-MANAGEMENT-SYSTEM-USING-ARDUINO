#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;//change pins accordingly
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Servo.h> 

Servo myservo1;
//pin no can vary
int echo1=A0;
int trigger1=A1;
int echo2=A2;
int trigger2=A3;
float duration1;
float distance1;
float duration2;
float distance2;

int Slot = 4;           //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

void setup() {
  lcd.begin(16,2);
pinMode(echo1,INPUT);
  pinMode(trigger1,OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(trigger2,OUTPUT);
  
myservo1.attach(9);
myservo1.write(100);

lcd.setCursor (0,0);
lcd.print("     ARDUINO    ");
lcd.setCursor (0,1);
lcd.print(" PARKING SYSTEM ");
delay (2000);
lcd.clear();  
}

void loop(){ 
   digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);
  duration1=pulseIn(echo1,HIGH);
  distance1=(duration1*0.034)/2;
   digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);
  duration2=pulseIn(echo2,HIGH);
  distance2=(duration2*0.034)/2;

if( distance1<40 && flag1==0){
if(Slot>0){flag1=1;
if(flag2==0)
{
  myservo1.write(0);
  Slot = Slot-1;
  }
}
else
{
lcd.setCursor (0,0);
lcd.print("    SORRY :(    ");  
lcd.setCursor (0,1);
lcd.print("  Parking Full  "); 
delay (2000);
lcd.clear(); 
}
}

if(distance2<40 && flag2==0)
{
  flag2=1;
if(flag1==0)
{
  myservo1.write(0); 
  Slot = Slot+1;
  }
}

if(flag1==1 && flag2==1){
delay (1000);
myservo1.write(100);
flag1=0, flag2=0;
}

lcd.setCursor (0,0);
lcd.print("    WELCOME!    ");
lcd.setCursor (0,1);
lcd.print("Slot Left: ");
lcd.print(Slot);
}
