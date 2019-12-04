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


// We save into a vector the segments of the first wire and the steps of the coordinates of the segment
// A segment is represented by two coordinates:
// - start coordinate and the next position of that coordinate after executing the instruction (L/R/U/D number)
void readInput(std::fstream& in, std::vector<Segment>& firstWireCoord)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0, steps = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x - number, currPos.y, steps + number), Coordinate(currPos.x - 1, currPos.y, steps + 1), false));
			currPos.x -= number;
			break;

		case 'L':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x, currPos.y - number, steps + number), Coordinate(currPos.x, currPos.y - 1, steps + 1), true));
			currPos.y -= number;
			break;

		case 'R':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x, currPos.y + 1, steps + 1), Coordinate(currPos.x, currPos.y + number, steps + number), true));
			currPos.y += number;
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


// We calculate the segments of the second wire and the steps for the two corodinates of the segment
// and check for every segment if it intersects the segments from the first wire
// If it does we find and save the coordinate of the intersection and the steps of the intersection point in a vector(see checkIntersection function)
void readInput2(std::fstream& in, std::vector<Segment>& firstWireCoord, std::vector<Coordinate>& intersections)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0, steps = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x - number, currPos.y, steps + number), Coordinate(currPos.x - 1, currPos.y, steps + 1), false), (*currSegment), intersections);
			}
			currPos.x -= number;
			break;

		case 'L':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x, currPos.y - number, steps + number), Coordinate(currPos.x, currPos.y - 1, steps + 1), true), (*currSegment), intersections);
			}
			currPos.y -= number;
			break;

		case 'R':
			for (std::vector<Segment>::iterator currSegment = firstWireCoord.begin(); currSegment != firstWireCoord.end(); currSegment++)
			{
				checkIntersection(Segment(Coordinate(currPos.x, currPos.y + 1, steps + 1), Coordinate(currPos.x, currPos.y + number, steps + number), true), (*currSegment), intersections);
			}
			currPos.y += number;
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
	// and add to a vector the points of intersection with their steps
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
			Coordinate left = s2.a;
			Coordinate right = std::min(s1.b, s2.b);
			if (left.steps > right.steps)
			{
				std::swap(left, right);
			}
			for (int pos = left.y; pos <= right.y; pos++)
			{
				intersections.push_back(Coordinate(s1.a.x, left.steps + std::abs(pos - left.y)));
			}
		}
	}

	// Checking if we have vertical paralel lines and have the same y
	// and add to a vector the points of intersection with their steps
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
			Coordinate left = s2.a;
			Coordinate right = std::min(s1.b, s2.b);
			if (left.steps > right.steps)
			{
				std::swap(left, right);
			}
			for (int pos = left.x; pos <= right.x; pos++)
			{
				intersections.push_back(Coordinate(pos, s1.a.y, left.steps + std::abs(pos - left.x)));
			}
		}
	}

	Coordinate intersPoint;
	// Checking if the two lines intersect and add to a vector the intersection point
	// with the steps necessary to get to that point

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