# Dynamixel Servo Control Node

## Preparation

### Installing necessary packages for the ROS-Kinetic system:
```
$ sudo apt-get install ros-kinetic-dynamixel-sdk
$ sudo apt-get install ros-kinetic-qt-build
```

### Downloading the Git repository:

```
$ git clone https://github.com/LRMPUT/OpenHandNode
```

### Compilation of the dynamixel_servos node:

```
$ cd ../catkin_ws
$ catkin_make
$ source ../catkin_ws/devel/setup.bash
```

### Adding a user to the dialout group:

```
sudo usermod -a -G dialout $USER
```
After calling command above, it is necessary to restart the system

### Running the dynamixel_servos node:

```
$ roscore
$ rosrun dynamixel_servos servo_control 
```

## Start-up
### Topic's subscription:

```
$ rostopic echo /servo_control_info 

servo_id: 21
present_current: 0
present_velocity: 0
present_position: 2000

```

### Sending a message to the topic

##### Turning on the torque:
```
$ rostopic pub /servo_control_commands dynamixel_servos/CommandMessage "servo_id: 21
register_address: 64
bytes_number: 1
value: 1" 
```
##### Sending position of the servo:
```
$ rostopic pub /servo_control_commands dynamixel_servos/CommandMessage "servo_id: 21
register_address: 116
bytes_number: 4
value: 2000" 
```
meaning:  
**servo_id** - servo's ID  
**register_address** - registry address  
**bytes_number** - register size  
**value** - value to enter

[Table with addresses and register sizes](http://support.robotis.com/en/product/actuator/dynamixel_x/xm_series/xm430-w210.htm#bookmark23) 

