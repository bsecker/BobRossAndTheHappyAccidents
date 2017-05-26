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
    bool finished_maze = false;

 	   // Line follower loop. will run until finished line maze (including multipath maze)
	   while (!finished_line) {

	      printf("\n\n");
        int cameraLine1White[CAMERA_WIDTH];
        int cameraLine2White[CAMERA_WIDTH]; // slightly above line 1

        take_picture();
        // set both camera lines
        get_picture(cameraLine1White, CAMERA_HEIGHT/2);
        get_picture(cameraLine2White, CAMERA_HEIGHT/2 - 10);

        // track errors and white pixels
        float error1 = 0;
        float error2 = 0;
        int whitePixels1 = 0;
        int whitePixels2 = 0;

       // calculate error
       // iterate through data and calculate error
       for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
           if (cameraLine1White[_i] == 1) {
               error1 += (_i - (CAMERA_WIDTH / 2));
               whitePixels1++;
           }
           if (cameraLine2White[_i] == 1) {
               error2 += (_i - (CAMERA_WIDTH/2));
               whitePixels2++;
           }
       }

       // change the error variable to the average error
       if (whitePixels1 > 0) {
           error1 = (int)error1 / whitePixels1;
       }
       // change the error variable to the average error
       if (whitePixels2 > 0) {
           error2 = (int)error2 / whitePixels2;
       }

        // calculate derivative - difference in errors
        float difference = error2 - error1; //TODO should be absolute? do we care about sign
        printf("line difference: %f \n ", difference);

        // track if there is a line left or right of the current line.

       bool line_left = is_line_left();
       bool line_right = is_line_right();


//	printf("Left: %d, Right: %d \n", line_left, line_right);
        // set motors if we have white pixels.
        if (whitePixels1 > 0 && whitePixels2 > 0) {
	        printf("Whitepixels: %d \n ", whitePixels1);
            printf("Error: Kp = %f Kd = %f Total = %f \n", (error1 * Kp), (difference * Kd), (error1 * Kp) + (difference * Kd));
            set_motors((error1 * Kp) + (difference * Kd));
        }
        // if no white pixels, go back and search for it!
        else {
            // back up a bit
            printf("Moving backwards. \n");

            if (line_left) {
                go_back(1);
            }
            else if (line_right) {
                go_back(0);
            }
            else {
                // turn around
                turn_around();
            }
        }
       // go to next loop if over red line.
       if (is_on_red()) {
           break;
       }


        sleep1(0,1000); // 0.01 seconds delay - TODO do we need this?
	}


    int last_error = 0;

    // do maze
    while (!finished_maze) {
        take_picture();
        int left = read_IR(1);
        int right = read_IR(3);

        // calculate error
        int error = getIR_error(left, right);
        int difference = error - last_error;


        int total_error = (error * IR_Kp) + (difference * IR_kd);
        set_motors(total_error);

        // hug the right wall
        // check up against the wall
        if (get_front_IR < MIN_FRONT_IR_DIST){
            if (is_gap(RIGHT_IR_PIN)) {
                turn_right();
            }
            else if (is_gap(LEFT_IR_PIN)) {
                turn_left();
            }
            else {
                turn_around();
            }
        }

        // go to next loop if over red line.
        if (is_on_red()) {
            wait_until_door();
        }

        // finally, change last error to the current error
        last_error = error;

    }

    // cleanup
    stop_motors();
	  return 0;
}
