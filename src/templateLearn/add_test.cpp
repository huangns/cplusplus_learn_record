#include "../include/templateFuncs.h"
#include "../include/myvector.h"
#include "../include/myarray.h"
#include <iostream>
#include <string>

class tc
{
public:
    tc(){std::cout<<"tc construction."<<std::endl;}
    tc(const tc& t){std::cout<<"copy construction"<<std::endl;}
    int operator()(int i, int j){return i+j;};
};

template<typename T>
typename T::size_type getlength(const T& c)
{
    if(c.empty())
	return 0;
    return c.size();
}

typedef int(*Functype)(int , int );
int testfunc(int i, int j, Functype func);
int addfunc(int i, int j);
int multifunc(int i, int j);
template<typename T,typename F>
T testfunc2(const T& i, const T& j, F func)
{
    return func(i,j);
}
template<typename T, typename F = tc>
T testfunc3(const T& i, const T& j, F func=F())
{
    return func(i,j);
}

template<typename T, typename F = Functype>
T testfunc4(const T& i, const T& j, F func=multifunc)
{
    return func(i,j);
}



int main()
{
    double c =funcAdd<double>(1.4,1.5);
    std::cout<<"c: "<<c<<std::endl;
    std::cout<<"c2: "<<funcAdd2<6,9>()<<std::endl;
    std::cout<<"c3: "<<funcAdd3<int,12,13>(11)<<std::endl;
    std::cout<<"c4: "<<funcAdd3<int,12,13>(11.5)<<std::endl; 
    int result = charsComp("test1","test02");
    std::cout<<"char cmp result: "<<result<<std::endl;
    myvector<int> mvi;
    std::cout<<"******** myarray test ***************"<<std::endl;
    myarray<int> myarray1;
    myarray1.myarrayfunc();
    myarray<int,109> myarray2;
   myarray2.myarrayfunc();

   std::cout<<"********* string size test **********"<<std::endl;
   std::string str="lllll";
   std::string::size_type len = getlength(str);
   std::cout<<"len: "<<len<<std::endl;

   std::cout<<"test func ...."<<std::endl;
   std::cout<<"add test: "<<testfunc2(1,2,addfunc)<<std::endl;
   std::cout<<"multi test: "<<testfunc2<int,Functype>(2,3,multifunc)<<std::endl;
   tc t;
   std::cout<<"obj operator test: "<<testfunc2(4,5,t)<<std::endl;
   std::cout<<"obj operator test 2: "<<testfunc2(4,5,tc())<<std::endl;
   std::cout<<"----------------------------------------------"<<std::endl;
   std::cout<<"obj operator test 3: "<<testfunc3(46,78)<<std::endl;
   std::cout<<"obj operator test 4: "<<testfunc4(12,10)<<std::endl;
   std::cout<<"obj operator test 5: "<<testfunc4(12,8,tc())<<std::endl;
    return 0;
}


int testfunc(int i, int j, Functype func)
{
    return func(i,j);
}

int addfunc(int i, int j)
{
    return i+j;
}
int multifunc(int i, int j)
{
    return i*j;
}
