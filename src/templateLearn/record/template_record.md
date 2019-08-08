template <typename T>;//T代表一个类型，是一个类型参数

template<int a, int b>//非类型参数代表一个值
int funcAdd2()
{
	return a+b;
}
当模版被实例化时，这种非类型模版参数的值或者是用户提供的，或者是编译器
推断的，都有可能，但是这些值必须都得是常量表达式，因为实例化
这些模版是编译器在编译的时候来实例化的。

int c = funcAdd2<12,13>();//显式指定模版参数，在尖括号中提供额外的参数。

template<typename T, int a, int b>
int add(T c)
{
    return (int)c+a+b;
}

int result = add<int,12,12>(13);


template<unsigned L1, unsigned L2>
int charsComp(const char(&p1)[L1], const char(&p2)[L2])
{
    return std::strcmp(p1,p2);
}


int charsComp("test1","test");//这里之所以不用<>提前写入字符大小，
是因为系统会根据test1的长度6个，test长度为5，取代L1,L2;
模版函数可以是inline的，关键字放在模版列表后面。

编译器不能为类模版推断模板类参数类型，所以必须使用类模版，必须在
模板名后边用<>来提供额外的信息，这些信息其实就是对应着模板。

类模板一旦被实例化后，那么这个模板的每个实例都会有自己版本的成员
函数，所以类模版的成员函数具有和这个类模板相同的模板参数（类模板的
成员函数是有模板参数的）
如果你要把类模板的成员函数的定义写在模板定义的外边，那么这个成员函数的
模板参数就体现出来了。
template<typename T>
class myvector
{
    public:
	typedef T* myiterator;
	myiterator mybegin();
}

template<typename T>
typename myvector<T>::myiterator myvector<T>::mybegin()
{
//这里 typename必须写，表明myvector<T>::myiterator是一个类型，因为
//编译器在编译的时候无法确定其是类型还是静态成员（这个只有在运行的时候才能确定）
 //....
}


定义在类模板之外的成员函数必须以关键字template开始，后边接类模板参数
列表。同时在，类名后边要用尖括号<>把模板参数列表里边的所有模板
参数名列出来，如果是多个模板参数，用,分隔。
template<typename T>
myvector<T>::myvector()
{
	//
}
myvector<T>& myvector<T>::operator==(const myvector& )

//非模版类型参数

#include <iostream>
template<typename T, int size = 10>//缺省值要一起放在最后
class myarray
{
public:
    T arr[size];
   // myarray();
    void myarrayfunc();
};

template<typename T, int size>
void myarray<T,size>::myarrayfunc()
{
    std::cout<<"size: "<<size<<std::endl;
    return;
}
非类型模板参数有一些限制：
（1）浮点型不能作为非类型模板参数，比如float,double 
(2)类类型通常也不允许。

typename的使用场合：
1.在模板定义里面，表明其后的模板参数是类型参数
2.类类型

example2:
template<typename T>
typename T::size_type getlength(const T& c)
{
    if(c.empty())
	    return 0;
	return c.size();
}


缺省值：
(1)类模版
template <typename T=string, int size=5>
class myarray
{
    private:
	T arr[size];
	public:
	void myfunc;
}


myarray<> abc;//因为都有缺省值，所以<>可以不要加类型，但是<>必须加

myarray<int> abcd;

(2)函数模板：老标准只能为为类模板提供默认模板参数，C++11新标准可以
为函数模板提供默认参数。
a: 同时给模板参数和函数参数提供缺省值
b: 注意写法 F funcpoint = F();



//20190809
一、普通类的成员函数模板
//不管是普通类，还是类模板，它的成员函数可以是一个函数模板，称为“成员函数模板”，不可以是虚函数。
二、类模板的成员函数模板
//类模板的模板参数必须用<>指定，成员函数模板的参数可以推断。  
//类模版的成员函数（包括普通成员函数、成员函数模板）只有为程序所用（代码中出现了对该函数或者该函数模板的的调用才实例化）
//如果某函数从未被使用，则不会实例化该成员函数。

三、模板显式实例化， 模板声明
//为了防止在多个.cpp文件中都实例化相同的类模板，所以c++11提出了一个
解决方法，称为显式实例化；通过显式实例化来。

//显式实例化 手段中的实例化定义（defination），这种实例化定义只需要在一个.cpp文件中写就可以了。
template A2<float>;

而在其它cpp文件中的 显式实例化 手段中的实例化声明

extern template A2<float>;
 






















