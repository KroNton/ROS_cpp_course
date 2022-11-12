#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
geometry_msgs::Twist vel;
ros::Publisher vel_pub;

bool move_in_circle(
    my_custom_srv_msg_pkg::MyCustomServiceMessage::Request &req,
    my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res) {
  ROS_INFO("Request Data==> duration=%d", req.duration);
  float time = req.duration;
  int i=0;
    vel.linear.x = 0.1;
    vel.angular.z = 0.2;
    vel_pub.publish(vel);
    while ( i<time) {
    
    ROS_INFO("count the duration %d ",i);
    sleep(1);
    i++;
 }
    vel.linear.x = 0.0;
    vel.angular.z = 0.0;
    vel_pub.publish(vel);
    res.success = true;
  ROS_INFO("sending back response:true");
  //   if (req.duration > 5) {
  //
  //     ROS_INFO("sending back response:true");
  //   } else {
  //     res.success = false;
  //     ROS_INFO("sending back response:false");
  //   }

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "bb8_custom_server");
  ros::NodeHandle nh;
   vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
  ros::ServiceServer my_service_move =
      nh.advertiseService("/move_bb8_in_circle_custom", move_in_circle);

  while (ros::ok()) {
    ros::Rate loop_rate(50); // my_service with the defined // callback

    // vel_pub.publish(vel);
    ros::spinOnce();
    // ros::spin(); // mantain the service open.
    loop_rate.sleep();
  }
  return 0;
}