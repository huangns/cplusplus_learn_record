#include <iostream>
#include <vector>
#include <thread>
void myPrint(int i)
{
    std::cout<<"thread id: "<<std::this_thread::get_id()<<std::endl;
    std::cout<<"parameter i: "<<i<<std::endl;
    std::cout<<"thread over."<<std::endl;
    return;
}
int main()
{
    std::vector<std::thread> thread_vec;
    for(int i=0;i<10;++i)
    {
        thread_vec.push_back(std::thread(myPrint,i));
    }
    for(auto it=thread_vec.begin();it!=thread_vec.end();++it)
    {
        it->join();
    }
    std::cout<<"wait all thread over."<<std::endl;
    return 0;
}
