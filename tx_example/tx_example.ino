/*
  @@@@@@@@@@@@@@@@@@@@@@                                                                                                                               
  @@@@@@@@@@@@@@@@@@@@@@             @@@.    @@@    @@@.     @@@@    @@@@        @@@@@@@@@        @@@@@@@@@@@@@.     .@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@%%@@@%%@@@%%@@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@@@@@@@        @@@@@@@@@@@@@@     @@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@  @@@  @@@  @@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@            @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@   @    @   @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@@@@@@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@@@@@@@@ 
  @@@@@            @@@@@             @@@@###@@@@@##@@@@@     @@@@    @@@@      @@@@@@@@@@@@       #@@@@@###@@@@@     ##@@@@@###@@@@       @@@@@@@@@@@
  @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@     @@@@    @@@@      @@@@    @@@@@      @@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@     @@@@
  @@@@@@@@@@@@@@@@@@@@@@
  
  Whadda LONG RANGE 433MHz TX RF WIRELESS MODULE
  This example code generate a random value and send it to the receiver when Button 1 or button 2 is pressed.
  The generated value is added with a different fixed value depending on which button is pressed.
  The transmitted code can be viewed on the serial monitor.

  For more information about the Whadda long range transmitter, consult the manual at the WPI469 product page on whadda.com
  
 */

#include <RCSwitch.h>
#include <EEPROM.h>

RCSwitch mySwitch = RCSwitch();

#define Button1 2
#define Button2 4
int code1 = 0;
int code2 = 0;

void setup()
{
  Serial.begin(9600);
  //mySwitch.setRepeatTransmit(10);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);

  byte data = EEPROM.read(0);
  randomSeed(analogRead(3));
  if (data == 0 || data == 255)
  {
    EEPROM.write(0, (byte)random(1, 256));
    data = EEPROM.read(0);
    code1 = 1000 + data;
    code2 = 2000 + data;
  } else {
    code1 = 1000 + data;
    code2 = 2000 + data;
  }
  // Transmitter is connected to Arduino Pin #0
  mySwitch.enableTransmit(10);
}

void loop()
{
  if (digitalRead(Button1) == LOW) {
    mySwitch.send(code1, 24);
    delayMicroseconds(100);
    Serial.print("Button 1 is pressed and sends code: ");
    Serial.println(code1);
  }
  else if (digitalRead(Button2) == LOW) {
    mySwitch.send(code2, 24);
    delayMicroseconds(100);
    Serial.print("Button 2 is pressed and sends code: ");
    Serial.println(code2);
  }
}
