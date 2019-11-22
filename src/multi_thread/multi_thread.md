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
起一个标记作用,要使用这个标记，前提是必须先lock
std::chrono::milliseconds dura(20000);
std::this_thread::sleep_for(dura);

unique_lock比lock_guard更灵活，但也更消耗内存
2.1 std::adopt_lock
2.2 std::try_to_lock
我们会尝试用mutex的lock()去锁定这个mutex,但是如果没有锁定成功，我也会立即返回
并不会阻塞在那里，用这个try_to_lock的前提是自己不能先去lock.
std::unique_lock<std::mutex> sbguard(my_mutex,std::try_to_lock);
if(sbguard.owns_lock())
{
	
}else
{
	
}

2.3 std::defer_lock
//用这个defer_lock的前提是你不能自己先去lock,否则会报告异常
//defer_lock的意思就是并没有给mutex加锁，初始化了一个没有加锁的mutex
std::unique_lock<std::mutex> sbguard(my_mutex,std::defer_lock);
sbguard1.lock();//不用自己调用unlock()

sbguard1.unlock();
//处理一些非共享代码

sbguard1.lock();
//处理共享代码


三 unique_lock的成员函数
1.lock()
2. unlock()锁住之后中间有一些非共享代码要处理，所以需要中途unlock一下
3.try_lock(),尝试给互斥量加锁，如果拿不到锁，则返回false,如果拿到了锁，返回
true，这个函数不阻塞

std::unique_lock<std::mutex> sbguard(my_mutex,std::defer_lock);

if(sbguard.try_lock()==true)
{
	
}else
{
	
}

3.4 release() 返回它所管理的mutex对象指针，并释放所有权，也就是说
这个unique_lock指针和mutex不再有关系，该自己unlock的就要自己unlock
严格区分unlock和release的区别，不要混淆
如果mutex对象处于加锁状态，你有责任接管过来并负责解锁

std::unique_lock<std::mutex> sbguard(my_mutex);
std::mutex *px=suguard.release();//现在你有责任去解锁这个my_mutex


4.unique_lock的所有权的传递mutex
std::unique_lock<std::mutex> sbguard1(my_mutex);
sbguard拥有my_mutex的所有权
sbguard可以把自己最my_mutex的所有权转移给其他的unique_lock对象
所以unique_lock对象这个mutex的所有权属于可以转移，但是不能复制
std::unique_lock<std::mutex> sbguard2(std::move(sbguard1));
或者也可以从函数中return 临时局部对象









































































