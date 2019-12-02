#include "../../AOCHeaders/stdafx.h"
#include "../../AOCHeaders/AOC.h"


void readInput(std::fstream& in, std::vector<int>& v)
{
	int nr = 0;
	char aux;

	while (in >> nr >> aux)
	{
		v.push_back(nr);
	}

	in >> nr;
	v.push_back(nr);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> v;

	readInput(in, v);
	std::vector<int> aux(v);

	for (int pos1 = 0; pos1 < 100; pos1++)
	{
		for (int pos2 = 0; pos2 < 100; pos2++)
		{
			v = aux;
			v[1] = pos1;
			v[2] = pos2;

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
				out << pos1 * 100 + pos2;
				pos1 = 100;
				pos2 = 100;
			}
		}
	}

	in.close();
	out.close();
}