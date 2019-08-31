#include <iostream>
#include <memory>

void share_ptr_test_func(std::shared_ptr<int> spobj)
{
  std::cout<<"spobj value: "<<*spobj<<std::endl;
  std::cout<<"spobj ptr ref count: "<<spobj.use_count()<<std::endl;
}

std::shared_ptr<int> share_ptr_return_func(const std::shared_ptr<int>& spobj)
{
  return spobj;
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
  
  
  
  
  return 0;
}
