#include "Arduino.h"
#include "my_remote.h"
#include <IRremote.h>

IRrecv irrecv(REMOTE_RECV_PIN);
decode_results results;


IRrecv SETUP_REMOTE(void) {
	irrecv.enableIRIn(); // Start the receiver
	return irrecv;
}


long GET_REMOTE_CODE (IRrecv &irrecv) {

    if(irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
	    irrecv.resume(); // Receive the next value
		return results.value;
	} else {
		return 0;
	}
}

bool IS_REMOTE_BUTTON_STOP(long remote_code) {
	if (remote_code == STOP_CAR) {
		return true;
	} else {
		return false;
	}
}
