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

    int cameraLine1White[CAMERA_WIDTH]; //where 1 is white, 0 is black

    get_picture(cameraLine1White);

    int error = get_error(cameraLine1White)
    printf("Error: %d\n", error);

    set_motors(error);

    sleep1(5,0);
    stop_motors();


	// Main game loop. Will run until finished maze
	while (finished_maze == false) {
        finished_maze = true; // quit straight away for now
	}


    // cleanup
    stop_motors();
    stop();
	return 0;
}
