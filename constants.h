
// Constants for entire Robot
// Please put constants in CAPS
#pragma once


// Camera
const int CAMERA_WIDTH = 320;
const int CAMERA_HEIGHT = 240;
const int WHITE_TOLERANCE = 128;
const int RED_TOLERANCE = 200; // change this

// Network
char SERVER_ADDRESS[] = "130.128.150.128"; //this and password couldnt be constants could just use local variables in network_functions file
const int SERVER_PORT = 1024;
char SERVER_PASSWORD[24] = "Please";


// Robot
const int MOTOR_SPEED = 40;
const int BACK_SPEED = 10;
const int MOTOR_MAX = 250; // max motor speed
const int MOTOR_MIN = -250; // min motor speed

// PID
const float Kp = 0.05; // constant of proportionality
const float Ki = 0.05; // not so useful for avc
const float Kd = 0.55;

