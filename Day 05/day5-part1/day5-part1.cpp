#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<int>& integers)
{
	int number = 0;
	char aux{};

	while (in >> number)
	{
		integers.push_back(number);
		in >> aux;
	}
}


void intCodeProgram(std::fstream& out, std::vector<int>& integers)
{
	int currPos = 0;
	int posMode1 = 0;
	int posMode2 = 0;
	int posMode3 = 0;

	while (integers[currPos] != 99)
	{
		posMode1 = (integers[currPos] / 100 % 10 == 1) ? currPos + 1 : (currPos + 1 < integers.size()) ? integers[currPos + 1] : posMode1;
		posMode2 = (integers[currPos] / 1000 % 10 == 1) ? currPos + 2 : (currPos + 2 < integers.size()) ? integers[currPos + 2] : posMode2;
		posMode3 = (integers[currPos] / 10000 % 10 == 1) ? currPos + 3 : (currPos + 3 < integers.size()) ? integers[currPos + 3] : posMode3;

		switch (integers[currPos] % 100)
		{
		case 1:
			integers[posMode3] = integers[posMode2] + integers[posMode1];
			currPos = currPos + 4;
			break;

		case 2:
			integers[posMode3] = integers[posMode2] * integers[posMode1];
			currPos = currPos + 4;
			break;

		case 3:
			integers[posMode1] = 1;
			currPos = currPos + 2;
			break;

		case 4:
			if (integers[posMode1] != 0)
			{
				out << integers[posMode1];
			}
			currPos = currPos + 2;
			break;
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> integers;

	readInput(in, integers);
	intCodeProgram(out, integers);

	in.close();
	out.close();
}