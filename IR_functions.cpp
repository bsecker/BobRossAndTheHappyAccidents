#include <stdio.h>
#include <time.h>
#include "E101.h"


// return average of three sensor readings.
int read_IR(int pin) {
	int read1;
	int read2;
	int read3;
	int average;
	 read1 = read_analog(pin);
	 sleep1(0,500);
	 read2 = read_analog(pin);
	 sleep1(0,500);
	 read3 = read_analog(pin);
	 average = ((read1+read2+read3)/3);

	return average;
}

//returns true if there is an empty space in direction of Ir sensor
bool is_gap(int pin){
	return read_IR(pin) > CLEARING_THRESHOLD;
}

// get error from side IR sensors
int getIR_error(int left_reading, int right_reading){
	int IR_error=((1024-right_reading)-(1024-left_reading));
	return IR_error;
}

// return distance to front of sensor
int get_front_IR() {
	return read_IR(FRONT_IR_PIN);
}

// pause robot until door is cleared
void wait_until_door() {
    while (get_front_IR() > MIN_FRONT_IR_DIST) {
        stop_motors();
        sleep1(0, 500000);
    }
}

//1 is left, 2 is middle and 3 is right}
