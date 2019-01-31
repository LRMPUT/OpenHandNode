# Open Hand Controller Node

### Preparation 
To run this controller, it is necessary to follow all instructions in "README.md" file in the "dynamixel_servos" folder.

Next, please open new terminal and call:
```
$ source devel/setup.bash
```


### Content of package
The main executable file is the open_hand_controller node, which communicates with the dynamixel_servos node using topics:
```
/servo_control_commands
/servo_control_info
```
also sends and receives messages from ROS by the topics:
```
/contr_to_ros
/ros_to_contr
```

There are two additional nodes: test_talker and test_listener. Their purpose is testing node for data correctness, which go through it between ROS and open_hand_controller.

### open_hand_controller

To run the controller, use the command:
```
$ rosrun open_hand_controller open_hand_controller
```

Two separate messages ros_to_contr and contr_to_ros were designed for communication with the ROS system, which have a structure adequate to the tasks being performed. Additionally you can communicate with the gripper using close_hand messages.
```
ros_to_contr

float64 Finger1Position
float64 Finger2Position
float64 Finger3Position
float64 FingersRotationPosition

float64 Finger1Torque
float64 Finger2Torque
float64 Finger3Torque
float64 FingersRotationTorque

bool Finger1Enable
bool Finger2Enable
bool Finger3Enable
bool FingersRotationEnable
```
To change the set position, enter the appropriate value in radians in the Finger_x_Position field (where _x_ is the servo no.) And activate the appropriate servo in the Finger_x_Enable field.

Servomechanisms work in the position and torque control mode, so you should also provide the maximum torque that can be used to perform a given motion. This value should be in the range from 0 to 1.

Data for servomechanisms should be sent when we want to change any of the parameters. The program is protected against some cases of entering bad values.


```
contr_to_ros

float64 Finger1Position
float64 Finger2Position
float64 Finger3Position
float64 FingersRotationPosition

float64 Finger1Velocity
float64 Finger2Velocity
float64 Finger3Velocity
float64 FingersRotationVelocity

float64 Finger1Torque
float64 Finger2Torque
float64 Finger3Torque
float64 FingersRotationTorque
```

In case of some reason the interruption with the servo will be interrupted, the last updated data on the state of the mechanism will be sent in the messages.

Value Position contain an angle in radians, Velocity current speed in individual drives, and Torque current torque calibrated to a value from 0 to 1.

```
close_hand

bool FingersClose
float64 FingersTorque
```

### Start-up

To run the comunication with servos:

```
$ rosrun dynamixel_servos servo_control
```

Now, in new terminal, please enter line below to run controller:

```
$ rosrun open_hand_controller open_hand_controller
```

To move the hand you have to public data:
```
$ rostopic pub /close_hand open_hand_controller/close_hand "opcja1" "opcja2" "opcja3"
```

or
```
$ rostopic pub /wide_close_hand open_hand_controller/wide_close_hand "option1" "option2"
"option3" "option4"
```
```
"option1" is a bool type; "true" value closes hand; "false" value opens hand;
"option2" is a float64 type; range is 0 to 1; It defines what percentage of the possible torque is using by servos.
"option3" is a float64 type; range is 0 to 1; It defines what percentage of the possible velocity is using by servos.
"option4" is a float64 type; range is 0 to 1; It defines what percentage of the possible distance between two upper fingers is using by servos.
```

### test_talker and test_listener
Both nodes operate on the basis of topics linking the open_hand_controller node to the ROS system.

test_listener on startup displays the actual parameters of servos.

test_talker has an interface that allows direct input of data to be sent to the servo.

To observe changes:
```
$ rostopic echo /servo_control_commands 
```


To run test nodes, while the open_hand_control is running, use the command:
```
$ rosrun open_hand_controller test_talker
```
in new terminal:
```
$ rosrun open_hand_controller test_listener
```

