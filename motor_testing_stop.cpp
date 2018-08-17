#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #if defined(__AVR__)
    #include <avr/io.h>
  #endif
  #include "WProgram.h"
#endif

#include "my_remote.h"
#include <IRremote.h>
#include "my_motor.h"

void MOTOR_TESTING_STOP (IRrecv irrecv) {

    motor3.run(RELEASE);
    motor4.run(RELEASE);
}
