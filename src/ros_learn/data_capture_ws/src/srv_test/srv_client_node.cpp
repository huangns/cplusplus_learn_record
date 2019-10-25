#include <iostream>
#include <ros/ros.h>
#include "data_capture_srv/data_capture_srv.h"
#include <string>

int main(int argc, char** argv)
{
  ros::init(argc,argv,"srv_client_node");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<data_capture_srv::data_capture_srv>("/data_capture_service/configs");
  for(int i=0;i<100;++i)
  {
    data_capture_srv::data_capture_srv srv;
    srv.request.request = std::string("hello");
    if(client.call(srv))
    {
         ROS_INFO("request: %s, reponse: %s",srv.request.request.c_str(), srv.response.reply.c_str());
    }else
    {
        ROS_ERROR("Faild to call service data_capture_srv/configs.");
    }
  }
  return 0;
}
