#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <iostream>
using namespace std;

//Define a global client that can request services

ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget drive_cmd;
    drive_cmd.request.linear_x = lin_x;
    drive_cmd.request.angular_z = ang_z;
    
    if (!client.call(drive_cmd)){
        ROS_ERROR("Failed to execute drive command");
    }
}

//This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    
    /*
     순서
      지도의 어디에 흰색이 있는지 찾기. 
      그쪽 방향으로 움직이기.
    */
    int pixel_white = 255;
    int cnt_white =0;
    float x=0,z=0;
    float mv_x, mv_y;
    float steer=0.01;
    int moment =0;
    float awm;

    for(int ps_i =0 ; ps_i <img.height;++ps_i) {
        for(int ps_j =0 ;ps_j< img.step;++ps_j){
            
            if(img.data[ps_i* img.step +ps_j] == pixel_white){
                ++cnt_white;
                moment = moment +ps_j - img.step/2;
                awm = moment/cnt_white;
            }
            //ROS_INFO("mtx:[ %d, %d], pixel : %d cnt_white: %d ", j, i ,img.data[i* img.step +j], cnt_white);
            
        }
    }

    if (cnt_white ==0) {
        x = 0.0;
        z = 0.8;
    }
    else{
        x = 0.5;
        z = -0.8*awm/600;
    }
    
    drive_robot(x,z);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    ros::spin();

    return 0;
}
