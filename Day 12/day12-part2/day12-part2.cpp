#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z), velx(0), vely(0), velz(0) {}

	bool operator==(const Coordinate& c) const
	{
		return (this->x == c.x && this->y == c.y && this->z == c.z &&
			this->velx == c.velx && this->vely == c.vely && this->velz == c.velz);
	}

public:
	int x, y, z;
	int velx, vely, velz;
};


void readInput(std::fstream& in, std::vector<Coordinate>& moons, std::vector<std::vector<int>>& initialMoonsPos)
{
	Coordinate currMoon;
	char aux{};

	while (in >> aux >> aux >> aux >> currMoon.x >> aux >> aux >> aux >> currMoon.y >> aux >> aux >> aux >> currMoon.z >> aux)
	{
		moons.push_back(currMoon);
		initialMoonsPos[0].push_back(currMoon.x);
		initialMoonsPos[1].push_back(currMoon.y);
		initialMoonsPos[2].push_back(currMoon.z);
	}
}


void updateVelocity(std::vector<Coordinate>& moons, const int numberMoons)
{
	for (auto& currMoon : moons)
	{
		for (const auto& otherMoons : moons)
		{
			if (currMoon == otherMoons)
			{
				continue;
			}

			if (currMoon.x != otherMoons.x)
			{
				currMoon.velx += currMoon.x < otherMoons.x ? 1 : -1;
			}

			if (currMoon.y != otherMoons.y)
			{
				currMoon.vely += currMoon.y < otherMoons.y ? 1 : -1;
			}

			if (currMoon.z != otherMoons.z)
			{
				currMoon.velz += currMoon.z < otherMoons.z ? 1 : -1;
			}
		}
	}
}


bool findIndependentCoordinates(const std::vector<Coordinate>& moons, const std::vector<std::vector<int>>& initialMoonsPos,
	 Coordinate& repeatMoonsPosAfter, const int steps, const int numberMoons)
{
	std::vector<bool> checkInitPos(3, true);

	for (int currMoon = 0; currMoon < numberMoons; currMoon++)
	{
		if ((initialMoonsPos[0][currMoon] != moons[currMoon].x) || (moons[currMoon].velx != 0))
		{
			checkInitPos[0] = false;
		}

		if ((initialMoonsPos[1][currMoon] != moons[currMoon].y) || (moons[currMoon].vely != 0))
		{
			checkInitPos[1] = false;
		}

		if ((initialMoonsPos[2][currMoon] != moons[currMoon].z) || (moons[currMoon].velz != 0))
		{
			checkInitPos[2] = false;
		}
	}


	if ((checkInitPos[0]) && (repeatMoonsPosAfter.x == -1))
	{
		repeatMoonsPosAfter.x = steps;
	}

	if ((checkInitPos[1]) && (repeatMoonsPosAfter.y == -1))
	{
		repeatMoonsPosAfter.y = steps;
	}

	if ((checkInitPos[2]) && (repeatMoonsPosAfter.z == -1))
	{
		repeatMoonsPosAfter.z = steps;
	}

	return (repeatMoonsPosAfter.x != -1 && repeatMoonsPosAfter.y != -1 && repeatMoonsPosAfter.z != -1);
}


long long findGCD(long long a, long long b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		long long r = a % b;

		while (r != 0)
		{
			a = b;
			b = r;
			r = a % b;
		}

		return b;
	}
}


long long findLCM(long long a, long long b)
{
	return (a * b) / findGCD(a, b);
}


long long findSteps(std::vector<Coordinate>& moons, const std::vector<std::vector<int>>& initialMoonsPos)
{
	Coordinate repeatMoonsPosAfter(-1, -1, -1);
	int numberMoons = moons.size();
	int steps = 1;

	while (true)
	{
		// Update velocity of the moons by applying gravity
		updateVelocity(moons, numberMoons);

		// Update position of the moons by applaying velocity
		for (auto& currMoon : moons)
		{
			currMoon.x += currMoon.velx;
			currMoon.y += currMoon.vely;
			currMoon.z += currMoon.velz;
		}

		// Finding after how many steps the coodinates X,Y,Z repeat
		if (findIndependentCoordinates(moons, initialMoonsPos, repeatMoonsPosAfter, steps, numberMoons))
		{
			break;
		}
		steps++;
	}
	
	return findLCM(findLCM(repeatMoonsPosAfter.x, repeatMoonsPosAfter.y), repeatMoonsPosAfter.z);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<int>> initialMoonsPos(3);
	std::vector<Coordinate> moons;

	readInput(in, moons, initialMoonsPos);

	out << findSteps(moons, initialMoonsPos);

	in.close();
	out.close();
}