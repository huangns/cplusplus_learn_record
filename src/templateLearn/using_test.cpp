#include <iostream>
#include <map>
#include <string>
//template 中，手动指定优先于自动推断
template<typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i+j;
	return result;
}
/*
double result = sum<double,double,double>(2000000000,2000000000);

*/


//C++ 98
template<typename T>
struct map_s_x
{
	typedef std::map<std::string,T> type;
};


//C++ 11
//using 用来给一个“类型模板”起别名用的
template<typename T>
using map_s_x_type = std::map<std::string,T>;

typedef int(*typedefFuncType)(int,int);
using usingFuncType = int(*)(int,int);
int addFunc(int a, int b);
int multFunc(int a, int b);
int typeDefinitionTest(int a, int b, typedefFuncType tFTobj);//要传递的是类型值
int usingDefinitionTest(int a, int b, usingFuncType uFTobj);

template<typename T>
using usingFuncType_template = T(*)(T,T);

template<typename T>
T usingDefinitionTemplateTest(T a, T b, usingFuncType_template<T> uFTtobj)
{
	return uFTtobj(a,b);
}
int main()
{
	std::cout<<"---------------- typedef -----------------"<<std::endl;
	//typedef unsigned int u_int;
	using u_int = unsigned int;
	u_int x =189;
	std::cout<<"u_int x: "<<x<<std::endl;
	typedef std::map<std::string,std::string> map_s_s;
	map_s_s mssObj;
	mssObj.insert({"C","PlusPlus"});
	std::cout<<mssObj.begin()->first<<" "<<mssObj.begin()->second<<std::endl;
	
	std::cout<<"---------------- typedef + arbitrary -------------"<<std::endl;
	map_s_x<std::string>::type map_s_x_obj;
	map_s_x_obj.insert({"PlusPlus","C"});
	std::cout<<map_s_x_obj.begin()->first<<" "<<map_s_x_obj.begin()->second<<std::endl;
	
	std::cout<<"---------------- using example -------------------"<<std::endl;
	map_s_x_type<std::string> map_s_x_type_obj;
	map_s_x_type_obj.insert({"C PlusPlus","using test"});
	std::cout<<map_s_x_type_obj.begin()->first<<" "<<map_s_x_type_obj.begin()->second<<std::endl;

	std::cout<<"----------------- typedef function pointer test -----------------"<<std::endl;
	std::cout<<"add function: "<<typeDefinitionTest(12,13,addFunc)<<std::endl;
	std::cout<<"mult function: "<<typeDefinitionTest(12,10,multFunc)<<std::endl;
	//typedefFuncType tft = addFunc;
	//std::cout<<"tft result: "<<tft(12,13)<<std::endl;
    std::cout<<"----------------- using function pointer test -----------------"<<std::endl;
	std::cout<<"add function: "<<usingDefinitionTest(12,13,addFunc)<<std::endl;
	std::cout<<"mult function: "<<usingDefinitionTest(12,10,multFunc)<<std::endl;
	
	std::cout<<"----------------- using function template pointer test -----------"<<std::endl;
	std::cout<<"add function: "<<usingDefinitionTemplateTest(12,13,addFunc)<<std::endl;
	std::cout<<"mult function: "<<usingDefinitionTemplateTest(12,10,multFunc)<<std::endl;
	
	return 0;
}
int addFunc(int a, int b)
{
	return a+b;
}

int multFunc(int a, int b)
{
	return a*b;
}
//error!!!
//int typeDefinitionTest(int a, int b, typedefFuncType)
//{
	//return typedefFuncType(a,b);//应该要通过这个类型的一个对象来调用，而不是这个类型来调用
//}

int typeDefinitionTest(int a, int b, typedefFuncType tFTobj)
{
	//int c = typedefFuncType(a,b);
	//return 0;
	return tFTobj(a,b);
}

int usingDefinitionTest(int a, int b, usingFuncType uFTobj)
{
	return uFTobj(a,b);
}


