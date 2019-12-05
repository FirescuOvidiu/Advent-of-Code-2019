#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<int>& v)
{
	int number = 0;
	char aux{};

	while (in >> number)
	{
		v.push_back(number);
		in >> aux;
	}
}


void intCodeProgram(std::fstream& out, std::vector<int>& integers)
{
	int currPos = 0;
	int posMode1 = 0;
	int posMode2 = 0;
	int posMode3 =0;

	while(integers[currPos] != 99)
	{
		posMode1 = (integers[currPos] / 100 % 10 == 1) ? currPos + 1 : integers[currPos + 1];
		posMode2 = (integers[currPos] / 1000 % 10 == 1) ? currPos +2 : integers[currPos + 2];
		posMode3 = (integers[currPos] / 10000 % 10 == 1) ? currPos + 3 : integers[currPos + 3];

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
			integers[integers[currPos+1]] = 5;
			currPos = currPos + 2;
			break;

		case 4:
			out << integers[integers[currPos + 1]];
			currPos = currPos + 2;
			break;

		case 5:
			currPos = integers[posMode1] != 0 ? integers[posMode2] : currPos + 3;
			break;

		case 6:
			currPos = integers[posMode1] == 0 ? integers[posMode2] : currPos + 3;
			break;

		case 7:
			integers[posMode3] = integers[posMode1] < integers[posMode2];
			currPos = currPos + 4;
			break;

		case 8:
			integers[posMode3] = integers[posMode1] == integers[posMode2];
			currPos = currPos + 4;
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