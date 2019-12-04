#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	bool prima = 0;
	bool adoua = 1;
	int aux = 0;
	int nr = 0;
	for (int i = 172930; i <= 683082; i++)
	{
		prima = 0;
		adoua = 1;
		aux = i;

		while (i > 9)
		{
			if (i % 10 == i / 10 % 10)
			{
				prima = true;
			}
			if (i % 10 < i / 10 % 10)
			{
				adoua = false;
			}
			i = i / 10;
		}
		if (prima && adoua)
		{
			nr++;
		}
		i = aux;
	}

	out << nr;

	in.close();
	out.close();
}