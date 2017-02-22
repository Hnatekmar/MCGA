#include "MCGA.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> integers;
	for(size_t i = 0; i < 20; i++)
	{
		integers.push_back(i);
	}

	std::cout << "Pocet integeru je " << MCGA::Stream<std::vector<int>::iterator>(integers.begin(), integers.end()).size() << std::endl;
	auto mapStream = MCGA::Stream<std::vector<int>::iterator>(integers.begin(), integers.end()).map([](int x)
			{
				return x * x;
			}).map([](int x)
				{
					return x / 2;
				});

	mapStream.forEach([](int x)
			{
				std::cout << x << std::endl;
			});
	return 0;
}
