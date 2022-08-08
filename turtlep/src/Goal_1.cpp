#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include<bits/stdc++.h>
#include <sstream>
using namespace std;
ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

double pi = 2 * acos(0.0);

void walk(double speed, double distance, bool isForward);

void rotate (double angular_speed, double angle, bool clockwise);

double getDistance(double x1, double y1, double x2, double y2);

int main(int argc, char **argv)
{
	// Initiate new ROS node named "talker"
	ros::init(argc, argv, "turtlesim");
	ros::NodeHandle n;
	double speed, angular_speed;
	double distance, angle;
	bool isForward, clockwise;


	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	
//cout<<turtlesim_pose.x<<" "<<turtlesim_pose.y<<endl;
//cout<<"enter speed: ";
	
	//cout<<"enter distance: ";
	//cout<<"forward?: ";
     /* ---------------------------------------------------- approch 1
    cout<<"Enter the cordinated: x ,y "<<endl;
    double px,py;
    cin>>px>>py;
    double zangle=atan2(py,px);
    cout<<zangle<<endl;
    speed=1;
	isForward=1;
    distance=getDistance(px,py,5,5);
    rotate(1,zangle,0);
	walk(speed, distance, isForward);
    // */
   // /*------------------------------------------------------approch 2
    
    double px0=5.0,py0=5.0;
    double px1,py1;
    cout<<"To stop inter x=22 !!!"<<endl;
    while(px0!=22)
    {
    cout<<"Enter the cordinated: x ,y "<<endl;
    cin>>px1>>py1;
    if(px1==22) break;
    if(px1>px0) 
    {walk(1.0,px1-px0,1);
    px0=px1;}
    else 
    {
    walk(1.0,px0-px1,0);
    px0=px1;
    }
    if(py1>py0) rotate(1.0,pi/2-(pi/24),1);
    else rotate(1.0,pi/2-(pi/24),0);

    if(py1>py0) 
    {walk(1.0,py1-py0,1);
    py0=py1;}
    else 
    {
    walk(1.0,py0-py1,0);
    py0=py1;
    }
    
    }
ros::Rate loop_rate(0.5);
	ros::spin();

	return 0;
}

void walk(double speed, double distance, bool isForward){
	geometry_msgs::Twist vel_msg;
	//set a random linear velocity in the x-axis
	if (isForward)
		vel_msg.linear.x =abs(speed);
	else
		vel_msg.linear.x =-abs(speed);
	vel_msg.linear.y =0;
	vel_msg.linear.z =0;
	//set a random angular velocity in the y-axis
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;
	vel_msg.angular.z =0;

	double t0 = ros::Time::now().toSec();
	double current_distance = 0.0;
	ros::Rate loop_rate(100);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_distance = speed * (t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
		//cout<<(t1-t0)<<", "<<current_distance <<", "<<distance<<endl;
	}while(current_distance<distance);
	vel_msg.linear.x =0;
	velocity_publisher.publish(vel_msg);

}

void rotate (double angular_speed, double relative_angle, bool clockwise){

	geometry_msgs::Twist vel_msg;
	//set a random linear velocity in the x-axis
	vel_msg.linear.x =0;
	vel_msg.linear.y =0;
	vel_msg.linear.z =0;
	//set a random angular velocity in the y-axis
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;

	if (clockwise)
		vel_msg.angular.z =-abs(angular_speed);
	else
		vel_msg.angular.z =abs(angular_speed);

	double current_angle = 0.0;
	double t0 = ros::Time::now().toSec();
	ros::Rate loop_rate(10);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_angle = angular_speed * (t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_angle<relative_angle);

	vel_msg.angular.z =0;
	velocity_publisher.publish(vel_msg);

}

double getDistance(double x1, double y1, double x2, double y2){
	return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}
