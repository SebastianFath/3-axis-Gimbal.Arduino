# 3-axis-Gimbal.Arduino
Software for a 2-IMU, 3-Axis Gimbal for Arduino microcontroller

The goal of the project is to create a so-called "3-axis-Gimbal".
A 3-axis-Gimbal is a Stabilizer for cameras, similar to a Flycam but utilizes Motors to compensate
different Movements that afflict the moviepicture of the camera.

The Software Part, we decided to use Arduino 101 needs to realize, which way the Gimbal needs to Compensate
and communicate this to the 3 Motors that controll the axes.

# Codestructure

the main Code is written in the following file:
  master/sketches/sketch_jan30a/sketch_jan30a.ino
  https://github.com/SebastianFath/3-axis-Gimbal.Arduino/blob/master/sketches/sketch_jan30a/sketch_jan30a.ino
side codes and to Develop are in either 
  master/sketches or
  master/processing , depending on in wich language and on what plattform they are written/ executed.

