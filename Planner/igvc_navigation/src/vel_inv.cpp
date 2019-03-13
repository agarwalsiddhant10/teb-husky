#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

geometry_msgs::Twist inv_vel;

void vel_callback(const geometry_msgs::Twist& vel_msg)
{
    inv_vel.linear.x = vel_msg.linear.x;
      inv_vel.linear.y = vel_msg.linear.y;
        inv_vel.linear.z = vel_msg.linear.z;
          
          inv_vel.angular.x = vel_msg.angular.x;
            inv_vel.angular.y = vel_msg.angular.y;
              inv_vel.angular.z = -1.0*vel_msg.angular.z; 
}

int main(int argc, char **argv)
{ 
    ros::init(argc, argv, "inver_vel");
      ros::NodeHandle n;
        ros::Subscriber odom_sub = n.subscribe("cmd_vel_neg", 50, &vel_callback);
          ros::Publisher odom_pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1000);
            
            ros::Rate loop_rate(10);

              while(ros::ok()) {
                  odom_pub.publish(inv_vel);
                    ros::spinOnce();
                      loop_rate.sleep();
                        } 

              return 0;
}

