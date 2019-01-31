# Hand Simulation Control

### Preparation 

To control gripper in simulation you can choose one of two options:

##### Running simulation cotrol for two terminals:

In first terminal:
```
$ roslaunch hand_gazebo hand.launch
```
In second terminal:
```
$ rosrun hand_control_example hand_control_example_node
```

##### Running simulation cotrol for one terminals:

```
$ roslaunch hand_cotrol_example hand_control_example.launch
```

### Controlling the simulation

Those two options above give us the same resoult - running simulation which we can control.

Now, in new terminal, we can public data to move the simulated robot:

```
$ rostopic pub /hand_controller/order std_msgs/String "<option>"
```
