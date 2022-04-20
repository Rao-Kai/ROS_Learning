#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "static_sub");
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    geometry_msgs::PointStamped ps;
    ps.header.stamp = ros::Time::now();
    ps.header.frame_id = "laser";
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    ros::Duration(2).sleep();

    ros::Rate rate(10);
    while (ros::ok())
    {
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps,"base_link");
        ROS_INFO("转换后的坐标值:(%.2f,%.2f,%.2f),参考的坐标系:%s",
                    ps_out.point.x, 
                    ps_out.point.y, 
                    ps_out.point.z,
                    ps_out.header.frame_id.c_str()
                );
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}
