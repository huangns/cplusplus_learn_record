#include <iostream>
#include <array>
#include <string>
int main()
{
    std::cout<<"array test..."<<std::endl;
    std::array<std::string,5> str_arr={"array","test1","test2","test3","test4"};
    for(int i=0;i<str_arr.size();++i)
    {
        std::cout<<str_arr[i]<<std::endl;
    }
    return 0;
}

