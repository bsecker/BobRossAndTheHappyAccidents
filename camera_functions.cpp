#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "constants.h"

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
    for (int _i = 0; _i < CAMERA_HEIGHT; _i++) {
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

    get_picture_vert(cameraLineRight, CAMERA_WIDTH - 2);

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
// middle 160ish pix.

bool is_on_red(){
    int redsum = 0;
    int bluesum = 0;
    int greensum = 0;
    for (int i = 80; i < CAMERA_WIDTH - 80; i++) {
        redsum += get_pixel(CAMERA_HEIGHT/2, i, 0);
        greensum += get_pixel(CAMERA_HEIGHT/2, i, 1);
        bluesum += get_pixel(CAMERA_HEIGHT/2, i, 2);
    }
	//printf("%d %d %d", redsum/160, greensum/160, bluesum/160);
    return ((redsum/160) > RED_TOLERANCE && (greensum/160) < 100 && (bluesum/160) < 100);
}

// return true if at a + junction (depreciated)
bool is_over_line(int whitepixels) {
    return (whitepixels > CAMERA_WIDTH-30);
}
