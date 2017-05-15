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

    // track completion of the line maze and block maze
    bool finished_line_maze = false;
    bool finished_block_maze = false;

    take_picture();
//    display_picture(2,0);

 	// Line follower loop. will run until finished line maze
	while (!finished_line_maze) {
	printf("\n\n");
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
//		printf("white here \n");
		whitePixels1 ++;
            }
            if (cameraLine2White[_i] == 1) {
                error2 += (_i - (CAMERA_WIDTH / 2));
		whitePixels2 ++;
            }
        }

        // change error for each line to average error
        if (whitePixels1 > 0) {
            error1 = error1/whitePixels1;
//	    printf("Error 1: %f \n", error1);
        }
        if (whitePixels2 > 0) {
            error2 = error2/whitePixels2;
        }

        // calculate derivative - difference in errors
        float difference = error2 - error1; //TODO should be absolute? do we care about sign
        printf("line difference: %f \n ", difference);


        // TODO: we need to test Kp and Kd.
        // Start by making Kp perfect and then changing Kd after that.

        // set motors if we have white pixels.
        if (whitePixels1 > 0) {
	    //printf("Whitepixels: %d \n ", whitePixels1);
            printf("Error: Kp = %f Kd = %f Total = %f \n", (error1 * Kp), (difference * Kd), (error1 * Kp) + (difference * Kd));
            set_motors((error1 * Kp) + (difference * Kd));
        }
        // if no white pixels, go back and search for it!
        else {
            // back up a bit
            printf("Moving backwards. \n");
           // backup_motors();
        }

        // break loop if over red part of maze
        if (is_on_red()) {
            ;
        }

        sleep1(0,10000); // 0.01 seconds delay - TODO do we need this?
	}

    printf("Finished line following, starting maze \n");

    while (!finished_block_maze) {
        ;
    }


    // cleanup
    stop_motors();
	return 0;
}
