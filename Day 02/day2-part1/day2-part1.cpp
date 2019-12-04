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


void intCodeProgram(std::vector<int>& integers)
{
	for (int currPos = 0; integers[currPos] != 99; currPos += 4)
	{
		switch ((integers[currPos]))
		{
		case 1:
			integers[integers[currPos + 3]] = integers[integers[currPos + 1]] + integers[integers[currPos + 2]];
			break;
		case 2:
			integers[integers[currPos + 3]] = integers[integers[currPos + 1]] * integers[integers[currPos + 2]];
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
	integers[1] = 12;
	integers[2] = 2;

	intCodeProgram(integers);

	out << integers[0];

	in.close();
	out.close();
}