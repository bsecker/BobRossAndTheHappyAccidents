# AVC challenge

## Programming Notes

 - Please use TODO in comments (IDEs can track them this way)
 - main file is main.cpp - entry point into robot program.
 - comments: WHY a particular piece of code does what, not just how
 - 4 SPACE indents, modularize code as much as possible


## Useful Links
AVC Plan - https://docs.google.com/document/d/1ohWP7eW6QpgYz0TD7oAWesx7KC22hXZOzdn1T1iDFE0/edit?usp=sharing


## Progress Summary
###  Week One
Ben:
 - Github Repo Made
 - RPi SSH and auto pull/build script made (not finished)
 - Test scripts made for camera and motors
Keanu:

Daniel:
 - CAD designing and building prototype robot

Mat:
 - CAD designing and building battery holder for robot

### Week Two
Ben:
 - P component of PID implemented, working on D component of PID and refining P component.
 - Fixed issue with motors running full when set to 0

Daniel:
 - Base Completed(1st time it didnt print properly), Key hardware for Quadrant one and two mounted, (needs trouble-shooting)
 - print side IR sensor mounts
 
Mat:
 - Battery mount designed and completed(had to print in a different orientation to stop the base from warping), (TODO): Design and print front mount for IR sensor and help trouble-shoot
 
Keanu:
 - Refining P and D componenets of PID implementation, bugfixing.
 - Fixed issue with motors running full when set to 0
(guys please update this so its not a pain in the ass when we get around to writing the progress report)
current IP: 10.140.93.191


### How we are going to do the second part of the maze


1) new loop once the error becomes massive. Need to make sure we dont accidentally get this anywhere else!
2) measure line at either side of camera
3) if on left side: turn left
3) if at T: turn left:
4) if on right but not on left: turn right

turning: loop to turn until error is close to zero.

THIS NEEDS TO BE UPDATED.