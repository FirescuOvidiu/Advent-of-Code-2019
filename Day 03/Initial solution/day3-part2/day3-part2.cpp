#include "../../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int stepts = 0) : x(x), y(y), steps(stepts) {}

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
	int steps;
};


// Saving every coordinate of the first path and the steps made to get to that coordinate into a list
void readInput(std::fstream& in, std::list<Coordinate>& firstWireCoord)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0, steps = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				steps++;
				currPos.x--;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y, steps));
			}
			break;

		case 'L':
			for (int i = 1; i <= number; i++)
			{

				steps++;
				currPos.y--;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y, steps));
			}
			break;

		case 'R':
			for (int i = 1; i <= number; i++)
			{
				steps++;
				currPos.y++;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y, steps));
			}
			break;

		case 'D':
			for (int i = 1; i <= number; i++)
			{

				steps++;
				currPos.x++;
				firstWireCoord.push_back(Coordinate(currPos.x, currPos.y, steps));
			}
			break;

		default:
			break;
		}
		in >> aux;
	}
}


// Parsing every coordinate of the second wire, calculate the steps for every coordinate,
// and check if that coordinate is in the list with the coordinates of the first wire
// If it is, it means we hit an intersection, we save that coord and the steps from first wire + steps from second wire into a vector
void readInput2(std::fstream& in, std::list<Coordinate>& firstWireCoord, std::vector<Coordinate>& intersections)
{
	std::list<Coordinate>::iterator it = firstWireCoord.end();
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0, steps = 0;


	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			for (int i = 1; i <= number; i++)
			{
				steps++;
				currPos.x--;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y, steps + (*it).steps));
				}
			}
			break;

		case 'L':
			for (int i = 1; i <= number; i++)
			{
				steps++;
				currPos.y--;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y, steps + (*it).steps));
				}
			}
			break;

		case 'R':
			for (int i = 1; i <= number; i++)
			{
				steps++;
				currPos.y++;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y, steps + (*it).steps));
				}
			}
			break;

		case 'D':
			for (int i = 1; i <= number; i++)
			{
				steps++;
				currPos.x++;
				if ((it = std::find(firstWireCoord.begin(), firstWireCoord.end(), currPos)) != firstWireCoord.end())
				{
					intersections.push_back(Coordinate(currPos.x, currPos.y, steps + (*it).steps));
				}
			}
			break;

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

	// Calculating the minimum number of steps and saving it into a variable
	int minSteps = (*(intersections.begin())).steps;
	for (auto it = intersections.begin() + 1; it != intersections.end(); it++)
	{
		if ((*it).steps < minSteps)
		{
			minSteps = (*it).steps;
		}
	}

	out << minSteps;

	in.close();
	out.close();
}