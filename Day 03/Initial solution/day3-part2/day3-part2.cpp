#include "../../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	static int manhattanDistance(const Coordinate& c1, const Coordinate& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y);
	}

	bool operator==(const Coordinate& c)
	{
		return ((this->x == c.x) && (this->y == c.y));
	}

public:
	int x, y;
};



void readInput(std::fstream& in, std::list<Coordinate>& firstWireCoord)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'R':
			for (int i = 1; i <= number; i++)
			{
				currPos.y++;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y));
			}
			break;
		case 'L':
			for (int i = 1; i <= number; i++)
			{
				currPos.y--;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y));
			}
			break;
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				currPos.x--;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y));
			}
			break;
		case 'D':
			for (int i = 1; i <= number; i++)
			{
				currPos.x++;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y));
			}
		default:
			break;
		}
		in >> aux;
	}
}


void readInput2(std::fstream& in, std::list<Coordinate>& firstWireCoord, std::vector<Coordinate>& intersections)
{
	std::list<Coordinate>::iterator it = firstWireCoord.end();
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'R':
			for (int i = 1; i <= number; i++)
			{
				currPos.y++;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y));
				}
			}
			break;
		case 'L':
			for (int i = 1; i <= number; i++)
			{
				currPos.y--;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y));
				}
			}
			break;
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				currPos.x--;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y));
				}
			}
			break;
		case 'D':
			for (int i = 1; i <= number; i++)
			{
				currPos.x++;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y));
				}
			}
		default:
			break;
		}
		in >> aux;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream in2("input2.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Coordinate> intersections;
	std::list<Coordinate> firstWireCoord;

	readInput(in, firstWireCoord);
	readInput2(in2, firstWireCoord, intersections);

	intersections.erase(intersections.begin());

	int minDist = Coordinate::manhattanDistance(Coordinate(0, 0), (*(intersections.begin())));
	for (auto it = intersections.begin() + 1; it != intersections.end(); it++)
	{
		if (Coordinate::manhattanDistance(Coordinate(0, 0), (*it)) < minDist)
		{
			minDist = Coordinate::manhattanDistance(Coordinate(0, 0), (*it));
		}
	}

	out << minDist;

	in.close();
	out.close();
}