(1) C++ 标准库： c++ standard library,只要装了C++编译器，那么这个C++标准库就自动地被安装进来了。
(2) 标准模板库： standard template library.包含于c++标准库之中，作为c++标准库中的一个重要组成部分或者说是c++的核心。
(3) 泛型编程： generic program,使用模板template为主要的编程手段来编写代码。
可以认为，标准模板库，就是用泛型编程的编码方式写的一套供我们非常方便使用的一套库。

STL的组成部分：
a) 容器： vector, list, map
b) 迭代器：用于遍历或者访问容器中的一些元素
c) 算法：(函数)，用来实现一些功能，search sort copy ...
d) 分配器(内存分配器) 

2.1 array:顺序容器，其实是个数组，内存空间连续，大小固定，开始申请是多大，他就是多大。
2.2 容器里面有多少个元素可以用size()查看，而这个容器有多少空间，可以用capacity()查看。vector里面的元素的地址是连续的，但是第一个元素的地址和vector对象的地址，并不是相等的，如&vector_obj[0] 不一定等于 &vector_obj，通常是不相等的。
2.3 deque 和 stack 顺序容器
deque: 双端队列double-ended-queue 双向开口，相当于动态数组：头部和尾部插入与删除数据都很快，如果往中间插入元素，那么可能会涉及到移动其他元素，效率上会比较低。
分段连续内存
push_front push_back
2.4 stack: 后进先出，只有一个开口，只要把deque左边开口封死，就可以认为是一个stack.和vector的区别：vector支持从中间插入中间删除，虽然效率不算高，但是stack只支持从栈顶放入元素以及从栈顶取出(删除)元素，这种特性是stack容器的设计初衷。
deque实际上是包含stack功能。
2.5 queue:队列，这是个普通队列，先进先出


3.1 map:每个元素有两项，是 key/value
//不允许key相同，要相同需要用multimap
map<int,string> mymap;
mymap.insert(std::make_pair(1,"str1"));
mymap.insert(std::make_pair(2,"str2"));
mymap.insert(std::make_pair(3,"str3"));
mymap.insert(std::make_pair(3,"str4"));//虽然能运行，但是无法插入，
auto iter = mymap.find(3);
if(iter!=mymap.end())
{
    std::cout<<mymap.first<<" , "<<mymap.second<<std::endl;
}

set:不存在键值对的说法：每个元素就是一个value:元素值不能重复，如果想重复，可以采用multiset.
//关联容器总结
1.内部实现的数据结构多为红黑树
2.插入的时候，因为容器要给你一个适当的插入位置，所以插入的速度可能会慢一点
3.查找的速度特别快
4.如果需要快速找到某个元素的时候，重点就要考虑使用map,set,multimap,multiset

4.哈希表类容器
unordered_set, unordered_multiset , unordered_map, unordered_multimap
增加bucket数量的目的是为了防止某个篮子后边挂的元素太多，从而影响查找速度
自动指定元素位置，不需要使用手工干预

void func()
{
    unordered_set<int> myset;
    cout<<"bucket_count() = "<<myset.bucket_count()<<std::endl;
    for(int i=0;i<8;++i)
    {
        myset.insert(i);
    }
    cout<<"bucket_count(): "<<myset.bucket_count()<<std::endl;
    myset.insert(8);

    cout<<"bucket_count(): "<<myset.bucket_count()<<std::endl;
    cout<<"max_bucket_count(): "<<myset.max_bucket_count() <<std::endl;
    
    std::cout<<"元素数量： "<<myset.size()<<std::endl;
    for(int i=0;i<myset.bucket_count();++i)
    {
        std::cout<<"elem size for bucket "<<i<< " is "<<myset.bucket_size(i)<<std::endl;
    }

    auto iter_find = myset.find(5);
    if(iter_find!=myset.end())
    {
        cout<<"elem 5 is in the set."<<std::endl;
    }

    if(find(myset.begin(), myset.end(),5)!=myset.end())
    {
        cout<<"elem 5 is in the set."<<std::endl;
    }
    
}
