#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::fstream& out)
{
	int pixelsWide = 25, pixelsTall = 6;
	int countZeros = 0, minZeros = 2147483647;
	int countOne = 0, countTwo = 0;
	int multiplication = 0;
	char aux{};


	while (!in.eof())
	{
		countZeros = countOne = countTwo = 0;

		for (int i = 1; i <= pixelsWide * pixelsTall; i++)
		{
			in >> aux;
			switch (aux - '0')
			{
			case 0:
				countZeros++;
				break;

			case 1:
				countOne++;
				break;

			case 2:
				countTwo++;
				break;
			}
		}
		
		if (countZeros < minZeros)
		{
			minZeros = countZeros;
			multiplication = countOne * countTwo;
		}
	}
	out << multiplication;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	readInput(in, out);

	in.close();
	out.close();
}