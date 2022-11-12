#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "std_srvs/Empty.h"
// Import the service message header file generated from the Empty.srv message
geometry_msgs::Twist vel;
// We define the callback function of the service
bool move_in_circle(std_srvs::Empty::Request &req,
                 std_srvs::Empty::Response &res) {
  

 vel.linear.x = 0.1;
  vel.angular.z = 0.2;

  ROS_INFO("robot started moving in curcile"); // We print an string whenever the                                        // Service gets called
  return true;
}
bool stop(std_srvs::Empty::Request &req,
                 std_srvs::Empty::Response &res) {
  

 vel.linear.x = 0.0;
  vel.angular.z = 0.0;

  ROS_INFO("robot stopped"); // We print an string whenever the                                        // Service gets called
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
  ros::ServiceServer my_service_move = nh.advertiseService("/move_bb8_in_circle",move_in_circle);
  ros::ServiceServer my_service_stop = nh.advertiseService("/stop_bb8",stop); // create the Service called
   
  while (ros::ok()) {
  ros::Rate loop_rate(50);                 // my_service with the defined // callback

  vel_pub.publish(vel);
   ros::spinOnce();
 // ros::spin(); // mantain the service open.
  loop_rate.sleep();
  }
  return 0;
}