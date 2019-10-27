#include "calibration_parser.h"
#include "json/json.h"
#include <iostream>
#include <sstream>
#include <fstream>
calibration_parser::calibration_parser(const std::string& json_file)
{
    std::cout<<"calibration_parser construct function ...."<<std::endl;
    std::cout<<"json file path: "<<json_file<<std::endl;
    Json::Reader reader;
    Json::Value value;
    std::ifstream is;
    is.open(json_file.c_str(), std::ios::binary);
    if(!is.is_open())
    {
        std::cout<<"open file error."<<std::endl;
    }
    
    reader.parse(is,value);
    
    camera_struct cs1;
    cs1.camera_model = value["camera_1"]["model"].asString();
    cs1.img_path = value["camera_1"]["img_path"].asString();
  	if(cs1.camera_model==std::string("pinhole"))
    {
        std::cout<<"pinhole data."<<std::endl;
        cs1.intrinsics<<0.0,
			value["camera_1"]["intrinsics"][0].asDouble(),
			value["camera_1"]["intrinsics"][1].asDouble(),
			value["camera_1"]["intrinsics"][2].asDouble(),
			value["camera_1"]["intrinsics"][3].asDouble();
    }else if(cs1.camera_model==std::string("omni"))
    {
        std::cout<<"omni data"<<std::endl;
        cs1.intrinsics<<
            value["camera_1"]["intrinsics"][0].asDouble(),
			value["camera_1"]["intrinsics"][1].asDouble(),
			value["camera_1"]["intrinsics"][2].asDouble(),
			value["camera_1"]["intrinsics"][3].asDouble(),
			value["camera_1"]["intrinsics"][4].asDouble();
    }else
    {
        std::cerr<<"please input correct camera model for camera 1."<<std::endl;
        exit(0);
    }
    cs1.distortions<<value["camera_1"]["distortions"][0].asDouble(),
                    value["camera_1"]["distortions"][1].asDouble(),
					value["camera_1"]["distortions"][2].asDouble(),
					value["camera_1"]["distortions"][3].asDouble();
	//std::cout<<"cs1: "<<cs1<<std::endl;


	camera_struct cs2;
    cs2.camera_model = value["camera_2"]["model"].asString();
    cs2.img_path = value["camera_2"]["img_path"].asString();
  	if(cs2.camera_model==std::string("pinhole"))
    {
        //std::cout<<"pinhole data."<<std::endl;
        cs2.intrinsics<<0.0,
			value["camera_2"]["intrinsics"][0].asDouble(),
			value["camera_2"]["intrinsics"][1].asDouble(),
			value["camera_2"]["intrinsics"][2].asDouble(),
			value["camera_2"]["intrinsics"][3].asDouble();
    }else if(cs2.camera_model==std::string("omni"))
    {
        //std::cout<<"omni data"<<std::endl;
        cs2.intrinsics<<
            value["camera_2"]["intrinsics"][0].asDouble(),
			value["camera_2"]["intrinsics"][1].asDouble(),
			value["camera_2"]["intrinsics"][2].asDouble(),
			value["camera_2"]["intrinsics"][3].asDouble(),
			value["camera_2"]["intrinsics"][4].asDouble();
    }else
    {
        std::cerr<<"please input correct camera model for camera 1."<<std::endl;
        exit(0);
    }
    cs2.distortions<<value["camera_2"]["distortions"][0].asDouble(),
                    value["camera_2"]["distortions"][1].asDouble(),
					value["camera_2"]["distortions"][2].asDouble(),
					value["camera_2"]["distortions"][3].asDouble();
	//std::cout<<"cs2: "<<cs2<<std::endl;

	camera_vector.push_back(cs1);
	camera_vector.push_back(cs2);

	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			T12(i,j)=value["T12"][i*4+j].asDouble();
		}
	}
	//std::cout<<"T12:\n"<<T12<<std::endl;
    //if(!reader.parse(is,value))
   // {
   //     std::cerr<<"parse json file failed, exit!"<<std::endl;
   //     exit(0);
   // }

}
const std::vector<camera_struct>& calibration_parser::getCameraVector()
{
    return camera_vector;
}
const Eigen::Matrix4d& calibration_parser::getT12()
{
    return T12;
}


bool stringToJsonFile(const std::string& json_str,const std::string& json_file_path)
{
  Json::Reader json_reader;
  Json::Value json_value;
  if(!json_reader.parse(json_str,json_value))
  {
    std::cerr<<"json str parse failed!"<<std::endl;
    return false;
  }
  Json::StyledWriter styled_writer;
  std::ofstream json_file(json_file_path);
  json_file<<styled_writer.write(json_value);
  return true;
}