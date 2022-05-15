// Print All the variables to troubleshoot

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

int LED = 10;
int ldr = A0;

/*Variable settings*/ 
int PV = 0;
int CO = 0;
int SetP = 0;
int Error = 0;
float pGain = 0.0;
float iGain = 0.0;
int Iaction;
int ScreenNumber;
int unsigned long previousMillis = 0;
const long interval = 100;
unsigned long currentMillis;

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

PV = analogRead(ldr);
currentMillis = millis();


if (currentMillis - previousMillis >= interval) {
  
  previousMillis = currentMillis;
  Error = SetP - PV;
  Iaction = (Iaction + Error);
  CO = (pGain * Error)+(iGain * Iaction);


if (CO >= 255)
{CO = 255;}

if (CO < 0){
CO = 0;

if (Iaction >= 255)
(Iaction = 255);

} 
analogWrite(LED, CO);    
  }

Serial.print("SP: ");
Serial.print(SetP);
Serial.print("\t");
Serial.print("PV: ");
Serial.print(PV);
Serial.print("\t");
Serial.print("SSE: ");
Serial.print(Error);
Serial.println();

/*PUSH BUTTON UP SETTINGS*/ 

LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if (LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 2){
    iGain = iGain + 0.05;
   }
   if(ScreenNumber == 1){
    SetP = SetP + 50;
   }
   if(ScreenNumber == 0){
    pGain = pGain + 0.1;
   }
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if (LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 2){
    iGain = iGain - 0.05;
   }
   if(ScreenNumber == 1){
    SetP = SetP - 50;
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
  if(ScreenNumber > 2){
    ScreenNumber = 0;
  }
 }

  switch(ScreenNumber){
    case 0:
  lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("pGain = ");
  lcd.print(pGain);
  lcd.print(" ");
    break;
    case 1:
     lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("SP = ");
  lcd.print(SetP);
  lcd.print("     ");
     break;
     case 2:
      lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("iGain = ");
  lcd.print(iGain);
  lcd.print("     ");
  default:
  break;
  }
}
