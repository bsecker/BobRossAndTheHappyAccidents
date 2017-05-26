#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"


void stop_motors() {
    set_motor(1, 0);
    set_motor(2, 0);
    printf("stopped motors!");
}

// turn left until it reaches
void turn_left(int times) {
    stop_motors();
    sleep1(0, 200000);

    // move backwards
    set_motor(1, TURN_SPEED); // assuming it turns to the left, TODO
    set_motor(2, TURN_SPEED);

    sleep1(0, TURN_DURATION);

    // stop again
    stop_motors();
}

void turn_right() {
    stop_motors();
    sleep1(0, 200000);

    // move backwards
    set_motor(1, -TURN_SPEED); // assuming it turns to the left, TODO
    set_motor(2, -TURN_SPEED);

    sleep1(0, TURN_DURATION);

    // stop again
    stop_motors();
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



// stop temporarily, 1 = right 0 = left
void go_back(bool direction){
    printf("Moving backwards in Dir: %d \n", direction);
    if (direction) {
        // stop temporarily
        stop_motors();
        sleep1(0, 200000);

        // move backwards
        set_motor(1, -BACK_SPEED);
        set_motor(2, BACK_SPEED*BACK_MOD);
        sleep1(0, BACK_TIME);

        // stop again
        stop_motors();
    }
    else {
        // stop temporarily
        stop_motors();
        sleep1(0, 200000);

        // move backwards
        set_motor(1, -BACK_SPEED*BACK_MOD);
        set_motor(2, BACK_SPEED);
        sleep1(0, BACK_TIME);

        // stop again
        stop_motors();
    }
}

void turn_around() {
    stop_motors();
    sleep1(0, 200000);

    // move backwards
    set_motor(1, BACK_SPEED);
    set_motor(2, BACK_SPEED);

    sleep1(0, 500000);

    // stop again
    stop_motors();
}
