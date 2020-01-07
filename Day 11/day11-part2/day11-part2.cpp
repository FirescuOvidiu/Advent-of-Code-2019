#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<long long>& integers)
{
	long long number = 0;
	char aux{};

	while (in >> number)
	{
		integers.push_back(number);
		in >> aux;
	}
}


void writeOutput(std::fstream& out, const std::vector<std::vector<bool>>& map, int nLines, int nColumns)
{
	int minX = nLines, minY = nColumns, maxX = 0, maxY = 0;

	for (int l = 0; l < nLines; l++)
	{
		for (int c = 0; c < nColumns; c++)
		{
			if (map[l][c])
			{
				if (l < minX)	minX = l;
				if (l > maxX)	maxX = l;
				if (c < minY)	minY = c;
				if (c > maxY)	maxY = c;
			}
		}
	}

	for (int l = minX; l <= maxX; l++)
	{
		for (int c = minY; c <= maxY; c++)
		{
			if (map[l][c])
			{
				out << "# ";
			}
			else
			{
				out << "  ";
			}
		}
		out << "\n";
	}
}


void setPosModes(std::vector<long long>& integers, long long currPos, long long relativeBase, long long& posMode1, long long& posMode2, long long& posMode3, long long opcode)
{
	if (currPos + 3 >= integers.size())
	{
		integers.resize(currPos + 4);
	}

	switch (integers[currPos] / 100 % 10)
	{
	case 0:
		posMode1 = integers[currPos + 1];
		break;

	case 1:
		posMode1 = currPos + 1;
		break;

	case 2:
		posMode1 = relativeBase + integers[currPos + 1];
		break;
	}

	switch (integers[currPos] / 1000 % 10)
	{
	case 0:
		posMode2 = integers[currPos + 2];
		break;

	case 1:
		posMode2 = currPos + 2;
		break;

	case 2:
		posMode2 = relativeBase + integers[currPos + 2];
		break;
	}

	switch (integers[currPos] / 10000 % 10)
	{
	case 0:
		posMode3 = integers[currPos + 3];
		break;

	case 1:
		posMode3 = currPos + 3;
		break;

	case 2:
		posMode3 = relativeBase + integers[currPos + 3];
		break;
	}

	if (posMode1 >= integers.size())
	{
		integers.resize(posMode1 + 1);
	}

	if (posMode2 >= integers.size() &&
		((opcode == 1) || (opcode == 2) || (opcode == 5) || (opcode == 6) || (opcode == 7) || (opcode == 8)))
	{
		integers.resize(posMode2 + 1);
	}

	if ((posMode3 >= integers.size()) &&
		((opcode == 1) || (opcode == 2) || (opcode == 7) || (opcode == 8)))
	{
		integers.resize(posMode3 + 1);
	}
}


void intCodeProgram(std::fstream& out, std::vector<long long>& integers, bool input)
{
	long long currPos = 0;
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;
	long long relativeBase = 0;

	int nLines = 200, nColumns = 200;
	std::vector<std::vector<bool>> visit(nLines, std::vector<bool>(nColumns));
	std::vector<std::vector<bool>> map(nLines, std::vector<bool>(nColumns));
	std::vector<char> dir{ '>' ,'v', '<' ,'^' };
	int posDir = 3;

	int rx = nLines / 2, ry = nColumns / 2;
	bool first = true;
	map[rx][ry] = true;

	while (integers[currPos] != 99)
	{
		setPosModes(integers, currPos, relativeBase, posMode1, posMode2, posMode3, integers[currPos] % 100);

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
			input = map[rx][ry];
			integers[posMode1] = input;
			currPos = currPos + 2;
			break;

		case 4:
			// std::cout << integers[posMode1] << " ";
			if (first)
			{
				map[rx][ry] = integers[posMode1];
				visit[rx][ry] = true;
			}
			else
			{
				posDir = (integers[posMode1] == 0) ? (posDir + 3) % 4 : (posDir + 1) % 4;

				if (posDir == 0) ry++;
				else if (posDir == 1) rx++;
				else if (posDir == 2) ry--;
				else if (posDir == 3) rx--;
			}

			first = !first;
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

		case 9:
			relativeBase += integers[posMode1];
			currPos = currPos + 2;
			break;
		}
	}

	writeOutput(out, map, nLines, nColumns);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<long long> integers;
	bool input = true;

	readInput(in, integers);
	intCodeProgram(out, integers, input);

	in.close();
	out.close();
}