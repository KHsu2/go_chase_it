# go_chase_it
go_chase_it is a robot that chases a white ball around the model of my apartment created in the build_my_world project, simulated in Gazebo and controlled with ROS.

<img width="300" alt="Robot In Apartment" src="/images/robot_apartment.PNG">

## Overview
### robot
A simple robot with
* 2 Wheels
* 2 Castor Wheels
* RGB Camera
* Hokuyo Rangefinder Lidar sensor

<img width="300" alt="Robot" src="/images/robot.PNG">

### ball_chaser
* Search camera feed for white pixels (Assumes ball is only thing that is white)
* Artificially split the camera feed vertically into thirds
* If the detected white pixel is in the left or right section of the image, command robot to turn to the left or right. If white pixel is in the middle section,  move forward.

## Launch
* Initialize Catkins workspace
``` $ mkdir -p <folder_destination>/catkins_ws/src 
    $ cd <folder_destination>/catkins_ws/src
    $ catkin_init_workspace
    $ cd <folder_destination>/catkins_ws
    $ catkin_make 
```

* Add contents of src (ball_chaser, my_robot, CMakeList) directory to current src folder 
* Launch my_robot to open up environment in Gazebo and an empty RViz window
``` $ cd <folder_destination>/catkins_ws
    $ catkin_make
    $ source devel/setup.bash
    $ roslaunch my_robot world.launch 
```
* Open a new terminal and launch ball_chaser
``` $ cd <folder_destination>/catkins_ws
    $ catkin_make
    $ source devel/setup.bash
    $ roslaunch ball_chaser ball_chaser.launch 
```
* Use RViz to visualize the input of the camera sensor
    * Change `Fixed Frame` to camera
    * `Add` new display of camera
    * Subscribe camera's `Image Topic` to `/camera/rgb/image_raw`
