#include "../../AOCHeaders/stdafx.h"
#include "../../AOCHeaders/AOC.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int number = 0;
	long long sum = 0;

	while (in >> number)
	{
		if (number >= 3)
		{
			number = number / 3 - 2;

			while (number >= 3)
			{
				sum = sum + number;
				number = number / 3 - 2;
			}
		}

		if (number >= 0)
		{
			sum = sum + number;
		}
	}

	out << sum;

	in.close();
	out.close();
}