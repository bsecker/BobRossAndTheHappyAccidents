
// Constants for entire Robot
// Please put constants in CAPS
#pragma once


// Camera
const int CAMERA_WIDTH = 320;
const int CAMERA_HEIGHT = 240;
const int WHITE_TOLERANCE = 115;
const int RED_TOLERANCE = 200;
const int SIDE_LINE_TOLERANCE = 30;

// Network
char SERVER_ADDRESS[] = "130.128.150.128"; //this and password couldnt be constants could just use local variables in network_functions file
const int SERVER_PORT = 1024;
char SERVER_PASSWORD[24] = "Please";

// Robot
const int MOTOR_SPEED = 35;
const int BACK_SPEED = 35;
const int MOTOR_MAX = 250; // max motor speed
const int MOTOR_MIN = -250; // min motor speed
const int BACK_MOD = 0.5;
const int BACK_TIME = 250000;
const int TURN_DURATION = 500000;
const int TURN_SPEED = 35;


// PID
// Guys we gotta play with this until its perfect! can't get much further without it!
const float Kp = 0.1; // constant of proportionality
const float Ki = 0.05; // not so useful for avc
const float Kd = 0.08;

// IR
const int MIN_FRONT_IR_DIST = 500;
const float IR_Kp = 0.02;
const float IR_Kd = 0.01; // change these
const int CLEARING_THRESHOLD = 300;

// pins
const int LEFT_IR_PIN = 1;
const int FRONT_IR_PIN = 2;
const int RIGHT_IR_PIN = 3;
