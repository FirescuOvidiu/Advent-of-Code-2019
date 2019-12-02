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
	v[1] = 12;
	v[2] = 2;

	for (int pos = 0; v[pos] != 99; pos += 4)
	{
		switch ((v[pos]))
		{
		case 1:
			v[v[pos + 3]] = v[v[pos + 1]] + v[v[pos + 2]];
			break;
		case 2:
			v[v[pos + 3]] = v[v[pos + 1]] * v[v[pos + 2]];
			break;
		}
	}

	out << v[0];

	in.close();
	out.close();
}