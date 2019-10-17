#include <ros/ros.h>
#include <imu_msgs/IMU.h>

int main(int argc, char** argv)
{
    ros::init(argc,argv,"msg_talker");
    ros::NodeHandle n;
    ros::Publisher msg_pub = n.advertise<imu_msgs::IMU>("imu_data",1000);
    ros::Rate loop_rate(10);
    
    int count=0;
    while(ros::ok())
    {
        imu_msgs::IMU msg;
	//std::cout<<"msg.data.size()="<<msg.data.size()<<std::endl;
        msg.timeStamp=count++;
        float acc_array[3]={0.02,0.03,9.81};
        std::vector<float> acc_vec(acc_array,acc_array+3);
        msg.acc=acc_vec;
        float gyro_array[3]={0.001,0.003,0.002};
	std::vector<float> gyro_vec(gyro_array,gyro_array+3);
	msg.gyro=gyro_vec;
	//std::cout<<"msg.data[0]: "<<msg.data[0]<<std::endl;
        //std::cout<<"msg.data3.size: "<<msg.data.size()<<std::endl;
	msg_pub.publish(msg);
	ros::spinOnce();
	loop_rate.sleep();
    }   

    return 0;
}
