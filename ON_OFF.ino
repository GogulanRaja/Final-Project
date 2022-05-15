#include <LiquidCrystal.h>

int PV;
int CO;
int SetP = 0;
int Hys = 0;
int ScreenNumber;

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
  
PV = analogRead(LDR);

/*HYSTERISIS SETTINGS*/
if(PV <= SetP-Hys){
    CO = 255;
  //analogWrite(LED, CO);  
}
  if(PV >= SetP+Hys){
    CO = 0;
 // analogWrite(LED, CO);  
}
analogWrite(LED, CO); 
/*CAP*/
if (SetP>1023){
  SetP = 1023;
  
}
if (SetP<0){
   SetP = 0;
}


/*PUSH BUTTON UP SETTINGS*/ 

LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if(LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){
    SetP = SetP + 50;
   }
   if(ScreenNumber == 0){
    Hys++;
   }
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if(LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){
    SetP = SetP - 50;
   }
   if(ScreenNumber == 0){
    Hys--;
   }
 }

/*PUSH BUTTON CHANGE PAGE SETTINGS*/ 

LastState3 = CurrentState3;
CurrentState3 = digitalRead(PushB3);
 if(LastState3 == 1 && CurrentState3 == 0){
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
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("Hyst = ");
  lcd.print(Hys);
  lcd.print(" ");
    break;
    case 1:
  lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print("    ");
  lcd.setCursor(0, 0);
  lcd.print("SP = ");
  lcd.print(SetP);
  lcd.print("    ");
  default:
  break;
  }
int PVdisplay = map(PV, 0, 1023, 0, 255);
Serial.print(SetP);
Serial.print("\t");
Serial.print(Hys);
Serial.print("\t");
Serial.println(PV);
}
