#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

// TODO once this works, put into main program


int main() {
    init();
    take_picture();

    int cameraLine1White[CAMERA_WIDTH]; //where 1 is white, 0 is black

    // get line of pixels
    for (int _i = 0; _i < CAMERA_WIDTH - 1; _i++) {

        char pix = get_pixel(CAMERA_HEIGHT / 2, _i, 3);
        printf("%d\n", pix);

        // convert values to 1's and 0s
        if (pix >= WHITE_TOLERANCE) {
            cameraLine1White[_i] = 1;
            printf("One!!\n");
        } else {
            cameraLine1White[_i] = 0;
        }

    }


    display_picture(5, 0);
    // Print out entire line (debugging)
    printf("done reading, printing out all lines...");
    for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
        printf("%d\n", cameraLine1White[_i]);
    }

    printf("error: %d \n", get_error(cameraLine1White));

    sleep1(0, 500000);
    return 0;
}

int get_error(int linePoints[]) {
    /* With linePoints input, find error value */
    int error = 0;
    int whitePixels = 0;
    int actual_error = 0;

    // iterate through data and calculate error
    for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
        if (linePoints[_i] == 1) {
            error += (_i - (CAMERA_WIDTH / 2));
            whitePixels++;
        }
    }
    // if no white, dont do anything
    if (whitePixels > 0) {
        actual_error = error / whitePixels;
        return actual_error;
    }
    return 0;
    // TODO: properly handling exceptions (if no white pixels)

}












