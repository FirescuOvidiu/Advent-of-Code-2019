#include "../../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	static int manhattanDistance(const Coordinate& c1, const Coordinate& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y);
	}

	bool operator<(const Coordinate& c) const
	{
		return this->x < c.x ? true : this->x == c.x ? this->y < c.y : false;
	}

public:
	int x, y;
};



// Saving every coordinate of the first path into a set
void readInput(std::fstream& in, std::set<Coordinate>& firstWireCoord)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				currPos.x--;
				firstWireCoord.insert(currPos);
			}
			break;

		case 'L':
			for (int i = 1; i <= number; i++)
			{
				currPos.y--;
				firstWireCoord.insert(currPos);
			}
			break;

		case 'R':
			for (int i = 1; i <= number; i++)
			{
				currPos.y++;
				firstWireCoord.insert(currPos);
			}
			break;

		case 'D':
			for (int i = 1; i <= number; i++)
			{
				currPos.x++;
				firstWireCoord.insert(currPos);
			}
			break;
		}
		in >> aux;
	}
}


// Parsing every coordinate of the second wire and checking if that coordinate is in the set with the coordinates of the first wire
// If it is, it means we hit an intersection, we save that coord into a vector
void readInput2(std::fstream& in,const std::set<Coordinate>& firstWireCoord, std::vector<Coordinate>& intersections)
{
	std::set<Coordinate>::iterator it = firstWireCoord.end();
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				currPos.x--;
				if ((it = firstWireCoord.find(currPos)) != firstWireCoord.end())
				{
					intersections.push_back(currPos);
				}
			}
			break;

		case 'L':
			for (int i = 1; i <= number; i++)
			{
				currPos.y--;
				if ((it = firstWireCoord.find(currPos)) != firstWireCoord.end())
				{
					intersections.push_back(currPos);
				}
			}
			break;

		case 'R':
			for (int i = 1; i <= number; i++)
			{
				currPos.y++;
				if ((it = firstWireCoord.find(currPos)) != firstWireCoord.end())
				{
					intersections.push_back(currPos);
				}
			}
			break;

		case 'D':
			for (int i = 1; i <= number; i++)
			{
				currPos.x++;
				if ((it = firstWireCoord.find(currPos)) != firstWireCoord.end())
				{
					intersections.push_back(currPos);
				}
			}
			break;
		}
		in >> aux;
	}
}


// Finding the closest intersection from the central port (0,0)
int findDistToClosestIntersection(const std::vector<Coordinate>& intersections)
{
	int minDist = Coordinate::manhattanDistance(Coordinate(0, 0), (*(intersections.begin())));

	for (const auto& intersection : intersections)
	{
		if (Coordinate::manhattanDistance(Coordinate(0, 0), intersection) < minDist)
		{
			minDist = Coordinate::manhattanDistance(Coordinate(0, 0), intersection);
		}
	}

	return minDist;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream in2("input2.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Coordinate> intersections;
	std::set<Coordinate> firstWireCoord;

	readInput(in, firstWireCoord);
	readInput2(in2, firstWireCoord, intersections);

	out << findDistToClosestIntersection(intersections);

	in.close();
	out.close();
}