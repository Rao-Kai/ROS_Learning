#include "ros/ros.h"
#include "std_msgs/String.h"

void chao_node_callback(std_msgs::String msg){
    ROS_INFO(msg.data.c_str());
}
void yao_node_callback(std_msgs::String msg){
    ROS_WARN(msg.data.c_str());
}

int main(int argc, char *argv[])
{
    /* code */
    ros::init(argc, argv, "player_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<std_msgs::String>("dai_fei_qun", 10, chao_node_callback);
    ros::Subscriber sub2 = nh.subscribe<std_msgs::String>("qiu_dai_qun", 10, yao_node_callback);

    while (ros::ok())
    {
        /* code */
        ros::spinOnce();
    }
    
    return 0;
}
