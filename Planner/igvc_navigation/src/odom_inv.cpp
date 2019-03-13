#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"

nav_msgs::Odometry inv_odom;
geometry_msgs::PoseStamped inv_goal;
ros::Publisher goal_pub;

void odom_callback(const nav_msgs::Odometry& odom_msg)
{
    inv_odom.header.seq = odom_msg.header.seq;
      inv_odom.header.stamp = odom_msg.header.stamp;
        inv_odom.header.frame_id = odom_msg.header.frame_id;
          
          inv_odom.child_frame_id = odom_msg.child_frame_id;
            inv_odom.pose.pose.position.x = odom_msg.pose.pose.position.x;
              inv_odom.pose.pose.position.y = odom_msg.pose.pose.position.y;
                inv_odom.pose.pose.position.z = odom_msg.pose.pose.position.z;
                  
                  inv_odom.pose.pose.orientation.x = odom_msg.pose.pose.orientation.x;
                    inv_odom.pose.pose.orientation.y = odom_msg.pose.pose.orientation.y;
                      inv_odom.pose.pose.orientation.z = -1.0*odom_msg.pose.pose.orientation.z;
                        inv_odom.pose.pose.orientation.w = odom_msg.pose.pose.orientation.w;

                          inv_odom.pose.covariance = odom_msg.pose.covariance;
                            inv_odom.twist.covariance = odom_msg.twist.covariance;

                              inv_odom.twist.twist.linear.x = odom_msg.twist.twist.linear.x;
                                inv_odom.twist.twist.linear.y = odom_msg.twist.twist.linear.y;
                                  inv_odom.twist.twist.linear.z = odom_msg.twist.twist.linear.z;

                                    inv_odom.twist.twist.angular.x = odom_msg.twist.twist.angular.x;
                                        inv_odom.twist.twist.angular.y = odom_msg.twist.twist.angular.y;
                                          inv_odom.twist.twist.angular.z = -1.0*odom_msg.twist.twist.angular.z;  
}

void goal_callback(const geometry_msgs::PoseStamped& goal_msg)
{
    inv_goal = goal_msg;
      inv_goal.pose.position.y = -1.0*goal_msg.pose.position.y;   
        inv_goal.pose.orientation.z = -1.0*goal_msg.pose.orientation.z;
        goal_pub.publish(inv_goal);
}

int main(int argc, char **argv)
{ 
    ros::init(argc, argv, "inver_odom");
      ros::NodeHandle n;
        ros::Subscriber odom_sub = n.subscribe("odometry/filtered", 50, &odom_callback);
          ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odometry/filtered_inv",1000);
    ros::Subscriber goal_sub = n.subscribe("move_base_simple/goal", 50, &goal_callback);
    goal_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple_inverted/goal",1000);    
  
    ros::Rate loop_rate(10);

              while(ros::ok()) {
                  odom_pub.publish(inv_odom);
                    ros::spinOnce();
                      loop_rate.sleep();
                        }

              return 0;
}

