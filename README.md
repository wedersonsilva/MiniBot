# MiniBOT

MiniBOT is a small robot (10 cm x 10 cm) originally created to battle in a mini autonomous sumô fight! 
However, nowadays it's used for other purposes also.

## Sumo Battle

The "MiniBOT-Sumo.ino" code is used to battle into a mini (10 cm x10 cm) autonomous sumo fight.

When started, the robot waits for 5 seconds and then starts to look for "enemies" randomically. If it finds it, go forward.

## Bluetooth Control

The "MiniBOT-Bluetooth.ino" code is used to control MiniBOT using a bluetooth.

A bluetooth module has to be installed on the robot directly and an app installed on an Android smartphone.

## Glove Control

The "MiniBOT-Glove.ino" code is used to control MiniBOT using a pair of Radio Frequency (433MHz) transmitter.

A receiver module has to be installed on the robot directly and the transmitter is installed on a glove of the _private_ project **Low Cost Flex Sensor** ( [lcfs](github.com/wedersonsilva/lcfs) )
