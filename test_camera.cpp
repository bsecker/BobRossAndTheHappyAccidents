#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

// !TODO once this works, put into main program


int main() {
	init();
	take_picture();
	


	int cameraWidth = 320;
	int cameraHeight = 240;
		
	

	// get line of pixels
	for (int _i = 0; _i < 320, _i ++){
		char pix = get_pixel( 160, 120, 3);
	
	}


	//display_picture(50, 500000);
	printf("%d\n", pix);
	
	sleep1(0,500000);	
	return 0;
}






