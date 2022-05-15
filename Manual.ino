/*Include library*/ 
#include <LiquidCrystal.h> //Include LCD library

/*Assign the variable*/ 
int PV; //Storable value which will be the LDR value
int CO; //Control Output Control
int ScreenNumber;
int SetP = 0;

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
analogWrite(LED, CO);

/*CAP*/
if (SetP>255){
  SetP = 255;
  
}
if (SetP<0){
   SetP = 0;
}


/*PUSH BUTTON UP SETTINGS*/ 

LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if (LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){
    CO = CO + 25;
   }
   
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if (LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){
    CO = CO - 25;
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
  lcd.print(" ");
    break;
    case 1:
    lcd.setCursor(0, 1);
  lcd.print("CO = ");
  lcd.print(CO);
  lcd.print("    ");
  default:
  break;
  }

Serial.print("SP: ");
Serial.print(SetP);
Serial.print("\t");
Serial.print("PV: ");
Serial.print(PV);
Serial.print("\t");
Serial.print("CO: ");
Serial.print(CO);
Serial.println();

}
