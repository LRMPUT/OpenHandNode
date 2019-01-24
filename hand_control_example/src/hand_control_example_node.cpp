#include "ros/ros.h"
#include "ros/package.h"
#include "ros/this_node.h"
#include <iostream>
#include <time.h>

#include "control_msgs/JointTrajectoryControllerState.h" //read state of the arm
#include "control_msgs/FollowJointTrajectoryAction.h" //set goal positions
#include "sensor_msgs/JointState.h"
#include "std_msgs/String.h"
#include "moveit_msgs/GetPositionIK.h"
#include "moveit_msgs/GetPositionFK.h"
#include "moveit_msgs/DisplayRobotState.h"

#include <stdio.h>

using namespace std;


ros::Publisher ctrlPub;//control the robot
std::vector<double> currentPos = {0,0,0,0,0};



/// received string order

//////////////////////////////////////////////////////////////////////
void orderCallback(const std_msgs::String::ConstPtr& msg){
    control_msgs::FollowJointTrajectoryActionGoal ctrlMsg;
    ctrlMsg.goal.trajectory.joint_names.push_back("rotator2");
    ctrlMsg.goal.trajectory.joint_names.push_back("rotator3");
    ctrlMsg.goal.trajectory.joint_names.push_back("finger1");
    ctrlMsg.goal.trajectory.joint_names.push_back("finger2");
    ctrlMsg.goal.trajectory.joint_names.push_back("finger3");

    ctrlMsg.goal.trajectory.points.resize(1);
    ctrlMsg.goal.trajectory.points[0].positions.resize(5);

    if (msg->data.compare("open")==0)
    {
	ctrlMsg.goal.trajectory.points[0].positions[2]=0.0;
	ctrlMsg.goal.trajectory.points[0].positions[3]=0.0;
	ctrlMsg.goal.trajectory.points[0].positions[4]=0.0;
    }

    else if (msg->data.compare("close")==0)
    {
	ctrlMsg.goal.trajectory.points[0].positions[2]=1.0;
	ctrlMsg.goal.trajectory.points[0].positions[3]=-1.0;
	ctrlMsg.goal.trajectory.points[0].positions[4]=-1.0;
    }

    else if (msg->data.compare("wideOpen")==0)
    {
	ctrlMsg.goal.trajectory.points[0].positions[2]=0.0;
	ctrlMsg.goal.trajectory.points[0].positions[3]=0.0;
	ctrlMsg.goal.trajectory.points[0].positions[4]=0.0;
	
	ctrlMsg.goal.trajectory.points[0].positions[0]=0.7;
	ctrlMsg.goal.trajectory.points[0].positions[1]=-0.7;
    }

    else if (msg->data.compare("wideClose")==0)
    {
	ctrlMsg.goal.trajectory.points[0].positions[2]=1.0;
	ctrlMsg.goal.trajectory.points[0].positions[3]=-1.0;
	ctrlMsg.goal.trajectory.points[0].positions[4]=-1.0;
	
	ctrlMsg.goal.trajectory.points[0].positions[0]=0.7;
	ctrlMsg.goal.trajectory.points[0].positions[1]=-0.7;
    }

    else
        ctrlMsg.goal.trajectory.points[0].positions[0]=0.0;
    // Velocities
    ctrlMsg.goal.trajectory.points[0].velocities.resize(5);
    for (size_t jointNo=0; jointNo<5;jointNo++)
        ctrlMsg.goal.trajectory.points[0].velocities[jointNo] = 0.0;
    ctrlMsg.goal.trajectory.points[0].time_from_start = ros::Duration(1.0);

    ctrlPub.publish(ctrlMsg);
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
/// read state of the robot
void urStateCallback(const control_msgs::JointTrajectoryControllerState::ConstPtr& msg)
{
    for (size_t jointNo=0; jointNo<5;jointNo++){
        ROS_INFO("Joint pos[%d]: %f", (int)jointNo, msg->actual.positions[jointNo]);
        currentPos[jointNo] = msg->actual.positions[jointNo];
    }
}
///////////////////////////////////////////////////////////////


int main(int argc, char **argv) {
    //initialize node
    ros::init(argc, argv, "hand_control_example");

    // node handler
    ros::NodeHandle n;
    // subsribe topic
    ros::Subscriber subRobot = n.subscribe("/hand_controller/state", 1, urStateCallback);//simulator
    // subsribe topic
    ros::Subscriber subOrders = n.subscribe("/hand_controller/order", 1, orderCallback);//subscribe orders topic

    ctrlPub = n.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/hand_controller/follow_joint_trajectory/goal", 1000);
    

    //ros loop
    ros::spin();
    return 0;
}
