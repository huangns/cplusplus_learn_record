#include <iostream>
#include <vector>
#include <memory>

template <typename T>
using MYV=std::vector<T,std::allocator<T>>;
template<typename T, template<class> class Container>
class myclass
{
	public:
	T m_i;
	Container<T> myc;
	myclass()
	{
		for(int i=0;i<10;++i)
		{
			myc.push_back(i);
		}
	}
};


int main()
{
	myclass<int,MYV> myclassObj;
	return 0;
}
