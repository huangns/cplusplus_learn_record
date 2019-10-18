#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <string>

struct camera_struct
{
    std::string camera_model;
    std::string img_path;
    Eigen::Matrix<double,5,1> intrinsics;
    Eigen::Matrix<double,4,1> distortions;
    //double xi,fx,fy,cx,cy;
  //  double k1,k2,p1,p2;
    friend std::ostream& operator<<(std::ostream& os, const camera_struct& cs)
    {
        os<<"model: "<<cs.camera_model<<std::endl;
        os<<"img_path: "<<cs.img_path<<std::endl;
        os<<"intrinsics: ["<<cs.intrinsics[0]<<", "<<cs.intrinsics[1]<<" , "<<cs.intrinsics[2]<<" , "<<cs.intrinsics[3]<<" , "<<cs.intrinsics[4]<<"]"<<std::endl;
        os<<"distortions: [";
        for(int i=0;i<4;++i)
        {
            os<<cs.distortions[i];
			if(i!=3)
				os<<" , ";
        }
        os<<"]"<<std::endl;
        return os;
    }

};
class calibration_parser
{
public:
    explicit calibration_parser(const std::string& json_file);
    const std::vector<camera_struct>& getCameraVector();
    const Eigen::Matrix4d& getT12();
private:
    std::vector<camera_struct> camera_vector;
    Eigen::Matrix4d T12;
};
