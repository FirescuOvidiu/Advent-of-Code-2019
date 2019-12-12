#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z), velx(0), vely(0), velz(0) {}

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
	for (int currMoon = 0; currMoon < numberMoons; currMoon++)
	{
		for (int otherMoons = 0; otherMoons < numberMoons; otherMoons++)
		{
			if (currMoon == otherMoons)
			{
				continue;
			}

			if (moons[currMoon].x != moons[otherMoons].x)
			{
				moons[currMoon].velx += moons[currMoon].x < moons[otherMoons].x ? 1 : -1;
			}

			if (moons[currMoon].y != moons[otherMoons].y)
			{
				moons[currMoon].vely += moons[currMoon].y < moons[otherMoons].y ? 1 : -1;
			}

			if (moons[currMoon].z != moons[otherMoons].z)
			{
				moons[currMoon].velz += moons[currMoon].z < moons[otherMoons].z ? 1 : -1;
			}
		}
	}
}


int calculateTotalEnergy(std::vector<Coordinate>& moons, const int numberMoons)
{
	int pot = 0, kin = 0, totalEnergy = 0;

	for (int currMoon = 0; currMoon < numberMoons; currMoon++)
	{
		pot = kin = 0;

		pot = abs(moons[currMoon].x) + abs(moons[currMoon].y) + abs(moons[currMoon].z);
		kin = abs(moons[currMoon].velx) + abs(moons[currMoon].vely) + abs(moons[currMoon].velz);
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
		for (int currMoon = 0; currMoon < numberMoons; currMoon++)
		{
			moons[currMoon].x += moons[currMoon].velx;
			moons[currMoon].y += moons[currMoon].vely;
			moons[currMoon].z += moons[currMoon].velz;
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
	int steps = 1000;

	readInput(in, moons);
	out << findTotalEnergy(moons,steps);

	in.close();
	out.close();
}