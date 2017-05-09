#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

// !TODO once this works, put into main program


int main() {
	//init();
	//take_picture();
	

	
	int cameraWidth = 320;
	int cameraHeight = 240;

	int cameraLine1White[ CAMERA_WIDTH ]; //where 1 is white, 0 is black
	//int cameraLine1Red[ CAMERA_WIDTH ]; 
	
	

	// get line of pixels at y=120
	for (int _i = 0; _i < CAMERA_WIDTH, _i ++){
		char pix = get_pixel( 160, 120, 3);
		
		// convert values to 1's and 0s 
		if (pix >= WHITE_TOLERANCE) {
			cameraLine1White[_i] = 1;	
		}
		else {
			cameraLine1White[_i] = 0;
		}
		
	}


	//display_picture(50, 500000);
	// Print out entire line (debugging)
	for (int _i = 0; _i < CAMERA_WIDTH, _i ++) {
		printf("%d\n", cameraLine[_i] );
	}

		
	sleep1(0,500000);	
	return 0;
}

int get_error(int[] linePoints) { //unsure on argument syntax for passing in arrays
	/* With linePoints input, find error value TODO*/
	int error = 0;
	int whitePixels = 0;
	int actual_error = 0;

	// iterate through data and calculate error	
	for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
		if (linePoints[_i] == 1) {
			error += (i - (CAMERA_WIDTH/2));
			whitePixels ++;
		}
	}
	// if no white, dont do anything ideally
	if (whitePixels > 0) {
		actual_error = error/whitePixels;
	}
	
	return actual_error;	
}










}




