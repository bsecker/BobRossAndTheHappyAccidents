#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

// turn left until it reaches
void turnleft(int times) {
    int speed = 50; // change these values
    int duration = 1000000;

	// set left motor to -speed and right motor to speed
	set_motor(1, -speed);
	set_motor(2, speed);
	
	// sleep for specified time
	sleep1(0, duration);
	
	// stop motors
	set_motor(1, 0);
	set_motor(2, 0);
}

void turnright() {
    int speed = 50; // change these values
    int duration = 1000000;

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
    int motor_1 = (int)((double)MOTOR_SPEED+proportional_error);
    int motor_2 = (int)((double)MOTOR_SPEED-proportional_error);

    // limit at -250 to 250 for sanity
    if (motor_1 > MOTOR_MAX) motor_1=MOTOR_MAX;
    if (motor_1 < MOTOR_MIN) motor_1=MOTOR_MIN;
    if (motor_2 > MOTOR_MAX) motor_2=MOTOR_MAX;
    if (motor_2 < MOTOR_MIN) motor_2=MOTOR_MIN;

    // print out values (debugging)
    printf("Motor 1 speed: %d \n", motor_1);
    printf("Motor 2 speed: %d \n", motor_2);

    // set motors
    set_motor(1, motor_1);
    set_motor(2, -motor_2);


}

void stop_motors() {
    set_motor(1, 0);
    set_motor(2, 0);
    printf("stopped motors!");
}

void backup_motors(){
    // stop temporarily
    stop_motors();
    sleep1(0,200000);

    // move backwards
    set_motor(1, -BACK_SPEED);
    set_motor(2, -BACK_SPEED);
    sleep1(0,500000);

    // stop again
    stop_motors();
}
