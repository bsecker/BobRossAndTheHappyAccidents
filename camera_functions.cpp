#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

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

    // return 0 if no white pixels.
    // (In theory, if the line is perfectly in the middle there is no error, so whatevers calling this function
    // wont know whether the error returned is perfect or no white at all. However because we are taking a picture
    // of the entire row (using all the pixels) we can be very certain that we will never get a perfectly centered line.
    return 0;

}

void get_picture(int *cameraLine1White) {
    take_picture();

    // debugging: display picture
    display_picture(5, 0);

    // get line of pixels
    for (int _i = 0; _i < CAMERA_WIDTH; _i++) {

        char pix = get_pixel(CAMERA_HEIGHT / 2, _i, 3);
        //printf("%d\n", pix);

        // convert values to 1's and 0s
        if (pix >= WHITE_TOLERANCE) {
            cameraLine1White[_i] = 1;
        } else {
            cameraLine1White[_i] = 0;
        }
    }
    // Print out entire line (debugging)
    printf("done reading camera");
    //for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
    //    printf("%d\n", cameraLine1White[_i]);
    //}
}









