#include "../../AOCHeaders/stdafx.h"
#include "../../AOCHeaders/AOC.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	int n = 0;
	long long sum = 0;

	while (in >> n)
	{
		sum = sum + std::round(n / 3) - 2;
	}

	out << sum;

	in.close();
	out.close();
}