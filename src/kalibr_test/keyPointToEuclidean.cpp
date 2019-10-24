#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>
typedef Eigen::Matrix<double,5,1> Vector5d;
bool keypointToEuclidean(Vector5d& intrinsics, Eigen::Vector4d& distortion_coeffes, Eigen::Vector2d& keypoint2d, Eigen::Vector3d& outPoint3d);
void undistort(Eigen::Vector4d& distortion_coeffes,Eigen::Vector2d& y);
void distort(Eigen::Vector4d& distortion_coeffes,Eigen::Vector2d& y, Eigen::Matrix2d& F);
int main()
{
  std::cout<<"2d_to_3d."<<std::endl;
  Vector5d intrinsics;
  intrinsics<<1.0,1000,1000,500,500;
  Eigen::Vector4d distortion_coeffes;
  distortion_coeffes<<0.1,0.0,0.1,0.1;
  double depth = 5;
  Eigen::Vector2d keypoint2d;
  keypoint2d<<640,320;
  Eigen::Vector3d outPoint3d;//result
  keypointToEuclidean(intrinsics,distortion_coeffes,depth,keypoint2d,outPoint3d);
  return 0;
}

bool keypointToEuclidean(Vector5d& intrinsics, Eigen::Vector4d& distortion_coeffes,double depth, Eigen::Vector2d& keypoint2d, Eigen::Vector3d& outPoint3d)
{
  double xi = intrinsics[0];
  double fx = intrinsics[1];
  double fy = intrinsics[2];
  double cx = intrinsics[3];
  double cy = intrinsics[4];
  
  Eigen::Vector2d outPoint2d;
  outPoint2d[0] = (keypoint2d[0] - cx)/fx;
  outPoint2d[1] = (keypoint2d[1] - cy)/fy;
  undistort(distortion_coeffes,outPoint2d);
  double rho2_d = outPoint2d[0] * outPoint2d[0] + outPoint2d[1] * outPoint2d[1];

  //if (!isUndistortedKeypointValid(rho2_d))
  //  return false;
  outPoint3d[0]=outPoint2d[0];
  outPoint3d[1]=outPoint2d[1];
  outPoint3d[2] = 1
      - xi * (rho2_d + 1) / (xi + sqrt(1 + (1 - xi * xi) * rho2_d));
  double outPoint3dNorm = sqrt(outPoint3d[0]*outPoint3d[0] +  outPoint3d[1]*outPoint3d[1] + outPoint3d[2]*outPoint3d[2]);
  
  outPoint3d/=outPoint3dNorm;
  outPoint3d*=depth;
  return true;
}

void undistort(Eigen::Vector4d& distortion_coeffes,Eigen::Vector2d& y){
  
  Eigen::Vector2d ybar = y;
  const int n = 5;
  
  Eigen::Matrix2d F;//2*2矩阵

  Eigen::Vector2d y_tmp;

  for (int i = 0; i < n; i++) {

    y_tmp = ybar;

    distort(distortion_coeffes,y_tmp, F);

    Eigen::Vector2d e(y - y_tmp);
    Eigen::Vector2d du = (F.transpose() * F).inverse() * F.transpose() * e;
    ybar += du;

    if (e.dot(e) < 1e-15)//e[0]*e[0] + e[1]*e[1]
      break;
  }
  y = ybar;
}

void distort(Eigen::Vector4d& distortion_coeffes,Eigen::Vector2d& y, Eigen::Matrix2d& F)
{
  F.setZero();
  double k1 = distortion_coeffes[0];
  double k2 = distortion_coeffes[1];
  double p1 = distortion_coeffes[2];
  double p2 = distortion_coeffes[3];
  
  double mx2_u, my2_u, mxy_u, rho2_u, rad_dist_u;
  mx2_u = y[0] * y[0];
  my2_u = y[1] * y[1];
  mxy_u = y[0] * y[1];
  rho2_u = mx2_u + my2_u;
  
  rad_dist_u = k1 * rho2_u + k2 * rho2_u * rho2_u;

  F(0, 0) = 1 + rad_dist_u + k1 * 2.0 * mx2_u + k2 * rho2_u * 4 * mx2_u
      + 2.0 * p1 * y[1] + 6 * p2 * y[0];
  F(1, 0) = k1 * 2.0 * y[0] * y[1] + k2 * 4 * rho2_u * y[0] * y[1]
      + p1 * 2.0 * y[0] + 2.0 * p2 * y[1];
  F(0, 1) = F(1, 0);
  F(1, 1) = 1 + rad_dist_u + k1 * 2.0 * my2_u + k2 * rho2_u * 4 * my2_u
      + 6 * p1 * y[1] + 2.0 * p2 * y[0];

  y[0] += y[0] * rad_dist_u + 2.0 * p1 * mxy_u + p2 * (rho2_u + 2.0 * mx2_u);
  y[1] += y[1] * rad_dist_u + 2.0 * p2 * mxy_u + p1 * (rho2_u + 2.0 * my2_u);

}
