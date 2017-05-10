#include <stdio.h>
#include <time.h>
#include "E101.h"

int main()
{
int read_IR(int a)	
init();
	int read1;
	int read2;
	int read3;
	int average;
	 read1 = read_analog(a);
	 sleep1(0,500);
	 read2 = read_analog(a);
	 sleep(0,500);
	 read3 = read_analog(a);
	 average = ((read1+read2+read3)/3);	


  
	return average;
}

	
	
