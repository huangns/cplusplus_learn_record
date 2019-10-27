#include "get_mac_address.h"
#include <string>
#include <iostream>
int main()
{
	std::string mac_address = getMacAddress();
    if(std::string("")==mac_address)
    {
        std::cerr<<"no mac address."<<std::endl;
    }else
    {
        std::cout<<"mac address: "<<mac_address<<std::endl;
//        std::cout<<"size: "<<mac_address.size()<<std::endl;
    }
    return 0;
}
