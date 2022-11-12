#include "geometry_msgs/Twist.h"
#include "math.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include "services_quiz/BB8CustomServiceMessage.h"

geometry_msgs::Twist vel;
ros::Publisher vel_pub;
nav_msgs::Odometry odom;
float distance;
void sleep_timer(float time) {
  float i = 0;

  while (i < time) {
    vel_pub.publish(vel);
    ROS_INFO("count the duration %f ", i);
    sleep(1);
    i++;
  }
}
void move_1square() {
  ROS_INFO("moving forward... ");
  vel.linear.x = 0.20;
  vel.angular.z = 0.0;
  sleep_timer(2);
  ROS_INFO("rotating... ");
  vel.linear.x = 0.0;
  vel.angular.z = .2;
  sleep_timer(4);
  ROS_INFO("moving forward... ");
  vel.linear.x = 0.20;
  vel.angular.z = 0.0;
  sleep_timer(2);
  ROS_INFO("rotating... ");
  vel.linear.x = 0.0;
  vel.angular.z = .2;
  sleep_timer(4);
  ROS_INFO("moving forward... ");
  vel.linear.x = 0.20;
  vel.angular.z = 0.0;
  sleep_timer(2);
  ROS_INFO("rotating... ");
  vel.linear.x = 0.0;
  vel.angular.z = 0.2;
  sleep_timer(4);
  ROS_INFO("moving forward... ");
  vel.linear.x = 0.2;
  vel.angular.z = 0.0;
  sleep_timer(2);
  ROS_INFO("rotating... ");
  vel.linear.x = 0.0;
  vel.angular.z = 0.2;
  sleep_timer(4);
  ROS_INFO("stop! ");
  vel.linear.x = 0.0;
  vel.angular.z = 0.0;
  vel_pub.publish(vel);
}

bool move_in_square(services_quiz::BB8CustomServiceMessage::Request &req,
                    services_quiz::BB8CustomServiceMessage::Response &res) {
  //   ROS_INFO("Request Data==> duration=%d", req.duration);
  distance = req.side;
  if (distance == 1.0) {
    move_1square();
  }

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
      nh.advertiseService("/move_bb8_in_square_custom", move_in_square);

  while (ros::ok()) {
    ros::Rate loop_rate(50); // my_service with the defined // callback

    // vel_pub.publish(vel);
    ros::spinOnce();
    // ros::spin(); // mantain the service open.
    loop_rate.sleep();
  }
  return 0;
}