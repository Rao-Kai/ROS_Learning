#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char *argv[])
{
    /* code */
    ros::init(argc, argv, "yao_node");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("qiu_dai_qun",10);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        /* code */
        printf("准备躺平\n");
        std_msgs::String msg;
        msg.data = "dai_dai_wo";
        pub.publish(msg);

        loop_rate.sleep();
    }
    

    return 0;
}
