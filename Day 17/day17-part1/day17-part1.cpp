#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

public:
	int x, y;
};


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


void intCodeProgram(std::fstream& out, std::vector<long long>& integers, const long long input,
	std::vector<std::vector<char>>& map)
{
	std::vector<char> line;
	long long currPos = 0;
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;
	long long relativeBase = 0;

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
			integers[posMode1] = input;
			currPos = currPos + 2;
			break;

		case 4:
			//out << integers[posMode1] << " ";
			switch (integers[posMode1])
			{
			case 10:
				map.push_back(line);
				line.clear();
				break;

			default:
				line.push_back((char)integers[posMode1]);
				break;
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
}


bool checkInMap(int x, int y, int lines, int columns)
{
	return x >= 0 && y >= 0 && x < lines && y < columns;
}

int findSumScaffoldIntersections(const std::vector<std::vector<char>>& map)
{
	int lines = map.size() - 1, columns = map[0].size();
	std::vector<std::vector<int>> visit(lines, std::vector<int>(columns, 0));
	int dirX[] = { -1,0,0,1 };
	int dirY[] = { 0,-1,1,0 };
	Coordinate robot(0, 0);

	for (int l = 0; l < lines; l++)
	{
		for (int c = 0; c < columns; c++)
		{
			if ((map[l][c] != '.') && (map[l][c] != '#'))
			{
				robot.x = l;  robot.y = c;
				l = lines;	c = columns;
			}
		}
	}

	for (int l = 0; l < lines; l++)
	{
		for (int c = 0; c < columns; c++)
		{
			std::cout << map[l][c];
		}
		std::cout << "\n";
	}

	int sum = 0;
	bool finish = false;

	while (!finish)
	{

		finish = true;
		for (int i = 0; i < 4; i++)
		{
			if (checkInMap(robot.x + dirX[i], robot.y + dirY[i], lines, columns) &&
				(map[dirX[i] + robot.x][dirY[i] + robot.y] == '#') && (!visit[dirX[i] + robot.x][dirY[i] + robot.y]))
			{
				while (checkInMap(robot.x + dirX[i], robot.y + dirY[i], lines, columns) &&
					(map[robot.x + dirX[i]][robot.y + dirY[i]] == '#'))
				{
					robot.x += dirX[i];
					robot.y += dirY[i];
					if (visit[robot.x][robot.y])
					{
						sum += robot.x * robot.y;
					}
					else
					{
						visit[robot.x][robot.y] = true;
					}
				}
				finish = false;
				break;
			}
		}
	}

	return sum;
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;
	std::vector<long long> integers;
	long long input = 1;

	readInput(in, integers);
	intCodeProgram(out, integers, input, map);

	out << findSumScaffoldIntersections(map);

	in.close();
	out.close();
}