
#include <ros/ros.h>
#include <topic_subscriber_pkg/Age.h>

int main(int argc, char **argv) {

  ros::init(argc, argv, "topic_publisher");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<topic_subscriber_pkg::Age>("age_pub", 1000);
  ros::Rate loop_rate(2);

  topic_subscriber_pkg::Age age;
  age.days = 20.0;
  age.months = 3;
  age.years = 1998;
  while (ros::ok()) {
    pub.publish(age);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}