RobotArm
========

Robot Arm software running on HCS12 and using PID controller. Created by Luke Frisken. Credit goes to Mathias Nielsen for the PWM module!

Sources are in the /Sources folder.

More comments in the code on the way, has been a bit of a rush to get this assignment working for performance assessment.

Structs are all statically allocated because HCS12 doesn't seem to support malloc,
and it doesn't seem like a good idea on a microcontroller anyway.
