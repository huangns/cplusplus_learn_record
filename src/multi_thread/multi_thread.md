线程id: std::this_thread::get_id()
g++ thread_id.cpp -std=c++11 -lpthread// pthread不是linux下的默认的库  

lock_guard是一个类，其在构造函数中对传入的mutex执行了lock()操作
在析构的时候执行的unlock操作
死锁的一般解决方案
只要保证这两个互斥量上锁的顺序一致就不会死锁
std::lock() 函数模板：用来处理多个互斥量的时候才出场
能力：一次锁住两个或者两个以上的互斥量（至少两个，多了不限，一个不行）
它不存在这种因为在多个线程中，因为锁的顺序问题导致的死锁的风险问题
std::lock():如果互斥量中有一个没锁住，它就在那里等着，等所有的互斥量都锁住，它
才能往下走
要么两个互斥量都锁住，要么两个互斥量都没锁住，如果只锁定了其中一个，另外一个没锁成功，则它立即把已经锁住的解锁。


std::lock(my_mutex1,my_mutex2)
依旧要调用unlock函数
my_mutex1.unlock();
my_mutex2.unlock();

如果不想调用unlock，则可以用lock_guard
std::lock_guard<std::mutex> guard1(my_mutex1,std::adopt_lock);
std::lock_guard<std::mutex> guard2(my_mutex2,std::adopt_lock);
std::adopt_lock可以使得lock_guard对象在构造的时候，不去执行mutex.lock操作，是一个结构体对象，
起一个标记作用



























