#include <stdio.h>
#include <time.h>
#include "E101.h"

#include "camera_functions.cpp"
//#include "motor_functions.cpp"
#include "constants.h"

// Main file for running Robot program.

int main() {
    init();

    int cameraLine1White[CAMERA_WIDTH]; //where 1 is white, 0 is black

    get_picture(&cameraLineWhite);


	// Main game loop. Will run until finished maze
	while (finished_maze == false) {
		;		
	}
	return 0;
}
