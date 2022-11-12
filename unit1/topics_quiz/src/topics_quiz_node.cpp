#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <array>
#include <iostream>
#include <vector>

using namespace std;
// float laser_data[720];
// vector<float> laser_vector;
float front_laser;
float left_laser;
float right_laser;

void laser_Callback(const sensor_msgs::LaserScan &msg) {
  // ROS_INFO("I heard: [%f]", msg.data);
  // int range_size= end(msg.ranges)- begin(msg.ranges);
  //   for (int i = 0; i < range_size; i++) {
  //      laser_data[i] = msg.ranges[i];
  //     std::cout << laser_data[i]<<endl ;
  //   }
  front_laser = msg.ranges[360];
  left_laser = msg.ranges[719];
  right_laser = msg.ranges[0];

  //   ROS_INFO_STREAM(msg);
  std::cout << front_laser << right_laser << endl;
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "topics_quiz_node");

  ros::NodeHandle n;

  geometry_msgs::Twist vel;

  ros::Subscriber sub = n.subscribe("/kobuki/laser/scan", 50, laser_Callback);
  ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
  ros::Rate loop_rate(50);

  while (ros::ok()) {
    if (front_laser > 1.0 && right_laser>1.0 && left_laser>1.0) {
      vel.linear.x = 0.2;
      vel.angular.z = 0;
      ROS_INFO("move forward[%f]", front_laser);
    }

     if (front_laser < 1.0 || right_laser <= 1.0) {
      vel.linear.x = 0.0;
      vel.angular.z = 0.2;
      ROS_INFO("turn left[%f]", right_laser);

    }

     if (left_laser <= 1.0) {
      vel.linear.x = 0.0;
      vel.angular.z = -0.2;
      ROS_INFO("turn right[%f]", left_laser);
    }

    ros::spinOnce();
    vel_pub.publish(vel);
    loop_rate.sleep();
  }
  return 0;
}
