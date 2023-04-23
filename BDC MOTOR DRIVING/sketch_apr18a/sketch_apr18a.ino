// Pin Configuration
const int En = 2;    // First Enable pin for the H-bridge
const int In1 = 3;   // First input for H-bridge
const int In2 = 4;   // Second input for H-bridge
const int In3 = 5;   // Third input for H-bridge
const int In4 = 6;   // Fourth input for H-bridge
const int led = 7;   // Indication auxiary LED pin
const int PB = 8;    // Push button pin
const int D7 = 9;    // lcd configure pin
const int D6 = 10;   // lcd configure pin
const int D5 = 11;   // lcd configure pin
const int D4 = 12;   // lcd configure pin
const int E = 13;    // lcd configure pin
const int RS = 14;   // lcd configure pin
const int EncA = 15; // Encoder Channel A input pin
const int EncB = 16; // Encoder Channel B input pin
const int En2 = 17;  // Second Enable pin for the H-bridge
volatile int Pos = 0;//Define volatile variable to store the current position in it. 
                     //The variable should be volatile because it is updated inside an interrupt pin code.

// LCD display Configuration
#include <LiquidCrystal.h>
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  

void setup() {
//SERIAL MONITOR & LCD DISPLAY
  Serial.begin(115200);  
  lcd.begin(16,2);
  lcd.print("HELLO :D");
  lcd.setCursor(0,1);
  lcd.print("ENCODER");
  delay(500);
  lcd.clear();


//L298N MOTOR DRIVER + LED + Push button
  pinMode(PB, INPUT); 
  pinMode(led, OUTPUT); 
  pinMode(En , OUTPUT); 
  pinMode(En2 , OUTPUT); 
  pinMode(EncA,INPUT ); 
  pinMode(EncB,INPUT ); 
  pinMode(In1, OUTPUT); 
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT); 
  pinMode(In4, OUTPUT); 
  attachInterrupt(15, doEncoder, RISING) ;
  digitalWrite(led,LOW ) ;        // Set the motor speed 
  analogWrite(En,200);
  }

void loop() {

  
  if (digitalRead(PB) == HIGH )                          // motor 1
        { digitalWrite(In1,LOW) ; 
        digitalWrite(In2,HIGH ) ; }
  else
        { digitalWrite(In1,HIGH) ; 
        digitalWrite(In2,LOW ) ; 
        digitalWrite(led,HIGH ) ;                        // To indicate reverse rotation. 
        }

  digitalWrite(17, 1);                                   // motor 2  
  digitalWrite(5, 1);
  digitalWrite(6, 0);
  delay(3000);
  digitalWrite(17, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 1);
  delay(500);
  digitalWrite(17, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 1);
  delay(3000);

  lcd.setCursor(0,0);                                    // LCD
  lcd.print("ENCODER");
  lcd.setCursor(0,1);
  lcd.print(Pos);
  lcd.print("         ");

  Serial.println (Pos);                                  // Serial monitor 
  delay(10) ;

}

void doEncoder() {
// Interrupt Code
if (digitalRead(EncA) == digitalRead(EncB))
     {Pos++;}
else { Pos--; }
}
