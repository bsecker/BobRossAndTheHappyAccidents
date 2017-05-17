#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "E101.h"
/*
#include "camera_functions.cpp"
#include "motor_functions.cpp"
#include "constants.h"
*/

int main(){
    init();
    set_motor(1,-100);
    set_motor(2,100);
    sleep1(3,0);
    set_motor(1,0);
    set_motor(2,0);
    //stop_motors();
    return 0;
}
