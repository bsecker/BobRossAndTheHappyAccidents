#include <stdio.h>
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
    int previous error;


    int _temp__step = 0;
	// Main game loop. Will run until finished maze

    // Temporary: do this 500 times and then stop program
	while (_temp__step < 500) {
        int cameraLine1White[CAMERA_WIDTH]; //where 1 is white, 0 is black

        get_picture(cameraLine1White);

        int error = get_error(cameraLine1White);
        printf("Error: %d\n", error);



        // error !=0 = there are white pixels.
        if (error != 0) {
            set_motors(error * Kp);
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
