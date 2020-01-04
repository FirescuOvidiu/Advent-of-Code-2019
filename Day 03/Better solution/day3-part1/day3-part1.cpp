#include "../../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	static int manhattanDistance(const Coordinate& c1, const Coordinate& c2)
	{
		return abs(c1.x - c2.x) + abs(c1.y - c2.y);
	}

public:
	int x, y;
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


// We save into a vector the segments of the first wire
// A segment is represented by two coordinates:
// - start coordinate and the next position of that coordinate after executing the instruction (L/R/U/D number)
void readInput(std::fstream& in, std::vector<Segment>& firstWireCoord)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x - number, currPos.y), Coordinate(currPos.x - 1, currPos.y), false));
			currPos.x -= number;
			break;

		case 'L':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x, currPos.y - number), Coordinate(currPos.x, currPos.y - 1), true));
			currPos.y -= number;
			break;

		case 'R':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x, currPos.y + 1), Coordinate(currPos.x, currPos.y + number), true));
			currPos.y += number;
			break;

		case 'D':
			firstWireCoord.push_back(Segment(Coordinate(currPos.x + 1, currPos.y), Coordinate(currPos.x + number, currPos.y), false));
			currPos.x += number;
			break;
		}
		in >> aux;
	}
}


// We calculate the segments of the second wire and check for every segment if it intersects the segments from the first wire
// If it does we add the coordinate of the intersection to a vector (see checkIntersection function)
void readInput2(std::fstream& in, const std::vector<Segment>& firstWireCoord, std::vector<Coordinate>& intersections)
{
	Coordinate currPos(0, 0);
	char dir{}, aux{};
	int number = 0;

	while (in >> dir >> number)
	{
		switch (dir)
		{
		case 'U':
			for (const auto& segment : firstWireCoord)
			{
				checkIntersection(Segment(Coordinate(currPos.x - number, currPos.y), Coordinate(currPos.x - 1, currPos.y), false), segment, intersections);
			}
			currPos.x -= number;
			break;

		case 'L':
			for (const auto& segment : firstWireCoord)
			{
				checkIntersection(Segment(Coordinate(currPos.x, currPos.y - number), Coordinate(currPos.x, currPos.y - 1), true), segment, intersections);
			}
			currPos.y -= number;
			break;


		case 'R':
			for (const auto& segment : firstWireCoord)
			{
				checkIntersection(Segment(Coordinate(currPos.x, currPos.y + 1), Coordinate(currPos.x, currPos.y + number), true), segment, intersections);
			}
			currPos.y += number;
			break;

		case 'D':
			for (const auto& segment : firstWireCoord)
			{
				checkIntersection(Segment(Coordinate(currPos.x + 1, currPos.y), Coordinate(currPos.x + number, currPos.y), false), segment, intersections);
			}
			currPos.x += number;
			break;
		}
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
	// and add to a vector the points of intersection
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
	// and add to a vector the points of intersection
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
	// Checking if the two lines intersect and add to a vector the intersection point
	if (!s1.hOv)
	{
		std::swap(s1, s2);
	}

	intersPoint.x = s1.a.x;
	intersPoint.y = s2.a.y;

	if (((intersPoint.x >= s2.a.x) && (intersPoint.x <= s2.b.x)) &&
		((intersPoint.y >= s1.a.y) && (intersPoint.y <= s1.b.y)))
	{
		intersections.push_back(intersPoint);
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
	std::vector<Segment> firstWireCoord;
	std::vector<Coordinate> intersections;

	readInput(in, firstWireCoord);
	readInput2(in2, firstWireCoord, intersections);

	out << findDistToClosestIntersection(intersections);

	in.close();
	out.close();
}