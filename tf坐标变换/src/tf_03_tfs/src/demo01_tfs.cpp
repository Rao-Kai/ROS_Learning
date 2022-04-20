#include <ros/ros.h>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "tfs_sub");
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    geometry_msgs::PointStamped psson1;
    psson1.header.stamp = ros::Time::now();
    psson1.header.frame_id = "son1";
    psson1.point.x = 1.0;
    psson1.point.y = 2.0;
    psson1.point.z = 3.0;

    ros::Rate rate(10);
    while(ros::ok())
    {

        try
        {
            geometry_msgs::TransformStamped son1Toson2;
            son1Toson2 = buffer.lookupTransform("son2","son1",ros::Time(0));
            ROS_INFO("父级名称:%s, 子级名称:%s 偏移量(%.2f,%.2f,%.2f)",
                    son1Toson2.header.frame_id.c_str(),
                    son1Toson2.child_frame_id.c_str(),
                    son1Toson2.transform.translation.x,
                    son1Toson2.transform.translation.y,
                    son1Toson2.transform.translation.z
                    );
            
            geometry_msgs::PointStamped psson2;
            psson2 = buffer.transform(psson1,"son2");
            ROS_INFO("坐标点在son2中的值(%.2f,%.2f,%.2f)",
                    psson2.point.x, 
                    psson2.point.y, 
                    psson2.point.z
                    );
        }
        catch(const std::exception& e)
        {
            ROS_INFO("错误:%s", e.what());
        }
        
    }
    return 0;
}
