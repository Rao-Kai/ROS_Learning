#include "ros/ros.h"
#include <std_msgs/String.h>

int main(int argc, char *argv[])
{
    /* code */
    ros::init(argc, argv, "chao_node"); //这个节点名最好可以和代码文件名同名，方便看rqt_graph;rqt_graph里的显示是按这个来的

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("dai_fei_qun", 10);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
       printf("准备带飞\n");
       std_msgs::String msg;
       msg.data = "I WILL TAKE YOU FLY";
       pub.publish(msg);
       loop_rate.sleep();
    }
    
    return 0;
}
