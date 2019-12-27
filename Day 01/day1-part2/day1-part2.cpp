#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int number = 0;
	long long sum = 0;

	while (in >> number)
	{
		while ((number = number / 3 - 2) > 0)
		{
			sum = sum + number;
		}
	}

	out << sum;

	in.close();
	out.close();
}