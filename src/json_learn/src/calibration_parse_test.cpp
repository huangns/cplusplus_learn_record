#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <json/json.h>
#include <iostream>
#include "../include/calibration_parser.h"

int main()
{
    
    std::cout<<"calibration parse ...."<<std::endl;
    calibration_parser cali_parser_obj("../data/calibration.json");
	for(int i=0;i<cali_parser_obj.getCameraVector().size();++i)
	{
		std::cout<<cali_parser_obj.getCameraVector()[i]<<std::endl;
	}
	std::cout<<"T12:\n"<<cali_parser_obj.getT12()<<std::endl;
    return 0;
}
