#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "E101.h"

#include "camera_functions.cpp"
#include "motor_functions.cpp"
#include "constants.h"

// Main file for running Robot program.

int main() {
    init();

    // track completion of the maze
    bool finished_maze = false;

    int total_error = 0;


    int _temp__step = 0;
	// Main game loop. Will run until finished maze

    // Temporary: do this 500 times and then stop program
	while (_temp__step < 500) {
        int cameraLine1White[CAMERA_WIDTH]; //where 1 is white, 0 is black
        int cameraLine2White[CAMERA_WIDTH]; // slightly above line 1

        take_picture();

        // set both camera lines
        get_picture(cameraLine1White, CAMERA_HEIGHT/2);
        get_picture(cameraLine2White, CAMERA_HEIGHT/2 - 10);

        int error_1 = get_error(cameraLine1White);
        int error_2 = get_error(cameraLine2White);
        printf("Error 1: %d ", error_1);
        printf("Error 2: %d\n", error_2);

        int difference = abs(error_1 - error_2);
        printf("difference: %d \n", difference);

        // error !=0 = there are white pixels.
        if (error_1 != 0) {
            set_motors((error_1 * Kp) + (difference * Kd));
        }
        // if no white pixels, gone off course - search for it!
        else {
            // back up a bit
            backup_motors();
        }

        _temp__step++;
        sleep1(0,250000); // 0.25 seconds delay

	}

    // somehow this causes the program to fail - talk to Arthur about this.
    sleep1(5,0);
    set_motor(1, -100);
    sleep1(1,0);
    set_motor(2, -100);
    sleep1(1,0);
    stop_motors();


    // cleanup
//    stop_motors();
	return 0;
}
