
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #if defined(__AVR__)
    #include <avr/io.h>
  #endif
  #include "WProgram.h"
#endif


#include "my_remote.h"
#include "wall_follower_l_f_pid.h"
#include "my_motor.h"

SR04 sr04_left = SR04(LEFT_US_SENSOR_ECHO,LEFT_US_SENSOR_TRIG);
SR04 sr04_front = SR04(FRONT_US_SENSOR_ECHO,FRONT_US_SENSOR_TRIG);

int WF_PID_Left=0;
int WF_PID_Front=0;

int Left_Status=0;
int Front_Status=0;

float Kp = 19;//13;
float Ki = 0.00003;//0.00001;
float Kd = 2;//0.037;
float Error = 0;
float LeftTurnSpeed = 0;
float RightTurnSpeed = 0;
float Correction = 0;
float Integral = 0;
float Derivative = 0;
float LastError = 0;



float Kp_Front = 8;
float Ki_Front = 0;
float Kd_Front = 0;
float Error_Front = 0;
float LTSpeed_F = 0;
float RTSpeed_F = 0;
float Correction_F = 0;
float Integral_Front = 0;
float Derivative_Front = 0;
float LastError_Front = 0;



void WALL_FOLLOWER_L_F_PID (IRrecv irrecv) {

     while (!IS_REMOTE_BUTTON_STOP(GET_REMOTE_CODE(irrecv))) {

	      Front_Status = GET_FRONT_US_STATUS();

	      if(Front_Status == NO_OBSTACLE) {
 	      	CONTINUE_WALL();
//        	INITIALIZE_WALL_FRONT();
      	  } else {
//			WF_PID_STOP();
			CONTINUE_WALL_FRONT();
	  	  }

//      	  if (Front_Status == OBSTACLE){
//        	CONTINUE_WALL_FRONT();
//        	INITIALIZE_WALL();
//      	  }

      }

	  WF_PID_STOP();
}


void INITIALIZE_WALL_FRONT(void) {

Integral_Front = 0;
Derivative_Front = 0;
LastError_Front = 0;

}

void INITIALIZE_WALL(void) {
Integral = 0;
Derivative = 0;
LastError = 0;

}

void CONTINUE_WALL(void) {
        WF_PID_Left = sr04_left.Distance();
        Error = (WF_PID_Left - DISTANCE);
        Integral = (Error + Integral);
        Derivative = (Error - LastError);

        Correction = Kp * Error + Kd * Derivative + Ki * Integral;

        LeftTurnSpeed = 140 - Correction;
        RightTurnSpeed = 140 + Correction;

        motor3.setSpeed(LeftTurnSpeed);
        motor3.run(FORWARD);
        motor4.setSpeed(RightTurnSpeed);
        motor4.run(FORWARD);

        LastError = Error;
}

void CONTINUE_WALL_FRONT(void) {
        WF_PID_Front = sr04_front.Distance();
        Error_Front = (WF_PID_Front - FRONT_DISTANCE);
        if(Error_Front < 0) {
        Integral_Front = (Error_Front + Integral_Front);
        Derivative_Front = (Error_Front - LastError_Front);
        LastError_Front = Error_Front;

        Correction_F = Kp_Front * Error_Front + Kd_Front * Derivative_Front + Ki_Front * Integral_Front;

        LTSpeed_F = 140 - Correction_F;
        RTSpeed_F = 140 + Correction_F;

        motor3.setSpeed(LTSpeed_F);
        motor3.run(FORWARD);
        motor4.setSpeed(RTSpeed_F);
        motor4.run(FORWARD);

        }
}

int GET_LEFT_US_STATUS(void) {
     if(sr04_left.Distance() < DISTANCE)
      return OBSTACLE;
     else
      return NO_OBSTACLE;
}

int GET_FRONT_US_STATUS(void) {
     if(sr04_front.Distance() < FRONT_DISTANCE)
      return OBSTACLE;
     else
      return NO_OBSTACLE;
}


void WF_PID_STOP (void)
{
  //Serial.println("Stop..");
   motor3.run(RELEASE);
   motor4.run(RELEASE);
}
