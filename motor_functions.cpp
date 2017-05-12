#include <stdio.h>
#include <time.h>
#include "E101.h"

void turnleft( int duration, int speed) {
	// set left motor to -speed and right motor to speed
	set_motor(1, -speed);
	set_motor(2, speed);
	
	// sleep for specified time
	sleep1(0, duration);
	
	// stop motors
	set_motor(1, 0);
	set_motor(2, 0);
}

void turnright( int duration, int speed) {
    // set left motor to -speed and right motor to speed
    set_motor(1, speed);
    set_motor(2, -speed);

    // sleep for specified time
    sleep1(0, duration);

    // stop motors
    set_motor(1, 0);
    set_motor(2, 0);
}

void set_motors(int proportional_error) {
    printf("Motor 1 speed: %d \n", MOTOR_SPEED+proportional_error);
    printf("Motor 2 speed: %d \n", MOTOR_SPEED-proportional_error);

//    set_motor(1, MOTOR_SPEED + proportional_error);
//    set_motor(2, -MOTOR_SPEED - proportional_error);
//    does this need to be set_motor(2, -MOTOR_SPEED - proportional_error);
}

void backup_motors(){
    // stop temporarily
    set_motor(1, 0);
    set_motor(2, 0);
    sleep1(0,20000); // TODO check right value

    // TODO finish

}

void stop_motors() {
    set_motor(1, 0);
    set_motor(2, 0);
    printf("stopped motors!");
}