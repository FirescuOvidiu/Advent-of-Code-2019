#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::fstream& out)
{
	std::vector<int> countsPos(3, 0);
	int pixelsWide = 25, pixelsTall = 6, lengthLayout = pixelsWide * pixelsTall;
	int minZeros = pixelsWide * pixelsTall + 1, multiplication = 0;
	char pixel{};


	while (!in.eof())
	{
		for (int it = 1; it <= lengthLayout; it++)
		{
			in >> pixel;
			countsPos[pixel - '0']++;
		}
		
		if (countsPos[0] < minZeros)
		{
			minZeros = countsPos[0];
			multiplication = countsPos[1] * countsPos[2];
		}

		std::fill(countsPos.begin(), countsPos.end(), 0);
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