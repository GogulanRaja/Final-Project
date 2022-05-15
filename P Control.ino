#include <LiquidCrystal.h>

int PV;
int CO;
int SetP = 0;
float pGain = 0.0;
int Error; 
int ScreenNumber;
int var;

/*INPUT/Button settings*/ 
const int PushB1 = 8;
const int PushB2 = 9;
const int PushB3 = 13;

int LastState1;
int LastState2;
int LastState3;

int CurrentState1;
int CurrentState2;
int CurrentState3;

/*OUTPUT settings*/ 
int LED = 10;
int LDR = A0;
/*LCD settings*/ 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
pinMode(PushB1, INPUT_PULLUP);
pinMode(PushB2, INPUT_PULLUP);
pinMode(PushB3, INPUT_PULLUP);
pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  
PV = analogRead(3);
Error = SetP-PV;
CO = pGain*Error;
analogWrite(LED, CO);

if (CO>255){
   CO = 255;  
}
if (CO<0){
   CO = 0;
  // analogWrite(LED, CO);
}


//CAP

if (pGain<0){
    pGain = 0;

}
/*
if (SetP>255){
  SetP = 255;
  
}
if (SetP<0){
   SetP = 0;
*\   
}
/*PUSH BUTTON UP SETTINGS*/ 

LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if (LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){
    SetP = SetP + 25;
   }
   if(ScreenNumber == 0){
    pGain = pGain + 0.1;
   }
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if (LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){
    SetP = SetP - 25;
   }
   if(ScreenNumber == 0){
    pGain = pGain - 0.1;
   }
 }

/*PUSH BUTTON CHANGE PAGE SETTINGS*/ 

LastState3 = CurrentState3;
CurrentState3 = digitalRead(PushB3);
 if (LastState3 == 1 && CurrentState3 == 0){
  ScreenNumber = ScreenNumber + 1;
  if(ScreenNumber > 1){
    ScreenNumber = 0;
  }
 }


  switch(ScreenNumber){
    case 0:
  lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print("     ");
  lcd.setCursor(0, 0);
  lcd.print("pGain = ");
  lcd.print(pGain);
  lcd.print("     ");
    break;
    case 1:
     lcd.setCursor(0, 1);
  lcd.print("CO = ");
  lcd.print(CO);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("SP = ");
  lcd.print(SetP);
  lcd.print("     ");
  default:
  break;
  }
  Serial.print("\t ERROR: ");
  Serial.print(Error);
  Serial.print("\t PV: ");
  Serial.print(PV);
  Serial.print("\t SETP: ");
  Serial.print(SetP);
  Serial.print("\t P: ");
  Serial.print(pGain);  
  Serial.print("\t CO: ");
  Serial.println(CO);
  delay(200);
}
