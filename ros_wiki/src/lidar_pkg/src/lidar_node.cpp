#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

// 因为要在main函数之外使用pub,也就是在回调函数里，所以要提前进行声明
ros::Publisher pub;
int ncount = 0;

void LidarCallback(const sensor_msgs::LaserScan msg){
    // 机器人正前方的数据刚好是第180个数据
    float fMidDist = msg.ranges[180];
    ROS_INFO("前方测距 rangs[180] = %f 米", fMidDist);

    // 当检测到障碍物时，开始记数，保证大概旋转5s
    // 能够保持5s的原因：通过查看雷达消息包的scan_time得到每隔0.08s雷达发射一次，也就是1s大概11次
    // 也就是1s执行11次callback函数，那我们就可让机器人在回调函数的50次执行中都保持转向行为
    // if中的return表示，执行完return后，整个函数调用结束，也就是callback调用结束
    if(ncount > 0){
        ncount --;
        return;
    }

    geometry_msgs::Twist vel_cmd;

    if(fMidDist <= 1.5){
        vel_cmd.angular.z = 0.3;
        ncount = 50;
    }else{
        vel_cmd.linear.x = 0.8;
    }
    
    pub.publish(vel_cmd);
}

int main(int argc, char *argv[])
{
    /* code */
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "lidar_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<sensor_msgs::LaserScan>("/scan", 10, &LidarCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin();
    return 0;
}
