#include <iostream>
#include <thread>
#include <list>
#include <deque>
#include <mutex>
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