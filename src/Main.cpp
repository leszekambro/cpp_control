#include <iostream>
#include <fstream>
#include <math.h>
#include "ros/ros.h"
#include "unistd.h"
#include "ardrone_autonomy/Navdata.h"
#include "string.h"
#include <iostream>
#include <fstream>
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"

using namespace std;
ardrone_autonomy::Navdata::ConstPtr navdata;
static bool isNavdataReady = false;

void ardroneNavdataCallback(const ardrone_autonomy::Navdata::ConstPtr& msg){
  navdata = msg;
  isNavdataReady = true;
}

int main(int argc, char* argv[])
{
  cout<<"Ros Ardrone Initialize"<<endl;
  ros::init(argc, argv, "cpp_example_controll");
  ros::NodeHandle nh;

  ros::Rate loop_rate(10);
  ros::spinOnce();

  ros::Subscriber subscriberNavdata = nh.subscribe("/ardrone/navdata", 1, ardroneNavdataCallback);
  ros::Publisher publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::spinOnce();

  ofstream File("/home/fly/PitchAndRoll.txt");
  while (ros::ok()){
    if(!isNavdataReady){
      ros::spinOnce();
      loop_rate.sleep();

      continue;
    }

    geometry_msgs::Twist msg;

    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.linear.z = 0;
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 0;

    if(!navdata->tags_xc.empty() && !navdata->tags_yc.empty() && !navdata->tags_distance.empty()) {
     // cout << "X: " << navdata->tags_xc.front() << " Y: " << navdata->tags_yc.front() << endl;
      //File << "X: " << navdata->tags_xc.front() << " Y: " << navdata->tags_yc.front() << endl;
      cout << " Distance: " << navdata->tags_distance.front() << endl;

      float distance = navdata->tags_distance.front();

      float diff = 100 - distance;

      if(abs(diff) > 30 ) {
        if(diff > 0 ){
          msg.linear.x = -0.1;
        } else {
          msg.linear.x = 0.1;
        }
      }
      } else {
         cout << " No tags found"<< endl;
      }

    publisher.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  File.close();
  return 0;
}
