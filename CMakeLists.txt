cmake_minimum_required(VERSION 3.0.2)
project(jetbot_cv)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)

find_package( OpenCV REQUIRED )


catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(jetbot_cv src/jetbot_cv.cpp)

target_link_libraries(jetbot_cv
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
 )
