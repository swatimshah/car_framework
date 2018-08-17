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

void MOTOR_TESTING_FORWARD (IRrecv irrecv) {

	while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

      Serial.println("Turning Forward");
      motor3.setSpeed(200);
      motor4.setSpeed(200);
      motor3.run(FORWARD);
      motor4.run(FORWARD);

	}

    motor3.run(RELEASE);
    motor4.run(RELEASE);
}
