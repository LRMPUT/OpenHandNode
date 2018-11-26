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
std::vector<double> currentPos = {0,0,0,0,0,0};


ros::Publisher ctrlPub2;//control the robot
std::vector<double> currentPos2 = {0,0,0,0,0,0};



/// received string order
void orderCallback(const std_msgs::String::ConstPtr& msg){
    control_msgs::FollowJointTrajectoryActionGoal ctrlMsg;
    ctrlMsg.goal.trajectory.joint_names.push_back("shoulder_pan_joint");
    ctrlMsg.goal.trajectory.joint_names.push_back("shoulder_lift_joint");
    ctrlMsg.goal.trajectory.joint_names.push_back("elbow_joint");
    ctrlMsg.goal.trajectory.joint_names.push_back("wrist_1_joint");
    ctrlMsg.goal.trajectory.joint_names.push_back("wrist_2_joint");
    ctrlMsg.goal.trajectory.joint_names.push_back("wrist_3_joint");
    //ctrlMsg.goal.trajectory.joint_names.push_back("finger1");

    ctrlMsg.goal.trajectory.points.resize(1);
    ctrlMsg.goal.trajectory.points[0].positions.resize(6);
    if (msg->data.compare("moveLeft")==0)
        ctrlMsg.goal.trajectory.points[0].positions[0]=1.0;
///////////////////////////
    else if (msg->data.compare("move0")==0)
	{
        ctrlMsg.goal.trajectory.points[0].positions[1]=-1.0;
	ctrlMsg.goal.trajectory.points[0].positions[5]=-1.0;
	}
    else if (msg->data.compare("move1")==0)
        ctrlMsg.goal.trajectory.points[0].positions[1]=-1.0;
    else if (msg->data.compare("move2")==0)
        ctrlMsg.goal.trajectory.points[0].positions[2]=-1.0;
    else if (msg->data.compare("move3")==0)
        ctrlMsg.goal.trajectory.points[0].positions[3]=-1.0;
    else if (msg->data.compare("move4")==0)
        ctrlMsg.goal.trajectory.points[0].positions[4]=-1.0;
    else if (msg->data.compare("move5")==0)
        ctrlMsg.goal.trajectory.points[0].positions[5]=-1.0;
    else if (msg->data.compare("moveRight")==0)
        ctrlMsg.goal.trajectory.points[0].positions[0]=-1.0;

    else
        ctrlMsg.goal.trajectory.points[0].positions[0]=0.0;
    // Velocities
    ctrlMsg.goal.trajectory.points[0].velocities.resize(6);
    for (size_t jointNo=0; jointNo<6;jointNo++)
        ctrlMsg.goal.trajectory.points[0].velocities[jointNo] = 0.0;
    ctrlMsg.goal.trajectory.points[0].time_from_start = ros::Duration(1.0);

    ctrlPub.publish(ctrlMsg);
}

//////////////////////////////////////////////////////////////////////
void orderCallback2(const std_msgs::String::ConstPtr& msg){
    control_msgs::FollowJointTrajectoryActionGoal ctrlMsg2;
    ctrlMsg2.goal.trajectory.joint_names.push_back("rotator1");
    ctrlMsg2.goal.trajectory.joint_names.push_back("rotator2");
    ctrlMsg2.goal.trajectory.joint_names.push_back("rotator3");
    ctrlMsg2.goal.trajectory.joint_names.push_back("finger1");
    ctrlMsg2.goal.trajectory.joint_names.push_back("finger2");
    ctrlMsg2.goal.trajectory.joint_names.push_back("finger3");

    ctrlMsg2.goal.trajectory.points.resize(1);
    ctrlMsg2.goal.trajectory.points[0].positions.resize(6);
    if (msg->data.compare("rotateThumb1")==0)
        ctrlMsg2.goal.trajectory.points[0].positions[0]=1.0;
    else if (msg->data.compare("rotateThumb2")==0)
        ctrlMsg2.goal.trajectory.points[0].positions[0]=-1.0;
    else if (msg->data.compare("moveFinger")==0)
        ctrlMsg2.goal.trajectory.points[0].positions[4]=-1.0;
    else if (msg->data.compare("grab")==0)
    {
	ctrlMsg2.goal.trajectory.points[0].positions[3]=1.0;
	ctrlMsg2.goal.trajectory.points[0].positions[4]=-1.0;
	ctrlMsg2.goal.trajectory.points[0].positions[5]=-1.0;
    }
    else if (msg->data.compare("open")==0)
    {
	ctrlMsg2.goal.trajectory.points[0].positions[3]=0.0;
	ctrlMsg2.goal.trajectory.points[0].positions[4]=0.0;
	ctrlMsg2.goal.trajectory.points[0].positions[5]=0.0;
    }

    else if (msg->data.compare("wideOpen")==0)
    {
	ctrlMsg2.goal.trajectory.points[0].positions[3]=-0.3;
	ctrlMsg2.goal.trajectory.points[0].positions[4]=0.3;
	ctrlMsg2.goal.trajectory.points[0].positions[5]=0.3;
	
	//thumb
	ctrlMsg2.goal.trajectory.points[0].positions[0]=0.0;
	//pointer
	ctrlMsg2.goal.trajectory.points[0].positions[1]=1.0;
	//middle
	ctrlMsg2.goal.trajectory.points[0].positions[2]=-1.0;
    }

    else
        ctrlMsg2.goal.trajectory.points[0].positions[0]=0.0;
    // Velocities
    ctrlMsg2.goal.trajectory.points[0].velocities.resize(6);
    for (size_t jointNo=0; jointNo<6;jointNo++)
        ctrlMsg2.goal.trajectory.points[0].velocities[jointNo] = 0.0;
    ctrlMsg2.goal.trajectory.points[0].time_from_start = ros::Duration(1.0);

    ctrlPub2.publish(ctrlMsg2);
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
/// read state of the robot
void urStateCallback(const control_msgs::JointTrajectoryControllerState::ConstPtr& msg)
{
    for (size_t jointNo=0; jointNo<6;jointNo++){
        ROS_INFO("Joint pos[%d]: %f", (int)jointNo, msg->actual.positions[jointNo]);
        currentPos[jointNo] = msg->actual.positions[jointNo];
    }
}



///////////////////////////////////////////////////////////////
void urStateCallback2(const control_msgs::JointTrajectoryControllerState::ConstPtr& msg)
{
    for (size_t jointNo=0; jointNo<6;jointNo++){
        ROS_INFO("Joint pos[%d]: %f", (int)jointNo, msg->actual.positions[jointNo]);
        currentPos2[jointNo] = msg->actual.positions[jointNo];
    }
}
///////////////////////////////////////////////////////////////


int main(int argc, char **argv) {
    //initialize node
    ros::init(argc, argv, "control_example");
    // node handler
    ros::NodeHandle n;
    // subsribe topic
    ros::Subscriber subRobot = n.subscribe("/arm_controller/state", 1, urStateCallback);//simulator
    // subsribe topic
    ros::Subscriber subOrders = n.subscribe("/arm_controller/order", 1, orderCallback);//subscribe orders topic

    ctrlPub = n.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/arm_controller/follow_joint_trajectory/goal", 1000);




    ros::NodeHandle n2;
    // subsribe topic
    ros::Subscriber subRobot2 = n2.subscribe("/hand_controller/state", 1, urStateCallback2);//simulator
    // subsribe topic
    ros::Subscriber subOrders2 = n2.subscribe("/hand_controller/order", 1, orderCallback2);//subscribe orders topic

    ctrlPub2 = n2.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/hand_controller/follow_joint_trajectory/goal", 1000);
    

    //ros loop
    ros::spin();
    return 0;
}
