#include "SR04.h"

#define LEFT_US_SENSOR_TRIG 16
#define LEFT_US_SENSOR_ECHO 15
#define FRONT_US_SENSOR_TRIG 18
#define FRONT_US_SENSOR_ECHO 17

#define NO_OBSTACLE 0
#define OBSTACLE 1

#define DISTANCE 14
#define FRONT_DISTANCE 30

void CONTINUE_WALL(void);
void CONTINUE_WALL_FRONT(void);
int GET_LEFT_US_STATUS(void);
int GET_FRONT_US_STATUS(void);
void INITIALIZE_WALL_FRONT(void);
void INITIALIZE_WALL(void);
void WF_PID_STOP (void);
void WALL_FOLLOWER_L_F_PID (IRrecv irrecv);

extern SR04 sr04_left;
extern SR04 sr04_front;





