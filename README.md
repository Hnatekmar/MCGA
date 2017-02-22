What is MCGA?
=============
MCGA aims to provide Java/C# like stream capabilities into C++. Here is short example of library in action:


```c++
#include "MCGA.h"
#include <vector>
int main()
{
	std::vector<size_t> numbers;
	for(size_t i = 0; i < 100; i++)
	{
		numbers.push_back(i);
	}
	auto n = mcga::stream(numbers.begin(), numbers.end()).map([](size_t x) { return x + 4; }).map([](size_t x) { return x * 504; }).sum();
	return 0;
}
```
