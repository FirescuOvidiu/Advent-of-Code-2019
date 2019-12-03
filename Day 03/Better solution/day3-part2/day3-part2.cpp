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


class Segment
{
public:
	Segment(Coordinate a, Coordinate b, bool hOv = false) : a(a), b(b), hOv(hOv) {}

public:
	Coordinate a, b;
	bool hOv;		// Information about the position of the Segment if its horizontal(true) or vertical(false)
};


void checkIntersection(Segment s1, Segment s2, std::vector<Coordinate>& intersections);


void readInput(std::fstream& in, std::vector<Segment>& firstWireCoord)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0, steps = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'R':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x, currPos.y + 1, steps + 1), Coordinate(currPos.x, currPos.y + number, steps + number), true));
			currPos.y += number;
			break;

		case 'L':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x, currPos.y - number, steps + number), Coordinate(currPos.x, currPos.y - 1, steps + 1), true));
			currPos.y -= number;
			break;

		case 'U':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x - number, currPos.y, steps+ number), Coordinate(currPos.x - 1, currPos.y, steps + 1) , false));
			currPos.x -= number;
			break;

		case 'D':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x + 1, currPos.y, steps + 1), Coordinate(currPos.x + number, currPos.y, steps + number), false));
			currPos.x += number;
			break;

		default:
			break;
		}
		steps += number;
		in >> aux;
	}
}


void readInput2(std::fstream& in, std::vector<Segment>& firstWireCoord, std::vector<Coordinate>& intersections)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0, steps = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'R':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x, currPos.y + 1, steps + 1), Coordinate(currPos.x, currPos.y + number, steps + number), true), (*currSegment), intersections);
			}
			currPos.y += number;
			break;

		case 'L':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x, currPos.y - number, steps + number), Coordinate(currPos.x, currPos.y - 1, steps + 1), true), (*currSegment), intersections);
			}
			currPos.y -= number;
			break;

		case 'U':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x - number, currPos.y, steps + number), Coordinate(currPos.x - 1, currPos.y, steps + 1), false), (*currSegment), intersections);
			}
			currPos.x -= number;
			break;

		case 'D':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x + 1, currPos.y, steps + 1), Coordinate(currPos.x + number, currPos.y, steps + number), false), (*currSegment), intersections);
			}
			currPos.x += number;
			break;

		default:
			break;
		}
		steps += number;
		in >> aux;
	}
}


void checkIntersection(Segment s1, Segment s2, std::vector<Coordinate>& intersections)
{
	// Checking if we have paralel lines
	if (((s1.hOv) && (s2.hOv) && (s1.a.x != s2.a.x)) ||
		((!s1.hOv) && (!s2.hOv) && (s1.a.y != s2.a.y)))
	{
		return;
	}

	// Checking if we have horizontal paralel lines and have the same x
	if ((s1.hOv) && (s2.hOv) && (s1.a.x == s2.a.x))
	{
		if (s1.a.y > s2.a.y)
		{
			std::swap(s1, s2);
		}

		if (s1.b.y < s2.a.y)
		{
			return;
		}
		else
		{
			for (int pos = s1.a.y; pos <= std::min(s1.b.y, s2.b.y); pos++)
			{
				intersections.push_back(Coordinate(s1.a.x, pos));
			}
		}
	}

	// Checking if we have vertical paralel lines and have the same y
	if ((!s1.hOv) && (!s2.hOv) && (s1.a.y == s2.a.y))
	{
		if (s1.a.x > s2.a.x)
		{
			std::swap(s1, s2);
		}

		if (s1.b.x < s2.a.x)
		{
			return;
		}
		else
		{
			for (int pos = s1.a.x; pos <= std::min(s1.b.x, s2.b.x); pos++)
			{
				intersections.push_back(Coordinate(pos, s1.a.y));
			}
		}
	}

	Coordinate intersPoint;
	// Checking if the two lines are intersected

	if (!s1.hOv)
	{
		std::swap(s1, s2);
	}
	intersPoint.x = s1.a.x;
	intersPoint.y = s2.a.y;

	if (((intersPoint.x >= s2.a.x) && (intersPoint.x <= s2.b.x)) &&
		((intersPoint.y >= s1.a.y) && (intersPoint.y <= s1.b.y)))
	{
		intersPoint.steps += s1.a.steps < s1.b.steps ? s1.a.steps + abs(intersPoint.y - s1.a.y) : s1.b.steps + abs(intersPoint.y - s1.b.y);
		intersPoint.steps += s2.a.steps < s2.b.steps ? s2.a.steps + abs(intersPoint.x - s2.a.x) : s2.b.steps + abs(intersPoint.x - s2.b.x);
		intersections.push_back(intersPoint);
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream in2("input2.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Segment> firstWireCoord;
	std::vector<Coordinate> intersections;

	readInput(in, firstWireCoord);
	readInput2(in2, firstWireCoord, intersections);

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