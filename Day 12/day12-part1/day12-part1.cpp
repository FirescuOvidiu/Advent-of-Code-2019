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


void readInput(std::fstream& in, std::vector<Coordinate>& moons)
{
	Coordinate currMoon;
	char aux{};

	while (in >> aux >> aux >> aux >> currMoon.x >> aux >> aux >> aux >> currMoon.y >> aux >> aux >> aux >> currMoon.z >> aux)
	{
		moons.push_back(currMoon);
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


int calculateTotalEnergy(std::vector<Coordinate>& moons, const int numberMoons)
{
	int pot = 0, kin = 0, totalEnergy = 0;

	for (const auto& currMoon : moons)
	{
		pot = kin = 0;

		pot = abs(currMoon.x) + abs(currMoon.y) + abs(currMoon.z);
		kin = abs(currMoon.velx) + abs(currMoon.vely) + abs(currMoon.velz);
		totalEnergy += pot * kin;
	}

	return totalEnergy;
}


int findTotalEnergy(std::vector<Coordinate>& moons, const int maxSteps)
{
	int numberMoons = moons.size();
	int steps = 0;

	while (steps < maxSteps)
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
		steps++;
	}

	// Calculate the total energy in the system after maxSteps steps
	return calculateTotalEnergy(moons, numberMoons);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<Coordinate> moons;
	int maxSteps = 1000;

	readInput(in, moons);
	out << findTotalEnergy(moons, maxSteps);

	in.close();
	out.close();
}