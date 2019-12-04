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


int IntCodeProgram(std::vector<int> integers)
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

	return integers[0];
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> integers;

	readInput(in, integers);

	for (int noun = 0; noun < 100; noun++)
	{
		for (int verb = 0; verb < 100; verb++)
		{
			integers[1] = noun;
			integers[2] = verb;

			if (IntCodeProgram(integers) == 19690720)
			{
				out << noun * 100 + verb;
				noun = 100;
				verb = 100;
			}
		}
	}

	in.close();
	out.close();
}