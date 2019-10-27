#include <iostream>
#include <stdlib.h>

int main()
{
   //int launch_result = system("bash /home/h/hns/github/cplusplus_learn_record/src/ros_learn/msg_catkin_ws/system_launch.sh");
    int copy_result = system("/bin/bash copy.sh");
    int pwd1 = system("pwd");
    int ls2 = system("ls");
    int lss3 = system("ls");
    std::cout<<"pwd1: "<<pwd1<<std::endl;
    std::cout<<"ls2: "<<ls2<<std::endl;
    std::cout<<"lss3: "<<lss3<<std::endl;
    //std::cout<<"launch_node_result: "<<launch_result<<std::endl;
    return 0;
}
