#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <json/json.h>
#include <iostream>
#include <string>
#include "../include/calibration_parser.h"
#include <fstream>
int main()
{
    std::ifstream is;
    is.open("../data/calibration.json", std::ios::binary);
    if(!is.is_open())
    {
        std::cout<<"open file error."<<std::endl;
    }
    std::string str="";
    while(is.good())
    {
      std::string temp;
      is>>temp;
      str+=temp;
    }
    std::cout<<"result: \n"<<str<<std::endl;
  std::string json_file_path2("/home/h/json_test2.json");
  stringToJsonFile(str,json_file_path2);
  return 0;
  return 0;
  std::string json_str("{\"age\" : 26,\"name\" : \"huchao\"}");
  std::string json_file_path("/home/h/json_test.json");
  stringToJsonFile(json_str,json_file_path);
  return 0;
    
    std::cout<<"calibration parse ...."<<std::endl;
    calibration_parser cali_parser_obj("../data/calibration.json");
	for(int i=0;i<cali_parser_obj.getCameraVector().size();++i)
	{
		std::cout<<cali_parser_obj.getCameraVector()[i]<<std::endl;
	}
	std::cout<<"T12:\n"<<cali_parser_obj.getT12()<<std::endl;
    return 0;
}
