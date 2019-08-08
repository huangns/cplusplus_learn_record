#include <iostream>
#include <string>
//#include "../include/template_member.h"
class A
{
public:
    template<typename T>
    void myft(T tmp)
    {
        std::cout<<"tmp: "<<tmp<<std::endl;
    }
};

template<typename C>
class A2
{
public:
    template <typename T>
    A2(T v1,T v2);
    C m_a;
};

template<typename C>
template<typename T>
A2<C>::A2(T v1, T v2)
{
    std::cout<<"v1: "<<v1<<", v2: "<<v2<<std::endl;
}


//template  A3<float>;


int main()
{
    std::cout<<"template class test."<<std::endl;
    A aobj;
    aobj.myft(3);
    aobj.myft(std::string("template class test."));
    
    std::cout<<"------------- A2 test --------------"<<std::endl;
    A2<float> a2_obj(4,5);
    std::cout<<"------------- A3 test --------------"<<std::endl;
    //A3<float> a3(12,13);
    return 0;
}
