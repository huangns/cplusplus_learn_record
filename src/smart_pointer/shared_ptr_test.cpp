#include <iostream>
#include <memory>
#include <string>
#include <vector>
void share_ptr_test_func(std::shared_ptr<int> spobj)
{
  std::cout<<"spobj value: "<<*spobj<<std::endl;
  std::cout<<"spobj ptr ref count: "<<spobj.use_count()<<std::endl;
}

std::shared_ptr<int> share_ptr_return_func(const std::shared_ptr<int>& spobj)
{
  return spobj;
}

void myDelete(int* p)
{
  std::cout<<"launch my delete function."<<std::endl;
  delete p;
}

template <typename T>
std::shared_ptr<T> make_shared_ptr_array(std::size_t size)
{
  return std::shared_ptr<T>(new T[size],std::default_delete<T[]>());
}


int main()
{
  std::cout<<"share_ptr learn."<<std::endl;
 
  //一： share_ptr引用计数的增加和减少
  //每一个share_ptr的拷贝都指向相同的内存对象
  //(1.1)引用计数的增加
  //每个share_ptr对象都会记录有多少个其他的share_ptr指向了相同的对象
  //a.用p6来初始化p7这个智能指针；
  //b.把智能指针当做实参往函数里面传递（非引用）
  auto p6 = std::make_shared<int>(100);
  std::cout<<"6: ptr ref count: "<<p6.use_count()<<std::endl;
  auto p7(p6);
  std::cout<<"6: ptr ref count: "<<p6.use_count()<<std::endl;
  std::cout<<"7: ptr ref count: "<<p7.use_count()<<std::endl;
  share_ptr_test_func(p7);
  std::cout<<"6: ptr ref count: "<<p6.use_count()<<std::endl;
  std::cout<<"7: ptr ref count: "<<p7.use_count()<<std::endl;
  //c.作为函数的返回值
  auto p8 = share_ptr_return_func(p7);//如果没有p8来接这个，则临时对象被销毁后，引用计数会自动从3降低到2
  std::cout<<"6: ptr ref count: "<<p6.use_count()<<std::endl;
  std::cout<<"7: ptr ref count: "<<p7.use_count()<<std::endl;
  std::cout<<"8: ptr ref count: "<<p8.use_count()<<std::endl;
  
  //1.2 引用计数减少
  std::cout<<"------------------------ ref count down -------------------------------"<<std::endl;
  //a.给share_ptr对象赋予新的值，让其指向新的对象
  // p8指向新对象， p6,p7引用对象减去1
  p8 = std::make_shared<int>(200);
  std::cout<<"6: ptr ref count: "<<p6.use_count()<<std::endl;
  std::cout<<"7: ptr ref count: "<<p7.use_count()<<std::endl;
  std::cout<<"8: ptr ref count: "<<p8.use_count()<<std::endl;
  //b. 局部的shared_ptr离开其作用域
  
  //c： 当一个share_ptr引用计数从1变为0，则他会自动释放自己所管理的对象
  
  
  
  /************************二： share_ptr 操作 **************************/
  //2.1 use_count(): 返回多少个智能指针指向某个对象
  //2.2 unique():是否该智能指针独占某个指向的对象, 如果是个未指向任何对象的智能指针对象，也不能算是独享，如std::shared_ptr<int> mptr; mptr.unique() 结果为false
  //2.3: 
  std::shared_ptr<int> p1(new int(100));
  if(p1.unique())
  {
    std::cout<<"ptr unique, the value is: "<<*p1<<std:: endl;
  }
  std::shared_ptr<int> p2(p1);
  if(p1.unique())
  {
     std::cout<<"ptr unique, the value is: "<<*p1<<std:: endl;
  }else
  {
    std::cout<<"ptr is not unique."<<std::endl;
  }
  //2.3 reset():恢复（复位、重置）的意思
  //a)reset（）不带参数的时候
  //若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空
  //若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但指向该对象的引用计数会减少1，同时将pi置空
  
  std::shared_ptr<int> pi(new int(88));
  if(pi!=nullptr)
  {
    std::cout<<"value of pi: "<<*pi<<std::endl;
  }
  pi.reset();
  if(pi==nullptr)
  {
    std::cout<<"pi is reset."<<std::endl;
  }
  
  //b) reset()带参数（一般是一个new出来的指针）时
  //若pi是唯一指向该对象的指针，则释放pi所指向的对象，让pi指向新对象
  //若pi不是唯一指向该对象的指针，则不释放pi指向的对象，但指向该对象的引用计数会减少1
  //同时让pi指向新对象。
  
  //2.4 *,解引用
  //2.5get() 考虑到有些函数的参数需要的是一个内置裸指针，而不是智能指针
  //p.get():返回p中保存的指针（裸指针），小心使用，如果智能指针释放了所指向的对象，那么这个返回的裸指针也就无效了
  std::shared_ptr<int> getp(new int(678));
  std::cout<<"getp value: "<<*getp<<std::endl;
  int *p=getp.get();
  *p = 786;
  std::cout<<"getp value after: "<<*getp<<std::endl;
  
  //swap
  std::shared_ptr<std::string> ps1(new std::string("ps1"));
  std::shared_ptr<std::string> ps2(new std::string("ps2"));
  std::cout<<"ps1 value: "<<*ps1<<", ps2 value: "<<*ps2<<std::endl;
  std::swap(ps1,ps2);
  std::cout<<"after swap1, ps1 value: "<<*ps1<<", ps2 value: "<<*ps2<<std::endl;
  ps1.swap(ps2);
  std::cout<<"after swap2, ps1 value: "<<*ps1<<", ps2 value: "<<*ps2<<std::endl;
  //2.7 =nullptr
  //a. 将所指向的对象 引用计数减去1， 若引用计数变为0， 则释放智能指针所指向的对象
  //b. 将智能指针置空
  std::shared_ptr<int> nptr(new int(99));
  nptr=nullptr;
  //2.8智能指针作为一个判断条件
  nptr.reset(new int(34));
  if(nullptr!=nptr)
  {
    std::cout<<"nptr pointer one obj."<<std::endl;
  }else
  {
    std::cout<<"nptr don't pointer any obj."<<std::endl;
  }
  nptr.reset();
  if(nullptr!=nptr)
  {
    std::cout<<"nptr pointer one obj."<<std::endl;
  }else
  {
    std::cout<<"nptr don't pointer any obj."<<std::endl;
  }
  
  //2.9 自定义删除qi
  std::shared_ptr<int> mdelete_ptr(new int(76),myDelete);
  mdelete_ptr.reset();
  //也可以用lambda函数
  std::shared_ptr<int> mlambda_delete_ptr(new int(45),[](int* p){std::cout<<"launch lambda delete func."<<std::endl;delete p;});
  
  //有些情况，默认删除qi解决不了（用shared_ptr管理动态数组），需要我们提供自己制定的删除qi,
  std::shared_ptr<int> sarray_p(new int[10],[](int*p){delete []p;});
  
  //可用default_delete来做删除qi,default_delete是标准库里的模板类
  //std::shared_ptr<A> pA(new A[10],std::default_delete<A[]>());
  std::shared_ptr<int> pint(new int[10],std::default_delete<int[]>());
  for(int i=0;i<10;++i)
  {
    pint.get()[i]=i*i;
  }
  for(int i=0;i<10;++i)
  {
    std::cout<<"pint["<<i<<"]: "<<pint.get()[i]<<std::endl;
  }
  
  std::shared_ptr<int> pint2(make_shared_ptr_array<int>(10));
  for(int i=0;i<10;++i)
  {
    pint2.get()[i]=(i+1)*(i+1);
  }
  for(int i=0;i<10;++i)
  {
    std::cout<<"pint2["<<i<<"]: "<<pint2.get()[i]<<std::endl;
  }
  
  //pint.get()[0]=1;
  //std::shared_ptr<A[]> pA(new A[10]);
  //????
  //b 制定删除其额外说明
  //就算是两个shared_ptr制定了不同的删除其，只要他们所指向的对象类型相同，那么这两个shared_ptr也属于同一个类型
  auto lambda1=[](int* p)
  {
    std::cout<<"lambda 1 delete."<<std::endl;delete p;
  };
  auto lambda2=[](int* p)
  {
    std::cout<<"lambda 2 delete."<<std::endl;delete p;
  };
  
  std::shared_ptr<int> psl1(new int(100),lambda1);
  std::shared_ptr<int> psl2(new int(200),lambda2);
  
  psl2=psl1;
  std::cout<<"-------------------------"<<std::endl;
  
  //类型相同，就代表可以放到元素类型为该对象类型的容器里来
  std::vector<std::shared_ptr<int>> pvec{psl1,psl2};
  //make_shared是提倡的生成shared_ptr的方法，但是make_shared这种方法，让我们没办法制定自己的删除其
  return 0;
}
