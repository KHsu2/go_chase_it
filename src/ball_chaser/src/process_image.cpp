#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv)) 
        ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    bool white_ball_exists = false;
    int white_location;
    int section_width = img.step / 3;
    //int section_width = img.width / 3;
    for (int i = 0; i < img.height * img.step; i++) {	// ERROR?? Why use step rather than width?
        if (img.data[i] == white_pixel) {
            white_ball_exists = true;
            white_location = i;
            break;
        }
    }

    // If white ball is in the image, then determine which section that white ball is in (3 
    // vertical sections: left, front, right) and move towards it. 
    if (white_ball_exists) {
        int white_section = white_location % img.step;
        
        // If white in left section
        if (white_section >= 0 && white_section < section_width) {
            drive_robot(0.0, 0.5);
        }
        // If white in middle section
        else if (white_section >= section_width && white_section < 2 * section_width) {
            drive_robot(0.5, 0.0);
        }
        // If white in right section
        else if (white_section >= 2 * section_width && white_section <= img.step) {
            drive_robot(0.0, -0.5);
        }
    }
    else {
        drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
