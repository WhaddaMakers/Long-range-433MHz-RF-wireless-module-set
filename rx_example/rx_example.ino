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
  
  Whadda LONG RANGE 433MHz RX RF WIRELESS MODULE
  This example code capture the received code from the transmitter and show it on the serial monitor.
  The code can detect if button 1 or button 2 was pressed.

  For more information about the Whadda long range receiver, consult the manual at the WPI469 product page on whadda.com
  
 */

#include <RCSwitch.h>

int led_pin = 13;
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2 pinMode(led,OUTPUT);
}
void loop() {

  digitalWrite(led_pin,LOW);
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } 
    else 
    {
       //  used for checking received data      
        Serial.print("Received ");       
        Serial.print( mySwitch.getReceivedValue() );      
        Serial.print(" / ");     
        Serial.print( mySwitch.getReceivedBitlength() );      
        Serial.print("bit ");      
        Serial.print("Protocol: ");     
        Serial.println( mySwitch.getReceivedProtocol() ); 
    }
    if (mySwitch.getReceivedValue())
    {
        process();
    }
    mySwitch.resetAvailable();
    Serial.println("  ");  
  }
  digitalWrite(led_pin,LOW);
  delay(100);
}

void process()
{
  unsigned long res = mySwitch.getReceivedValue();
  if ((res-1000) > 1000){
    Serial.println("Button 2 was pressed");
  }
  else {
    Serial.println("Button 1 was pressed");
  }
}
