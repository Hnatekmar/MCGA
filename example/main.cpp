#include "../src/MCGA.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> integers;
	for(size_t i = 0; i < 20; i++)
	{
		integers.push_back(i);
	}
	mcga::stream(integers.begin(), integers.end())
        .map<int>([](const int& x)
        {
            return x * x;
        })
        .forEach([](const int& x) -> void
        {
            std::cout << x << std::endl;
            return;
        });
	return 0;
}
