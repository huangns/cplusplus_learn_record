#include "get_mac_address.h"
#include <stdio.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
std::string getMacAddress()
{
    struct ifaddrs *ifaddr=NULL;
    struct ifaddrs *ifa = NULL;
    int i = 0;

    if (getifaddrs(&ifaddr) == -1)
    {
         perror("getifaddrs");
    }
    else
    {
         std::vector<std::string> mac_name_vec;
         std::vector<std::string> mac_address_vec;
         for ( ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
         {
             if ( (ifa->ifa_addr) && (ifa->ifa_addr->sa_family == AF_PACKET) )
             {
				  char mac_name_temp[80];
				  char mac_address_temp[80];
				  char *mac_address_temp_ptr = mac_address_temp;
                  struct sockaddr_ll *s = (struct sockaddr_ll*)ifa->ifa_addr;
				  sprintf(mac_name_temp,"%s",ifa->ifa_name);
				  //printf("%-8s ", ifa->ifa_name);
                  std::string mac_name(mac_name_temp);
                  mac_name_vec.push_back(mac_name);
				  for (i=0; i <s->sll_halen; i++)
                  {
                      if(i+1!=s->sll_halen)
                      {
					      sprintf(mac_address_temp_ptr,"%02x%c",(s->sll_addr[i]),':');
							mac_address_temp_ptr+=3;
                      }else
                      {
                       		sprintf(mac_address_temp_ptr,"%02x",(s->sll_addr[i]));
							mac_address_temp_ptr+=2; 
                      }
					  //sprintf(mac_address_temp_ptr,"%02x%c",(s->sll_addr[i]),(i+1!=s->sll_halen)?':':'');
					  
                      //printf("%02x%c", (s->sll_addr[i]), (i+1!=s->sll_halen)?':':'\n');
                  }
                  //*mac_address_temp_ptr='\n';
				  std::string mac_address(mac_address_temp);
				  mac_address_vec.push_back(mac_address);
                  //std::cout<<"mac name: "<<mac_name<<", mac address: "<<mac_address<<std::endl;
             }
         }
         freeifaddrs(ifaddr);
        // std::cout<<"second"<<std::endl;
        // for(int i=0;i<mac_name_vec.size();++i)
        // {
        //    std::cout<<"mac name "<<i<<" "<<mac_name_vec[i]<<", mac name size: "<<mac_name_vec[i].size()<<std::endl;
       //  }
         for(int i=0;i<mac_name_vec.size();++i)
         {
            if(mac_name_vec[i]==std::string("eth0"))
            {
                return mac_address_vec[i];
            }
         }
        // std::cout<<"third part."<<std::endl;        
         for(int i=0;i<mac_name_vec.size();++i)
         {
           // std::cout<<"mac name: "<<mac_name_vec[i]<<std::endl;
            if(mac_name_vec[i][0]=='e')
            {
                return mac_address_vec[i];
            }
        }
    }
    return std::string("");
}
std::string getMacAddressIfconfig()
{
    return std::string("");
}
