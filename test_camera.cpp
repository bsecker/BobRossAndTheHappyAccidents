#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	take_picture();
	
	char pix = get_pixel( 160, 120, 3);
	printf("%d\n", pix);
	
	sleep1(0,500000);	
	return 0;
}






