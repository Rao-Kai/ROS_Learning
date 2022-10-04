#include "ros/ros.h"
#include "std_msgs/String.h"


void ChatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  // 节点名称为listener
  ros::init(argc, argv, "listener");

  ros::NodeHandle nh;

  ros::Subscriber Chatter_Sub = nh.subscribe("chatter", 1000, ChatterCallback);

  ros::spin();

  return 0;
}