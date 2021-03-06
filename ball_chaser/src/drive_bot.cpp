#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
//TODO: Include the ball_chaser "DriveToTarget" header file

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities



bool cmd_move(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{ 
/*
    
    구독:  process_image 노드로부터 각도 속도 req를 서비스로 받음.
    발행: 서비스 받은 것을 로봇에게 publish
*/
    geometry_msgs::Twist motor_command;
    motor_command.linear.x =    req.linear_x;
    motor_command.angular.z =   req.angular_z;

    motor_command_publisher.publish(motor_command);
    ROS_INFO("Let's go, chaser bot!\n");
    return true;

}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle nh;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer serv = nh.advertiseService("/ball_chaser/command_robot",cmd_move);
    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
    
    // Create a motor_command object of type geometry_msgs::Twist
    geometry_msgs::Twist motor_command;
    // Set wheel velocities, forward [0.5, 0.0]
    motor_command.linear.x = 0.0;
    motor_command.angular.z = 0.5;
    motor_command.angular.y = 0.5;
    // Publish angles to drive the robot
    motor_command_publisher.publish(motor_command);


    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}