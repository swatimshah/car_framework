
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #if defined(__AVR__)
    #include <avr/io.h>
  #endif
  #include "WProgram.h"
#endif


#include "my_remote.h"
#include "line_follower.h"
#include <IRremote.h>
#include "my_motor.h"

int Left=0;
int Right=0;

void LINE_FOLLOWER (IRrecv irrecv) {

     while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

        Left = digitalRead(LEFT_IR_SENSOR);
        Right = digitalRead(RIGHT_IR_SENSOR);

        if(Left==WHITE && Right==BLACK)
          RIGHT();
        if(Right==WHITE && Left==BLACK)
          LEFT();
        if((Right==BLACK && Left==BLACK))
          CONTINUE_LINE();
        if(Right==WHITE && Left==WHITE)
          RIGHT();

      }

	  STOP();
}


void CONTINUE_LINE (void)
{
  //Serial.println("Continue..");
   motor3.setSpeed(SPEED);
   motor3.run(FORWARD);
   motor4.setSpeed(SPEED);
   motor4.run(FORWARD);
}

void RIGHT (void)
{
   //Serial.println("Right ..");
   motor3.setSpeed(SPEED);
   motor3.run(FORWARD);
   motor4.setSpeed(NO_SPEED);
   motor4.run(FORWARD);
}

void LEFT (void)
{
   //Serial.println("Left ..");
   motor3.setSpeed(NO_SPEED);
   motor3.run(FORWARD);
   motor4.setSpeed(SPEED);
   motor4.run(FORWARD);
}

void STOP (void)
{
  //Serial.println("Stop..");
   motor3.setSpeed(NO_SPEED);
   motor4.setSpeed(NO_SPEED);
}
