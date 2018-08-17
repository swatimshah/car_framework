#include "SR04.h"

#define LEFT_US_SENSOR_TRIG 16
#define LEFT_US_SENSOR_ECHO 15
#define FRONT_US_SENSOR_TRIG 18
#define FRONT_US_SENSOR_ECHO 17

#define NO_OBSTACLE 0
#define OBSTACLE 1

#define WF_SPEED 180
#define WF_NO_SPEED 0

#define WF_DISTANCE 10
#define WF_FRONT_DISTANCE 16

void WF_LEFT (void);
void WF_RIGHT (void);
void WF_CONTINUE_WALL (void);
void WF_INITIALIZE_WALL(void);
int WF_GET_LEFT_US_STATUS(void);
int WF_GET_FRONT_US_STATUS(void);
void WF_STOP (void);
void WALL_FOLLOWER (IRrecv irrecv);

extern SR04 wf_sr04_left;
extern SR04 wf_sr04_front;





