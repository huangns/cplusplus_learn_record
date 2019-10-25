#include <iostream>
#include <string>
#include <ros/ros.h>
#include "data_capture_srv/data_capture_srv.h"
bool configureServiceCallback(data_capture_srv::data_capture_srv::Request& req,
                    data_capture_srv::data_capture_srv::Response& rep)
{
    rep.reply = std::string("world");
    std::cout<<req.request<<" , ";
    std::cout<<rep.reply<<std::endl;
    return true;
}
int main(int argc, char** argv)
{
    ros::init(argc,argv,"srv_server_node");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("/data_capture_service/configs",configureServiceCallback);
    ROS_INFO("ready to response request from clients.");
    ros::spin();
    return 0;
}
