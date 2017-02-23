#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

Servo servo; //Servo object


#define CE_PIN   9 //nrf24l01 PINS
#define CSN_PIN 10
#define led 4

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

int joystick[3]; //joystick variable with 3 element array

void setup() {
  pinMode(4, OUTPUT);
  radio.begin();  //nrf24l01 started
  radio.openReadingPipe(1, pipe);
  radio.startListening();;
  servo.attach(6);  //servo started
  Serial.begin(9600);
}

void loop() {


  if ( radio.available() ) //If signal available
  {
    radio.read( joystick, sizeof(joystick) );  //read joystick values

    int  xpos = joystick[1];  
    int button = joystick[2];
    int xpos1 = map(xpos, 0, 1023, 0, 180);
    bool done = false;  
    while (!done) {  //listen till done become true
      done = radio.read(joystick, 1);
      servo.write (xpos1);
      delay(10);
    }
    if (button == 0) { //led
      digitalWrite(4, HIGH);

    }
    else {
      digitalWrite(4, LOW);

    }


  }
}

