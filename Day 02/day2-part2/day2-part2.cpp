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


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> v;

	readInput(in, v);
	std::vector<int> aux(v);

	for (int noun = 0; noun < 100; noun++)
	{
		for (int verb = 0; verb < 100; verb++)
		{
			v = aux;
			v[1] = noun;
			v[2] = verb;

			for (int currPos = 0; v[currPos] != 99; currPos += 4)
			{
				switch ((v[currPos]))
				{
				case 1:
					v[v[currPos + 3]] = v[v[currPos + 1]] + v[v[currPos + 2]];
					break;
				case 2:
					v[v[currPos + 3]] = v[v[currPos + 1]] * v[v[currPos + 2]];
					break;
				}
			}

			if (v[0] == 19690720)
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