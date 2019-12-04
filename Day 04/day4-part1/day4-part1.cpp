#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	bool firstRule = false;
	bool secondRule = true;
	int aux = 0;
	int nr = 0;
	for (int i = 172930; i <= 683082; i++)
	{
		firstRule = false;
		secondRule = true;
		aux = i;

		while (i > 9)
		{
			if (i % 10 == i / 10 % 10)
			{
				firstRule = true;
			}
			if (i % 10 < i / 10 % 10)
			{
				secondRule = false;
			}
			i = i / 10;
		}
		if (firstRule && secondRule)
		{
			nr++;
		}
		i = aux;
	}

	out << nr;

	in.close();
	out.close();
}
