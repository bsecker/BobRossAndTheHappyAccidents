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

void set_motors(int error) {
    set_motor(1, MOTOR_SPEED + error);
    set_motor(2, MOTOR_SPEED - error);
}

void stop_motors() {
    set_motor(1, 0);
    set_motor(2, 0);
}