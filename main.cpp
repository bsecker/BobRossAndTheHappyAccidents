#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "E101.h"

#include "camera_functions.cpp"
#include "motor_functions.cpp"
#include "constants.h"
#include "network_functions.cpp"


// Main file for running Robot program.

int main() {
    init();

    open_gate();

    // track completion of the line maze and block maze
    bool finished_line = false;
    bool finished_line_maze = false;
    bool finished_block_maze = false;

 	   // Line follower loop. will run until finished line maze (including multipath maze)
	   while (!finished_line) {

	      printf("\n\n");
        int cameraLine1White[CAMERA_WIDTH];
        int cameraLine2White[CAMERA_WIDTH]; // slightly above line 1

        take_picture();
        // set both camera lines
        get_picture(cameraLine1White, CAMERA_HEIGHT/2);
        get_picture(cameraLine2White, CAMERA_HEIGHT/2 - 70);

        // track errors and white pixels
        float error1 = 0;
        float error2 = 0;
        int *whitePixels1 = 0;
        int *whitePixels2 = 0;
        //
        //int *whitePixels1Pointer = &whitePixels1;
        //int* whitePixels2Pointer = &whitePixels2;

        // get the errors for each line
        error1 = set_error(cameraLine1White, whitePixels1);
        error2 = set_error(cameraLine2White, whitePixels2);
	
        // calculate derivative - difference in errors
        float difference = error2 - error1; //TODO should be absolute? do we care about sign
        printf("line difference: %f \n ", difference);

        // track if there is a line left or right of the current line.
        bool line_left = is_line_left();
        bool line_right = is_line_right();

        // TODO: check profiler for these functions. They could add quite a bit of processing..


        // set motors if we have white pixels.
        if (whitePixels1 > 0) {
	        printf("Whitepixels: %d \n ", whitePixels1);
            printf("Error: Kp = %f Kd = %f Total = %f \n", (error1 * Kp), (difference * Kd), (error1 * Kp) + (difference * Kd));
            set_motors((error1 * Kp) + (difference * Kd));
        }
        // if no white pixels, go back and search for it!
        else {
            // back up a bit
            printf("Moving backwards. \n");
            backup_motors();				
        }


        sleep1(0,1000); // 0.01 seconds delay - TODO do we need this?
	}

    // cleanup
    stop_motors();
	  return 0;
}
