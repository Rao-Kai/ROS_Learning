#include <ros/ros.h>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "tfs_sub");
    ros::NodeHandle nh;

    //创建速度发布对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",1000);

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    ros::Rate rate(10);
    while(ros::ok())
    {
        try
        {
            geometry_msgs::TransformStamped turtle1Toturtle2;
            turtle1Toturtle2 = buffer.lookupTransform("turtle2","turtle1",ros::Time(0),ros::Duration(3.0));//turtle1在turtle2参考系下的位置
            // ROS_INFO("父级名称:%s, 子级名称:%s 偏移量(%.2f,%.2f,%.2f)",
            //         turtle1Toturtle2.header.frame_id.c_str(),
            //         turtle1Toturtle2.child_frame_id.c_str(),
            //         turtle1Toturtle2.transform.translation.x,
            //         turtle1Toturtle2.transform.translation.y,
            //         turtle1Toturtle2.transform.translation.z
            //         );

            geometry_msgs::Twist twist;
            //乌龟只有x方向的线速度和绕z轴的偏航角
            twist.linear.x = 0.8 * sqrt(pow(turtle1Toturtle2.transform.translation.x,2) + 
                                        pow(turtle1Toturtle2.transform.translation.y,2));
            twist.angular.z = 4 * atan2(turtle1Toturtle2.transform.translation.y,turtle1Toturtle2.transform.translation.x);
            
            pub.publish(twist);
            
        }
        catch(const std::exception& e)
        {
            ROS_INFO("错误:%s", e.what());
        }
        
    }
    return 0;
}
