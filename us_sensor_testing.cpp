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
#include "SR04.h"
#include "us_sensor_testing.h"

long a;
SR04 sr04_LEFT = SR04(ECHO_PIN_LEFT,TRIG_PIN_LEFT);
long b;
SR04 sr04_FRONT = SR04(ECHO_PIN_FRONT,TRIG_PIN_FRONT);

void US_SENSOR_TESTING (IRrecv irrecv) {

	while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

        a=sr04_LEFT.Distance();
        Serial.print(a);
        Serial.println("cm - LEFT");
        delay(2000);
        b=sr04_FRONT.Distance();
        Serial.print(b);
        Serial.println("cm - FRONT");
        delay(2000);

	}

}
