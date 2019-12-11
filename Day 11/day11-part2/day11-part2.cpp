#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	bool operator<(const Coordinate& c) const
	{
		return this->x < c.x ? true : this->x == c.x ? this->y < this->x : false;
	}

	bool operator==(const Coordinate& c) const
	{
		return ((this->x == c.x) && (this->y == c.y));
	}

public:
	int x, y;
};


void readInput(std::fstream& in, std::vector<long long>& integers)
{
	long long number = 0;
	char aux{};
	int it = 0;

	while (in >> number)
	{
		integers[it++] = number;
		in >> aux;
	}
}


void writeOutput(std::fstream& out, const std::vector<std::vector<bool>>& map, int nLines, int nColumns)
{
	int saveX = 0, saveY = 0;

	for (int l = 0; l < nLines; l++)
	{
		for (int c = 0; c < nColumns; c++)
		{
			if (map[l][c] == 1)
			{
				saveX = l;	saveY = c;
				l = c = 200;
			}
		}
	}

	for (int l = saveX; l < nLines; l++)
	{
		for (int c = saveY; c < nColumns; c++)
		{
			if (map[l][c] == 1)
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


void setPosModes(const std::vector<long long>& integers, long long currPos, long long relativeBase, long long& posMode1, long long& posMode2, long long& posMode3)
{
	switch (integers[currPos] / 100 % 10)
	{
	case 0:
		if (currPos + 1 < integers.size())
		{
			posMode1 = integers[currPos + 1];
		}
		break;

	case 1:
		posMode1 = currPos + 1;
		break;

	case 2:
		if (currPos + 1 < integers.size())
		{
			posMode1 = relativeBase + integers[currPos + 1];
		}
		break;
	}

	switch (integers[currPos] / 1000 % 10)
	{
	case 0:
		if (currPos + 2 < integers.size())
		{
			posMode2 = integers[currPos + 2];
		}
		break;

	case 1:
		posMode2 = currPos + 2;
		break;

	case 2:
		if (currPos + 2 < integers.size())
		{
			posMode2 = relativeBase + integers[currPos + 2];
		}
		break;
	}

	switch (integers[currPos] / 10000 % 10)
	{
	case 0:
		if (currPos + 3 < integers.size())
		{
			posMode3 = integers[currPos + 3];
		}
		break;

	case 1:
		posMode3 = currPos + 3;
		break;

	case 2:
		if (currPos + 3 < integers.size())
		{
			posMode3 = relativeBase + integers[currPos + 3];
		}
		break;
	}
}


void intCodeProgram(std::fstream& out, std::vector<long long>& integers, int input)
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
	map[rx][ry] = '#';

	while (integers[currPos] != 99)
	{
		setPosModes(integers, currPos, relativeBase, posMode1, posMode2, posMode3);

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
			integers[posMode1] = map[rx][ry];
			currPos = currPos + 2;
			break;

		case 4:
			// std::cout << integers[posMode1];
			if (first)
			{
				map[rx][ry] = integers[posMode1];
				visit[rx][ry] = 1;
				first = false;
			}
			else
			{
				posDir = (integers[posMode1] == 0) ? (posDir - 1 + 4) % 4 : (posDir + 1 + 4) % 4;

				if (posDir == 0) ry++;
				else if (posDir == 1) rx++;
				else if (posDir == 2) ry--;
				else if (posDir == 3) rx--;
				
				first = true;
			}

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
	std::vector<long long> integers(100000000);
	int input = 1;

	readInput(in, integers);
	intCodeProgram(out, integers, input);

	in.close();
	out.close();
}