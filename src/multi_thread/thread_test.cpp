#include <iostream>
#include <thread>
#include <list>
#include <deque>
#include <mutex>
#include <condition_variable>
#define CONDITION_TEST
/*
void thread_test()
{
  std::cout<<"child thread id: "<<std::this_thread::get_id()<<std::endl;
}

class push_pop
{
public:
  push_pop(int c):count(c){}
  ~push_pop(){}
  void pushOperation()
  {
    for(int i=0;i<count;++i)
    {
      std::cout<<"push back data: "<<i<<std::endl;
      data.push_back(i);
    }
  }
  void popOperation()
  {
    //for(int i=0;i<count;++i)
    
    while(true)
    {
      if(data.size())
      {
	std::cout<<"push front data: "<<data.front()<<std::endl;
	data.pop_front();
      }
    }
  }
private:
  int count;
  std::deque<int> data;
  std::mutex data_mutex;
};
int main()
{
  std::cout<<"multi thread learn."<<std::endl;
  push_pop push_pop_obj(100000);
  std::thread push_thread(&push_pop::pushOperation,&push_pop_obj);
  std::thread pop_thread(&push_pop::popOperation,&push_pop_obj);
  push_thread.join();
  pop_thread.join();
  //std::thread thread_obj(thread_test);
  //thread_obj.join();
  return 0;
}
*/


//2019.1124 condition_variable, wait(), notify_one(), notify_all
class in_out_system
{
public:
  in_out_system():
  new_str(false)
  {
    
  }
  ~in_out_system(){}
  void in_msg()
  {
    while(true)
    {
      static int count=0;
      std::unique_lock<std::mutex> guard_in(my_mutex);
      msg=std::string("this is my ")+std::to_string(count++)+std::string(" msg.");
      new_str=true;
      //如果执行wait()的线程正在处理其他事务，而需要一段时间，而不是正卡在wait()那里等待唤醒，那么此时notify_one这个线程就无效了
      //或者如果这个线程notify_one()之后又拿到了锁，那么另一个线程可能还得继续阻塞，等这个线层加入多个数据之后才能取出一个数据
      my_condition.notify_one();
      //std::cout<<"publish msg: "<<msg<<std::endl;
      
    }
  }

#ifndef CONDITION_TEST
  void out_msg()
  {
    while(true)
    {
      std::unique_lock<std::mutex> guard_out(my_mutex);
      if(new_str)
      {
	std::cout<<"receive: "<<msg<<std::endl;
	new_str=false;
      }else
      {
	std::cout<<"receive none!"<<std::endl;
      }
    }
  }
#else
//wait()用来等待一个东西
//如果第二个参数lambda表达式是true,那么wait()直接返回
//如果第二个参数lambda表达式返回值是false,那么wait()将解锁互斥量，并堵塞到本行
//堵塞到其他某个线程调用notify_one()成员函数为止
//如果wait()没有第二个参数，my_condition(guard_out),那么就跟第二个参数lambda表达式返回false效果一样
//wait将解锁互斥量，并堵塞到本行，堵塞到其他某个线程调用notify_one（）成员函数为止
//wait被唤醒之后的操作：
//a) wait()会不断地尝试获取互斥量锁，如果获取不到，那么流程就会卡在wait这里等着获取，如果获取到了锁，那么wait就接着往下
//b)1.如果wait有第二个参数（如lambda表达式），如果表达式为false，那么wait又对互斥量解锁，继续堵塞等待被唤醒
//  2.如果lambda表达式为true，那么wait返回，流程走下去
//  3.如果wait没有第二个参数，那么流程走下来



  void out_msg()
  {
    while(true)
    {
      std::unique_lock<std::mutex> guard_out(my_mutex);
      //前提是得拿到锁之后才能执行wait操作
      my_condition.wait(guard_out,[this]
      {
	return new_str;
      }
      );
      //流程能走到这里，互斥锁一定是锁着的
      std::cout<<"receive: "<<msg<<std::endl;
      new_str=false;
    }
  }
#endif
private:
  std::mutex my_mutex;
  std::condition_variable my_condition;
  std::string msg;
  bool new_str;
};
 
int main()
{
  /*
  in_out_system in_out_system_obj;
  std::thread in_thread(&in_out_system::in_msg,&in_out_system_obj);
  std::thread out_thread(&in_out_system::out_msg,&in_out_system_obj);
  in_thread.join();
  out_thread.join();
  return 0;
  */
  //一：：std::async,std::future 创建后台任务并返回值
  //希望线程返回一个结果
  //std::async 是个函数模板，用来启动一个异步任务，启动起来一个异步任务之后，就返回一个std::future对象，std::future是个类模板
  //什么叫启动一个异步任务，就是自动创建一个线程并开始执行对应的线程入口函数，它返回一个std::future对象
  return 0;
}