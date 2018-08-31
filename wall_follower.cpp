
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #if defined(__AVR__)
    #include <avr/io.h>
  #endif
  #include "WProgram.h"
#endif


#include "my_remote.h"
#include "wall_follower.h"
#include "my_motor.h"

SR04 wf_sr04_left = SR04(LEFT_US_SENSOR_ECHO,LEFT_US_SENSOR_TRIG);
SR04 wf_sr04_front = SR04(FRONT_US_SENSOR_ECHO,FRONT_US_SENSOR_TRIG);

int WF_Left=0;
int WF_Front=0;

int WF_Left_Status=0;
int WF_Front_Status=0;

float WF_Error = 0;
float WF_Kp = 30;//40;//30;//8;
float WF_Ki = 0.003;//0.004;//0.003;//0.001; //0.000007; //0.00001
float WF_Kd = 8;//13;//8; //0.2; //0.5;//0.07 //0.05 //0.037

float MY_Kp_Front = 40;//50;//80;//8;
float MY_Ki_Front = 0; //0.2; //0.5;//0.07 //0.05 //0.037
float MY_Kd_Front = 20; //10;//20;//0.001; //0.000007; //0.00001


float MY_Error_Front = 0;
float MY_Correction_F = 0;
float MY_Integral_Front = 0;
float MY_Derivative_Front = 0;
float MY_LastError_Front = 0;


int WF_LeftTurnSpeed = 0;
int WF_RightTurnSpeed = 0;
int WF_Correction = 0;
float WF_Integral = 0;
float WF_Derivative = 0;
float WF_LastError = 0;
int rightTurnBegin = 0;
int leftTurnBegin = 0;
int straightLineBegin = 0;

void WALL_FOLLOWER (IRrecv irrecv) {

     while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

	WF_Front_Status = WF_GET_FRONT_US_STATUS();

    if(WF_Front_Status == OBSTACLE) {

		if (rightTurnBegin == 0)
		WF_INITIALIZE_WALL();

	    //WF_RIGHT();
	    WF_CONTINUE_WALL_FRONT();

 		rightTurnBegin = 1;
 		straightLineBegin = 0;

		continue;
    }

	rightTurnBegin = 0;

    WF_Left = wf_sr04_left.Distance();
    WF_Error = WF_Left - WF_DISTANCE;
    WF_Integral = (WF_Error + WF_Integral);
    WF_Derivative = (WF_Error - WF_LastError);

    WF_Correction = WF_Kp * WF_Error + WF_Kd * WF_Derivative + WF_Ki * WF_Integral;

    if (WF_Error < 10) {

    leftTurnBegin = 0;

	if (straightLineBegin == 0)
		WF_INITIALIZE_WALL();

	if(WF_Correction > 127 && WF_Correction > 0)
		WF_Correction = 127;

	if(WF_Correction < -127 && WF_Correction < 0)
		WF_Correction = -127;

    WF_LeftTurnSpeed = 128 - WF_Correction;
    WF_RightTurnSpeed = 128 + WF_Correction;

	straightLineBegin = 1;

    } else {

	if (leftTurnBegin == 0) {
    	WF_INITIALIZE_WALL();
		WF_INITIALIZE_WALL_FRONT();
	}

	int speed = 2.5 * WF_Error + 8 * WF_Derivative;

	if (speed > 127 && speed > 0)
		speed = 127;

	if (speed < -127 && speed < 0)
		speed = -127;

    WF_LeftTurnSpeed = 128 - (speed);
    WF_RightTurnSpeed = 128 + (speed);

    leftTurnBegin = 1;
    straightLineBegin = 0;

    }

    motor3.setSpeed(WF_LeftTurnSpeed);
    motor3.run(FORWARD);
    motor4.setSpeed(WF_RightTurnSpeed);
    motor4.run(FORWARD);

    WF_LastError = WF_Error;
	WF_INITIALIZE_WALL_FRONT();
//	straightLineBegin = 1;

	}

  WF_STOP();
}


void WF_INITIALIZE_WALL(void) {
WF_Integral = 0;
WF_Derivative = 0;
WF_LastError = 0;

}

void WF_INITIALIZE_WALL_FRONT(void) {

MY_Integral_Front = 0;
MY_Derivative_Front = 0;
MY_LastError_Front = 0;

}


void WF_CONTINUE_WALL_FRONT(void) {

        WF_Front = wf_sr04_front.Distance();
        MY_Error_Front = (WF_Front - WF_FRONT_DISTANCE);
        MY_Integral_Front = (MY_Error_Front + MY_Integral_Front);
        MY_Derivative_Front = (MY_Error_Front - MY_LastError_Front);

        MY_Correction_F = MY_Kp_Front * MY_Error_Front + MY_Kd_Front * MY_Derivative_Front + MY_Ki_Front * MY_Integral_Front;

		if(MY_Correction_F > 127 && MY_Correction_F > 0)
			MY_Correction_F = 127;

		if(MY_Correction_F < -127 && MY_Correction_F < 0)
			MY_Correction_F = -127;

        WF_LeftTurnSpeed = 128 - MY_Correction_F;
        WF_RightTurnSpeed = 128 + MY_Correction_F;

        motor3.setSpeed(WF_LeftTurnSpeed);
        motor3.run(FORWARD);
        motor4.setSpeed(WF_RightTurnSpeed);
        motor4.run(FORWARD);

        MY_LastError_Front = MY_Error_Front;

}





int WF_GET_LEFT_US_STATUS(void) {
     if(wf_sr04_left.Distance() < WF_DISTANCE)
      return OBSTACLE;
     else
      return NO_OBSTACLE;
}

int WF_GET_FRONT_US_STATUS(void) {
     if(wf_sr04_front.Distance() < WF_FRONT_DISTANCE)
      return OBSTACLE;
     else
      return NO_OBSTACLE;
}


void WF_RIGHT (void)
{
   //Serial.println("Right ..");
   motor3.setSpeed(WF_SPEED);
   motor3.run(FORWARD);
   motor4.setSpeed(WF_NO_SPEED);
   motor4.run(FORWARD);
}

void WF_LEFT (void)
{
   //Serial.println("Left ..");
   motor3.setSpeed(WF_NO_SPEED);
   motor3.run(FORWARD);
   motor4.setSpeed(WF_SPEED);
   motor4.run(FORWARD);
}

void WF_STOP (void)
{
  //Serial.println("Stop..");
   motor3.setSpeed(WF_NO_SPEED);
   motor4.setSpeed(WF_NO_SPEED);
}
