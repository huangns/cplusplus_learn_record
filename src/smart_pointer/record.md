1.new delete 具备对堆上所分配内存进行初始化/释放（反初始化）的能力，而这些能力是malloc/free所不具备的（即构造+析构）。
2. new+delete VS new()+delete()
new+delete是运算符，不是个函数，而new()+delete()是函数， operator new(), operator delete()
int* pi = new int;
delete pi;
new 干了两件事： a)分配内存(通过operator new 来分配内存) b)调用构造函数来初始化内存 
delete干了两件事： a)先调用析构函数 b)释放内存(调用operator delete())，和 new反着来
3. new 内部有记录机制，记录了分配出去多少内存，在删除的时候，编译器知道怎么回收内存。
