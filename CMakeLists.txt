cmake_minimum_required(VERSION 2.8.3)
project(cpp_example_controll)

add_compile_options(-std=c++11)

find_package(X11 REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  cv_bridge
  sensor_msgs
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

find_package(OpenCV)
message("OpenCV version: ${OpenCV_VERSION}")

include_directories(
	include
	${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

LINK_DIRECTORIES("usr/local/lib")

#generate_messages(
#   DEPENDENCIES
#   mavros_msgs
#   std_msgs
#   sensor_msgs
#)

catkin_package(
   CATKIN_DEPENDS 
   roscpp
   cv_bridge
   sensor_msgs
   std_msgs
)


add_executable(cpp_example_controll src/Main.cpp)
target_link_libraries(cpp_example_controll ${catkin_LIBRARIES} ${OpenCV_LIBS} X11)
