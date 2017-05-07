#!/bin/bash

# Potentially dangerous shell script to wipe the RPi, copy latest code from source PC and recompile.


# arguments:
# copy_rpi.sh [source folder]

IP=pi@10.140.120.159
DIRPI=/home/pi/AVC/
DIRPC=$1

echo "Deleting old c files"
ssh -x $IP 'cd $DIRPI; rm *.cpp'
echo "Transferring files to pi"
rsync -e 'ssh -ax' -av $DIRPC $IP:$DIRPI
echo "compiling code"
ssh -x $IP 'cd $DIRPI; make; ./start'
