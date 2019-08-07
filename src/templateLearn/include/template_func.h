#include <cstring>
template <typename  T>
T funcAdd(T a, T b)
{
    T c = a+b;
    return c;
}

template <int a, int b>
int funcAdd2()
{
    int c = a+b;
    return c;
}

template <typename T, int a, int b>
int funcAdd3(T c)
{
    return a+b+c;
}

template<unsigned L1, unsigned L2>
int charsComp(const char(&p1)[L1], const char(&p2)[L2])
{
    return std::strcmp(p1,p2);
}


template<typename T, int size = 10>
class myarray
{
public:
   // myarray();
    void myarrayfunc();
};

template<typename T, int size>
void myarray<T,size>::myarrayfunc()
{
    std::cout<<"size: "<<size<<std::endl;
    return;
}

template<typename T>
class myvector
{
public:
    typedef T* myiterator;
public:
    myvector();
    myvector& operator=(const myvector& );
public:
    myiterator mybegin();
    myiterator myend();

};
template <typename T>
myvector<T>::myvector()
{
  
}

