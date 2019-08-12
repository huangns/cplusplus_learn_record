#include <iostream>

//可变参数模板 variadic templates :允许模版中含有0个到任意个模板参数，在语法上也和传统模板不太一样，多了一个 ...
//模板参数可以为任意类型
//T后边带了...，所以称呼T为可变参类型
//args代表的是一包形参
template <typename... T>
void variadicTemplateFunc(T... args)
{
	std::cout<<"sizeof...(args): "<<sizeof...(args)<<std::endl;
	std::cout<<"sizeof...(T): "<<sizeof...(T)<<std::endl;
}

void variadicTemplateTestFunc()
{
	variadicTemplateFunc();
	variadicTemplateFunc(10,20);
	variadicTemplateFunc(10,1.2,'a',"huang");
}

template<typename T, typename... U>
void variadicTemplateFunc2(const T& firstarg, const U&... secondarg)
{
	std::cout<<"sizeof...(secondarg): "<<sizeof...(secondarg)<<std::endl;
}
void variadicTemplateTestFunc2()
{
	variadicTemplateFunc2(10);
	variadicTemplateFunc2(20,1.5,8,'c',"ch");
}
//1.2 参数包展开
//展开套路比较固定，一般都是用递归函数的方式来展开函数
//一个参数，一包参数，这种可变参函数模板写法最适合参数包的展开
// void variadicTemplateFunc2(const T& firstarg, const U&... secondarg)
void variadic_template_recursion()
{
	std::cout<<"parameter bag recursion over."<<std::endl;
}
template<typename T, typename... U>
void variadic_template_recursion(const T& firstarg, const U&... otherarg)
{
	std::cout<<"receive value: "<<firstarg<<std::endl;
	variadic_template_recursion(otherarg...);
}
//2：可变参类模板：允许模板定义中含有0到任意个模板参数
//2.1可通过递归继承的方式展开参数包

template<typename... args> class myclass{};//主模板
template<> class myclass<>{//0个模板参数的特化版本
	public:
	myclass()
	{
		std::cout<<"myclass<>::myclass(),this="<<this<<std::endl;
	}
};

template<typename First, typename... Others>
class myclass<First,Others...>:private myclass<Others...>//偏特化
{
	public:
	myclass():m_i(0)
	{
		std::cout<<"myclass<First,Others...>,this:"<<this<<std::endl;
	}
	myclass(First fp, Others... op):m_i(fp),myclass<Others...>(op...)
	{
		std::cout<<"--------------------- begin --------------------"<<std::endl;
		std::cout<<"myclass::myclass(First fp, Others... op) version,this: "<<this<<std::endl;
		std::cout<<"m_i: "<<m_i<<std::endl;
		std::cout<<"--------------------- end ----------------------"<<std::endl;
	}
	First m_i;
};

int main()
{
	variadicTemplateTestFunc();
	variadicTemplateTestFunc2();
    variadic_template_recursion(1,1.2,4.1,-8,'c',9,"hu");
	std::cout<<"---------------- variadic template for class --------------"<<std::endl;
	//myclass<int,float,double> myclassobj;
	myclass<int,float,double> myclassobj2(1,10.0,12.333);
	return 0;
}
