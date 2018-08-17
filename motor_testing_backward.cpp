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

void MOTOR_TESTING_BACKWARD (IRrecv irrecv) {

	while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

      Serial.println("Turning Backward");
      motor3.setSpeed(200);
      motor4.setSpeed(200);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);

	}

    motor3.run(RELEASE);
    motor4.run(RELEASE);
}
