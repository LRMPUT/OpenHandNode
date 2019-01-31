# Putarm Simulation Control

### Preparation 

To control putarm in simulation you can choose one of two options:

##### Running simulation cotrol for two terminals:

In first terminal:
```
$ roslaunch putarm_gazebo putarm.launch
```
In second terminal:
```
$ rosrun putarm_control_example putarm_control_example_node
```

##### Running simulation cotrol for one terminals:

```
$ roslaunch hand_cotrol_example hand_control_example.launch
```

### Controlling the simulation

Those two options above give us the same result - running simulation which we can control.

Now, in new terminal, we can public data to move the simulated hand:

```
$ rostopic pub /hand_controller/order std_msgs/String "option1"
```

or arm:

```
$ rostopic pub /arm_controller/order std_msgs/String "option2"
```

In option1 field you can put one of four possible actions:
```
"open" - open the gripper
"close" - close the gripper
```


In option2 field you can put one of six possible actions:
```
"move0"
"move1"
"move2"
"move3"
"move4"
"move5"
```
Those six actions will move the UR3 arm in six different nodes.
