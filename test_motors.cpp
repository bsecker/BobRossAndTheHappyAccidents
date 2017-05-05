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
	stop(1);
	stop(2);
}

int main() {
	init();
	turnleft(500000, 255);
	return 0;
}
