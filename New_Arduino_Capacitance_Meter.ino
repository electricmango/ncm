/*
  New Arduino Capacitance Meter
  V 2.3.1
  by 
  Daniel Min Hyuk Jang
  
  Just an edit for the Liquid Crystal Library
  
  Original:
  RCTiming_capacitance_meter
  Paul Badger 2008
  Demonstrates use of RC time constants to measure the value of a capacitor 
 
  Theory   A capcitor will charge, through a resistor, in one time constant, 
  defined as T seconds where
  
    TC = R * C
 
    TC = time constant period in seconds
    R = resistance in ohms
    C = capacitance in farads (1 microfarad (ufd) = .0000001 farad = 10^-6 
    farads) 

    The capacitor's voltage at one time constant is defined as 63.2% of the 
    charging voltage.
 
  Hardware setup:
  Test Capacitor between common point and ground (positive side of an 
  electrolytic capacitor  to common)
  Test Resistor between chargePin and common point
  220 ohm resistor between dischargePin and common point
  Wire between common point and analogPin (A/D input)
  Liquid Crystal Display
  
  For detailed schematic and original code (uses serial port):
  
  http://arduino.cc/it/Tutorial/CapacitanceMeter
  
 */

#define analogPin      0          // analog pin for measuring capacitor voltage
#define chargePin      13         // pin to charge the capacitor - connected
                                  // to one end of the charging resistor
#define dischargePin   2          // pin to discharge the capacitor
#define resistorValue  1000.0F    // change this to whatever resistor value you
                                  // are using
                                  // F formatter tells compliler it's a floating
                                  // point value
#include <LiquidCrystal.h>
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                /* floating point variable to preserve 
                                     precision, make calculations
                                   */
float nanoFarads;
float picoFarads;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

byte loading[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup(){
  pinMode(chargePin, OUTPUT);     // set chargePin to output
  digitalWrite(chargePin, LOW);  
  lcd.begin(16, 2);
  lcd.createChar(0, loading);
  lcd.clear();                    // clear the screen
  lcd.print("New Arduino Capacitance Meter  V 2.3.1"); // intro
  delay(500);
  for (int positionCounter = 0; positionCounter < 22; positionCounter++){ /* 
    scroll 13 positions (string length) to the left 
    to move it offscreen left
    */
    lcd.scrollDisplayLeft();      // scroll one position left
    delay(200);                   // wait a bit
  }
  delay(500);
  lcd.clear();                    // clear the screen
  lcd.setCursor(0,0);
  lcd.print("Sorry, this ca-");
  lcd.setCursor(0,1);
  lcd.print("pacitance meter");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("can only read ");
  lcd.setCursor(0,1);
  lcd.print("microFarads.");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mango Labs is ");
  lcd.setCursor(0,1);
  lcd.print("working on a ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("better capaci-");
  lcd.setCursor(0,1);
  lcd.print("tance meter.");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("We are sorry for");
  lcd.setCursor(0,1);
  lcd.print("the long message");
  delay(1500);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Starting up");        /* 'Starting up' sign just for fun (you'll
                                      like it)
                                    */
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(1,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(2,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(3,1);
  lcd.write(byte(0));
  delay(500);  
  lcd.setCursor(4,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(5,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(6,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(7,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(8,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(9,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(10,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(11,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(12,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(13,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(14,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(15,1);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(2,0);
  lcd.print("  Ready    ");
  delay(500);
  lcd.clear();
}

void loop(){
  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = millis();
  while(analogRead(analogPin) < 648){ /* 647 is 63.2% of 1023, which 
                                         corresponds 
                                         to full-scale voltage 
                                       */
  }
  elapsedTime= millis() - startTime; /* convert milliseconds to seconds (10^-3
                                        ) and Farads to microFarads ( 10^6 ),
                                        net 10^3 (1000)
                                      */
  microFarads = ((float)elapsedTime / resistorValue) * 1000;
  lcd.setCursor(0,1);
  lcd.print(elapsedTime);          // print the value to lcd
  lcd.print(" milliseconds");      // print units and carriage return
  if(elapsedTime == 0){
    lcd.clear();                   // print nothing if elapsedTime == 0
    delay(1000);
  }
  if (microFarads >= 1){
    lcd.setCursor(0,0);
    lcd.print((long)microFarads);   // print the value to serial port
    lcd.print(" microFarads");      // print units and carriage return
    lcd.setCursor(0,0);
  }
  else if (microFarads <= 1){ 
    /* if value is smaller than one microFarad, convert to nanoFarads 
    (10^-9
    Farad).
     */
    nanoFarads = microFarads * 1000.0; /* multiply by 1000 to convert to
                                       nanoFarads (10^-9 Farads)
                                        */
    lcd.setCursor(0,0);                                   
    lcd.print((long)nanoFarads); // print the value to serial port
    lcd.print(" nanoFarads");       // print units and carriage return
    lcd.setCursor(0,0);
  }
  if (nanoFarads >= 1){
    picoFarads = nanoFarads * 1000.0; /* multiply by 1000 to convert to
                                       picoFarads (10^-12 Farads)
                                        */
    lcd.setCursor(0,0);                                   
    lcd.print((long)picoFarads); // print the value to serial port
    lcd.print(" picoFarads");       // print units and carriage return
    lcd.setCursor(0,0);
  }
  // dicharge the capacitor
  digitalWrite(chargePin, LOW);     // set charge pin to  LOW 
  pinMode(dischargePin, OUTPUT);    // set discharge pin to output 
  digitalWrite(dischargePin, LOW);  // set discharge pin LOW 
  while(analogRead(analogPin) > 0){ /* wait until capacitor is completely
                                       discharged
                                     */
  }
  pinMode(dischargePin, INPUT);     // set discharge pin back to input
} 
