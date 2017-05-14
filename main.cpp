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

	// Main game loop. Will run until finished maze

	while (!finished_maze) {

        int cameraLine1White[CAMERA_WIDTH];
        int cameraLine2White[CAMERA_WIDTH]; // slightly above line 1

        take_picture();

        // set both camera lines
        get_picture(cameraLine1White, CAMERA_HEIGHT/2);
        get_picture(cameraLine2White, CAMERA_HEIGHT/2 - 10);

        // track errors
        float error1 = 0;
        float error2 = 0;
        int whitePixels1 = 0;
        int whitePixels2 = 0;

        // iterate through data and calculate error
        for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
            if (cameraLine1White[_i] == 1) {
                error1 += (_i - (CAMERA_WIDTH / 2));
            }
            if (cameraLine2White[_i] == 1) {
                error2 += (_i - (CAMERA_WIDTH / 2));
            }
        }

        // change error for each line to average error
        if (whitePixels1 > 0) {
            error1 = error1/whitePixels1;
        }
        if (whitePixels2 > 0) {
            error2 = error21/whitePixels1;
        }

        // calculate derivative - difference in errors
        int difference = error2 - error1; //TODO should be absolute? do we care about sign
        printf("line difference: %d \n ", difference);


        // TODO: we need to test Kp and Kd.
        // Start by making Kp perfect and then changing Kd after that.

        // set motors if we have white pixels.
        if (whitePixels1 > 0) {
            printf("Error: Kp = %d Kd = %d Total = %d \n", (error1 * Kp), (difference * Kd), (error1 * Kp) + (difference * Kd));
            set_motors((error1 * Kp) + (difference * Kd));
        }
        // if no white pixels, go back and search for it!
        else {
            // back up a bit
            printf("Moving backwards.");
            backup_motors();
        }

        sleep1(0,10000); // 0.01 seconds delay - TODO do we need this?
	}


    // cleanup
    stop_motors();
	return 0;
}
