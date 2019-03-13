cmake_minimum_required(VERSION 2.8.3)
project(igvc_navigation)

find_package(catkin REQUIRED roslaunch nav_msgs geometry_msgs roscpp rospy)

catkin_package()

roslaunch_add_file_check(launch)

add_executable(odom_inv src/odom_inv.cpp)
target_link_libraries(odom_inv ${catkin_LIBRARIES})

add_executable(vel_inv src/vel_inv.cpp)
target_link_libraries(vel_inv ${catkin_LIBRARIES})

install(
  DIRECTORY config launch maps
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

