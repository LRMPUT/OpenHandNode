# Putarm Gazebo Simulation

### Preparation
To work with simulation, please clone the repository to src folder in your ROS workspace:
```
$ git clone https://github.com/LRMPUT/OpenHandNode
```

For simulation, you only need to install a tool to simulate a robotic arm and gripper. This tool is Gazebo. To install it you must
enter command below to the console:
```
$ sudo apt-get install ros-kinetic-gazebo-ros-pkgs ros-kinetic-gazebo-ros-control
```

Depending on your version of ROS, you should enter your version in the place of "kinetic".

Now, please compile:
```
$ catkin_make
```

### Start-up
To run simulation, please enter command below:
```
$ roslaunch putarm_gazebo putarm.launch
```

This command will shows how gripper on the UR3 robot looks like.

To control the simulation of the putarm, please follow the instructions in the "README.md" file in the "putarm_control_example" folder.
