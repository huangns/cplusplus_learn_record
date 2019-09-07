#include <memory>
#include <string>
#include <iostream>
#include <map>

using namespace std;

auto myfunc()
{
	return unique_ptr<string>(new string("unique_ptr -> shared_ptr"));//这是个右值
}

int main()
{
	//1.unique_ptr：同一时刻，只能有一个unique_ptr指针指向这个对象(这块内存)
	//当这个unique_ptr被销毁的时候，它所指向的对象也被销毁
	//格式：
	//1.1 常规初始化
	unique_ptr<int> pi;
	if(nullptr==pi)
	{
		cout<<"pi is null pointer."<<std::endl;
	}
	unique_ptr<int> pi2(new int(109));
	std::cout<<"pi2 point value: "<<*pi2<<std::endl;
	//1.2 make_unique函数
	//c++11 中没有， c++14才有的make_unique:不支持指定的删除器
	//语法，如果不用删除器，建议优先选用，更高的性能
	//unique_ptr<int> p1 = make_unique<int>(100);
	//audo p2 = make_unique<int>(100);
	
	//unique_ptr 常用操作
	//2.1 unique_ptr不支持的操作，独占式
	unique_ptr<string> ps1(new string("unique_ptr learn."));
	//unique_ptr<string> ps2(ps1);该智能指针，不支持拷贝动作
	//unique_ptr<string> ps3 = ps1;不支持拷贝动作
	//unique_ptr<string> ps4;
	//ps4 = ps1; 不支持赋值操作
	
	//2.2 移动语义
	 unique_ptr<string> ps2;
	 ps2 = std::move(ps1);
	 std::cout<<"*ps2: "<<*ps2<<std::endl;
	 //std::cout<<"*ps1: "<<*ps1<<std::endl; nullptr
	 
	//2.3 release(): 放弃对指针的控制权（切断了智能指针和其所指向的对象之间的联系）
	//返回裸指针，将该智能指针置空，返回的这个裸指针可以手工release释放
	//也可以用来初始化另外一个智能指针,share_ptr.get()返回的是指向的裸指针，但是并不会释放
	unique_ptr<string> ps3(new string("unique_ptr release()"));
	unique_ptr<string> ps4(ps3.release());
	if(nullptr==ps3)
	{
		cout<<"ps3 become nullptr."<<std::endl;
	}
	//ps4.release()会导致内存泄漏
	string* str_temp = ps4.release();
	cout<<"str_temp: "<<*str_temp<<std::endl;
	delete str_temp;
	
	//2.4 reset()
	//reset()不带参数的情况，释放智能指针所指向的对象，并将智能指针置空
	unique_ptr<string> ps5(new string("unique_ptr reset()."));
	ps5.reset();
	if(nullptr==ps5)
	{
		cout<<"ps5 become nullptr after reset."<<endl;
	}
	//reset()带参数(裸指针)的情况，释放智能所指向的对象，并让该智能指针指向新对象
	unique_ptr<string> ps6(new string("unique_ptr reset(**)."));
	ps5.reset(ps6.release());
	if(ps6==nullptr)
	{
		std::cout<<"ps6 become nullptr."<<std::endl;
		std::cout<<"*ps5: "<<*ps5<<std::endl;
	}
	
	//2.5 =nullptr 释放智能指针所指向的对象，并将智能指针置空
	//unique_ptr<string> ps7(new string("=nullptr operator"));
	//ps7=nullptr; //释放ps7所指向的对象，并ps7置空
	
	//2.6 指向一个数组，这个数组不需要指定删除器，可以自动释放内存，和shared_ptr不同
	unique_ptr<int[]> ptrarray(new int[10]);
	ptrarray[0]=12;
	ptrarray[1]=24;
	
	//2.7 get();返回智能指针中保存的裸指针
	//2.8 *解引用
	//2.9 swap 交换两个智能指针所指向的对象
	//std::swap(ps1,ps2);
	//ps1.swap(ps2);
	
	//2.10 将智能指针名字作为一个判断条件
	//if(ps1){std::cour<<"ptr is not null."<<std::endl;}
	//else {std::cout<<"ptr is null."<<std::endl; }
	
	
	//2.11 转换成shared_ptr类型：如果unique_ptr为右值，就可以将它赋值给shared_ptr
	//因为shared_ptr包含一个显示构造函数，可以用于将右值unique_ptr转换为shared_ptr,shared_ptr
	//将接管原来归unique_ptr所拥有的内容
	shared_ptr<string> ps10 = myfunc();//这里会创建一个控制块
	std::cout<<"ps10: "<<*ps10<<std::endl;
	
	unique_ptr<string> ps11(new string("unique_ptr -> shared_ptr 2"));
	shared_ptr<string> ps12 = std::move(ps11);
	std::cout<<"ps12: "<<*ps12<<std::endl;
}
