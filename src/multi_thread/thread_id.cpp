#include <thread>
#include <iostream>
void my_print()
{
    std::cout<<"my_print id: "<<std::this_thread::get_id()<<std::endl;
}
int main()
{
    std::thread print_thread(my_print);
    std::cout<<"main thread id: "<<std::this_thread::get_id()<<std::endl;
    print_thread.join();
    return 0;
}
