#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

// don't need this anymore - but keeping for a while.
//float get_error(int linePoints[]) {
//    /* With linePoints input, find error value */
//    float error = 0;
//    int whitePixels = 0;
//    float actual_error = 0;
//
//    // iterate through data and calculate error
//    for (int _i = 0; _i < CAMERA_WIDTH; _i++) {
//        if (linePoints[_i] == 1) {
//            error = error + (_i - (CAMERA_WIDTH / 2));
//            whitePixels++;
//        }
//    }
//
//    // if no white, dont do anything
//    if (whitePixels > 0) {
//        actual_error = error / whitePixels;
//        return actual_error;
//    }
//
//    // return 0 if no white pixels.
//    // (In theory, if the line is perfectly in the middle there is no error, so whatevers calling this function
//    // wont know whether the error returned is perfect or no white at all. However because we are taking a picture
//    // of the entire row (using all the pixels) we can be very certain that we will never get a perfectly centered line.
//    return 0;
//
//}

// modify cameraLine to have 1's and 0's instead of raw camera values.
void get_picture(int *cameraLine, int y) {
    // debugging: display picture
    //display_picture(5, 0);

    // get line of pixels
    for (int _i = 0; _i < CAMERA_WIDTH; _i++) {

        char pix = get_pixel(y, _i, 3);
        // convert values to 1's and 0s
        if (pix >= WHITE_TOLERANCE) {
            cameraLine[_i] = 1;
        } else {
            cameraLine[_i] = 0;
        }
    }
}

// Modify cameraLine to have 1's and 0's instead of raw camera, but for a vertical line.
void get_picture_vert(int *cameraLine, int x) {
    for (int _i = 0; i < CAMERA_HEIGHT, _i++) {
        char pix = get_pixel(_i, x, 3);

        if (pix >= WHITE_TOLERANCE) {
            cameraLine[_i] = 1;
        }
        else {
            cameraLine[_i] = 0;
        }
    }
}

bool is_line_left() {
    int cameraLineLeft[CAMERA_HEIGHT];

    get_picture_vert(cameraLineLeft, 2);

    int left_line_size = 0;

    for (int i = 0; i < CAMERA_HEIGHT; i++) {
        if (cameraLineLeft[i] == 1) {
            left_line_size++;
        }
    }

    return (left_line_size > SIDE_LINE_TOLERANCE);

}

bool is_line_right() {
    int cameraLineRight[CAMERA_HEIGHT];

    get_picture_vert(cameraLineRight, 2);

    int right_line_size = 0;

    for (int i = 0; i < CAMERA_HEIGHT; i++) {
        if (cameraLineRight[i] == 1) {
            right_line_size++;
        }
    }

    return (right_line_size > SIDE_LINE_TOLERANCE);
}


/* scale brightness of all points on pixel down or up depending on lighting conditions.*/
void normalise_camera_brightness() {
    ;
}

// return true if the center of the camera sees red
// MATT IS DOING THIS
bool is_on_red(){
    return get_pixel( CAMERA_WIDTH/2, CAMERA_HEIGHT/2, 0) > RED_TOLERANCE;
}

// return true if at a + junction
bool is_over_line(int whitepixels) {
    return (whitepixels > CAMERA_WIDTH-MAZE_TOLERANCE);
}




