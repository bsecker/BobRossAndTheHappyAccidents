#include <stdio.h>
#include <time.h>
#include "E101.h"

int main()
{
	init();
	
	int adc_reading;
	int adc_reading2;
	int adc_reading3;
	
	for(int i=0;i<100;i++){
		adc_reading = read_analog(0);
		printf("0: %d\n", adc_reading);
		sleep1(1,0);
		adc_reading2 = read_analog(1);
		printf("1: %d\n", adc_reading2);
		sleep1(1,0);
		adc_reading4 = read_analog(2);
		printf("2: %d\n", adc_reading3);
		sleep1(1,0);
		
}
  
	return 0;
}
	







