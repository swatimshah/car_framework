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
#include "ir_sensor_testing.h"

void IR_SENSOR_TESTING (IRrecv irrecv) {

	while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

	  pinMode(LEFT,INPUT);
	  pinMode(RIGHT,INPUT);

  	  Serial.print("Left: ");
      Serial.println(digitalRead(LEFT));

  	  Serial.print("Right: ");
      Serial.println(digitalRead(RIGHT));

	}

}
