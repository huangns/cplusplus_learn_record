#include <iostream>
#include <string>
#include <vector>
#include <regex>
 
std::vector<std::string> regexsplit(const std::string& input)
{ 
    std::regex re(",");
    std::sregex_token_iterator p(input.begin(), input.end(), re, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> vec;
    while (p != end)
        vec.emplace_back(*p++);
    return std::move(vec);
}

//进来之前判断是否等于70
//! sizeof(gprmc)>=70
std::string gprmcCutting(const std::string& str)
{
  char new_gprmc[]="$GPRMC,000000.00,A,0000.00000,N,00000.00000,E,0.000,,000000,,,0,0*00\r\n";
  
  std::vector<std::string> split_vec=regexsplit(str);
  
  memcpy(new_gprmc+7,split_vec[1].c_str(),9);
  memcpy(new_gprmc+19,split_vec[3].c_str(),10);
  memcpy(new_gprmc+32,split_vec[5].c_str(),11);
  memcpy(new_gprmc+46,split_vec[7].c_str(),5);
  memcpy(new_gprmc+53,split_vec[9].c_str(),6);
  memcpy(new_gprmc+62,split_vec[12].c_str(),1);
  memcpy(new_gprmc+64,split_vec[13].c_str(),4);    
  return std::move(std::string(new_gprmc,new_gprmc+70));
}

bool checkTimeConsistency(const char* gprmc)
{
  //utc_now: get utc from gettimeofday
  //utc_gprmc:get utc time from gprmc
  //if(std::abs(utc_now-utc_gprmc)<0.4)
 // {
 //   return true;
 // }else
 // {
 //   return false;
 // }
}


int main()
{
  std::string gprmc("$GPRMC,085721.00,A,3958.92733,N,11618.18395,E,0.061,0.56,191219,,,A,V*05");
  std::string result=gprmcCutting(gprmc);
  std::cout<<"1:"<<result;
  std::cout<<"2:"<<gprmc<<std::endl;
  std::cout<<"size:"<<result.size()<<std::endl;
  std::vector<std::string> split_vec=regexsplit(gprmc);
  for(auto x:split_vec)
  {
    //std::cout<<"size: "<<x.size()<<" :"<<x<<std::endl;
  }
  return 0;
}


