#include <ros/ros.h>
#include <imu_msgs/IMU.h>
#include <vector>
void msg_callback(const imu_msgs::IMU& msg)
{
    std::vector<float> acc_vec=msg.acc;
    std::vector<float> gyro_vec=msg.gyro;
    std::cout<<"msg timeStamp: "<<msg.timeStamp<<std::endl;
    
    std::cout<<"acc: ";
    for(int i=0;i<acc_vec.size();++i)
    {
        std::cout<<acc_vec[i]<<" ";
    }
    std::cout<<std::endl;
    
    std::cout<<"gyro: ";
    for(int i=0;i<gyro_vec.size();++i)
    {
        std::cout<<gyro_vec[i]<<" ";
    }
    std::cout<<std::endl;
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"sub_node");
    ros::NodeHandle n;
    ros::Subscriber msg_sub = n.subscribe("imu_data",100,msg_callback);
    ros::spin();
    return 0;
}



