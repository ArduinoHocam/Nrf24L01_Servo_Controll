#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>

//Pins....
#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICKX A0 //X axsis connected to A0
#define JOYSTICKY A1 
#define BUTTON 8 


const uint64_t pipe = 0xE8E8F0F0E1LL;  //channel identity
RF24 radio(CE_PIN, CSN_PIN); 
int joystick[3];  //3 element array

void setup() 
{
  //Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(BUTTON, INPUT);
}

void loop()   
{

  joystick[0] = analogRead(JOYSTICKX);
  joystick[1] = analogRead(JOYSTICKY);
  joystick[2] = digitalRead(BUTTON);
  radio.write( joystick, sizeof(joystick) ); //sending...
 

}
