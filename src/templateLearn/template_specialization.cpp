#include <iostream>

template<typename T1, typename T2>
struct template_spec 
{
  template_spec()
  {
    std::cout<<"template generalization version construction."<<std::endl;
  }
  void test()
  {
    std::cout<<"template generalization version."<<std::endl;
  }
};

template <>
struct template_spec<int,int> 
{
  template_spec()
  {
    std::cout<<"template specialization version: <int, int> construction."<<std::endl;
  }
  void test()
  {
    std::cout<<"template specialization version: <int, int>."<<std::endl;
  }
};

template <>
struct template_spec<int,double> 
{
  template_spec()
  {
    std::cout<<"template specialization version: <int, double> construction."<<std::endl;
  }
  void test()
  {
    std::cout<<"template specialization version: <int, double>."<<std::endl;
  }
};

//特化成员函数，而不是模板
template<>
void template_spec<double,double>::test()
{
  std::cout<<"template member function specialization version: <double, double>."<<std::endl;
}


//类模板偏特化
//1.模板参数数量 2.模板参数数量上
template<typename T1, typename T2, typename T3>
struct template_local_spec
{
  template_local_spec(){
    std::cout<<"template_local_spec generalization version construction."<<std::endl;
  }
  void test()
  {
    std::cout<<"template_local_spec generalization version test function."<<std::endl;
  }
};

template<typename T2>
struct template_local_spec<int,T2,int>
{
  template_local_spec(){
    std::cout<<"template_local_spec<int,T2,int> version construction."<<std::endl;
  }
  void test()
  {
    std::cout<<"template_local_spec<int,T2,int> version test function"<<std::endl;
  }
};

//函数没有偏特化版本
template<>
void template_local_spec<double,double,double>::test()
{
  std::cout<<"template_local_spec version, <double,T2,double> local_spec function."<<std::endl;
}

//模板参数范围
template<typename T>
struct template_local_spec2
{
  template_local_spec2()
  {
    std::cout<<"template_local_spec2 generalization version construction."<<std::endl;
  }
};

template<typename T>
struct template_local_spec2<T*>
{
  template_local_spec2()
  {
     std::cout<<"template_local_spec2 T* version construction."<<std::endl;
  }
};


template<typename T>
struct template_local_spec2<const T>
{
  template_local_spec2()
  {
     std::cout<<"template_local_spec2 const T version construction."<<std::endl;
  }
};

template<typename T>
struct template_local_spec2<T&>
{
  template_local_spec2()
  {
     std::cout<<"template_local_spec2 T& version construction."<<std::endl;
  }
};

template<typename T>
struct template_local_spec2<T&&>
{
  template_local_spec2()
  {
     std::cout<<"template_local_spec2 T&& version construction."<<std::endl;
  }
};

//函数模板+全特化
template <typename T1, typename T2>
void template_function(T1& t1, T2& t2)
{
  std::cout<<"template function generalization version."<<std::endl;
  std::cout<<"first: "<<t1<<std::endl;
  std::cout<<"second: "<<t2<<std::endl;
}
template<>
void template_function(double& t1,int& t2)
{
  std::cout<<"template function(double&,int&) version."<<std::endl;
  std::cout<<"first: "<<t1<<std::endl;
  std::cout<<"second: "<<t2<<std::endl;
}

int main()
{
  //特化：对特殊的类型（类型模版参数）进行特殊的对待，给他开小灶，给它写适合它的专用代码
  //一：类模版特化
  //1.1 类模板全特化
  //a)常规全特化
  //必须先有泛化版本，才能存在特化版本，只要涉及特化，一定先存在泛化
  //特化版本代码编译器会优先选择
  
  std::cout<<"----------------- template specialization test ---------------------"<<std::endl;
  template_spec<double,int> tsobj1;
  tsobj1.test();
  template_spec<int,int> tsobj2;
  tsobj2.test();
  template_spec<int,double> tsobj3;
  tsobj3.test();
  
  template_spec<double,double> tsobj4;//任然是泛化版本对象，调用的是泛化版本的构造函数
  tsobj4.test();//因为特化了double, double类型的test函数，所以这里调用的是特化版本的test函数
  
  
  std::cout<<"----------------- template local specialization test ---------------"<<std::endl;
  template_local_spec<int,double,double> tlsobj1;
  tlsobj1.test();
  template_local_spec<int,double,int> tlsobj2;
  tlsobj2.test();
  template_local_spec<int,int,int> tlsobj3;
  tlsobj3.test();
  template_local_spec<double,double,double> tlsobj4;
  tlsobj4.test();
  
  std::cout<<"----------------- template local specialization const T, T*,  T&, T&& version test --------------- "<<std::endl;
  template_local_spec2<double> tls2obj1;
  template_local_spec2<double*> tls2obj2;
  template_local_spec2<const double> tls2obj3;
  template_local_spec2<double&> tls2obj4;
  template_local_spec2<double&&> tls2obj5;
  template_local_spec2<int> tls2obj6;
  
  std::cout<<"----------------- template function test ----------------------"<<std::endl;
  const char* pcchar = "CPP";
  int i=9;
  template_function(pcchar,i);
  double j=78.9;
  template_function(j,i);
  
  
  
  
  return 0;
}


/*
 特化：对特殊的类型（类型模版参数）进行特殊的对待，给他开小灶，给它写适合它的专用代码
一：类模版特化
1.1 类模板全特化
a)常规全特化
//必须先有泛化版本，才能存在特化版本，只要涉及特化，一定先存在泛化
//特化版本代码编译器会优先选择


//局部特化， 特化完了之后它本质上还是个模板，全特化，完了之后等于一个具体的类。
全特化函数模板实际上等价于实例化一个函数模板，并不是等价于一个函数重载 
编译器选择最合适，普通优先，特化版本，泛化版本
 
 */
