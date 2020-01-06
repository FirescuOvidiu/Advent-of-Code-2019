#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	bool operator<(const Coordinate& c) const
	{
		return this->x < c.x ? true : this->x == c.x ? this->y < this->x : false;
	}

	bool operator==(const Coordinate& c) const
	{
		return ((this->x == c.x) && (this->y == c.y));
	}

public:
	int x, y;
};


int findGCD(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		int r = a % b;

		while (r != 0)
		{
			a = b;
			b = r;
			r = a % b;
		}

		return b;
	}
}


void calcDistBetweenBlockedAsteroids(Coordinate& distance, const Coordinate& currAsteroid, const int l, const int c)
{
	int cmmdc = findGCD(abs(currAsteroid.x - l), abs(currAsteroid.y - c));
	distance.x = abs(currAsteroid.x - l) / cmmdc;
	distance.y = abs(currAsteroid.y - c) / cmmdc;

	if ((currAsteroid.x >= l) && (currAsteroid.y < c))
	{
		distance.y = -distance.y;
	}
	else
	{
		if ((currAsteroid.x < l) && (currAsteroid.y >= c))
		{
			distance.x = -distance.x;
		}
		else
			if ((currAsteroid.x < l) && (currAsteroid.y <= c))
			{
				distance.y = -distance.y;
				distance.x = -distance.x;
			}
	}
}


bool checkInMap(const Coordinate& c, const int nLines, const int nColumns)
{
	return (c.x < nLines && c.x >= 0 && c.y < nColumns && c.y >= 0);
}


std::vector<Coordinate> findClosestAsteroids(std::vector<std::vector<char>> map, Coordinate startAsteroid, int nLines, int nColumns)
{
	std::vector<std::vector<bool>> visit(nLines, std::vector<bool>(nColumns));
	std::vector<Coordinate> asteroids;
	int dx[] = { -1,0,0,1 };
	int dy[] = { 0,-1,1,0 };

	std::queue<Coordinate> queue;
	Coordinate currCoord, newCoord;

	queue.push(Coordinate(startAsteroid.x, startAsteroid.y));
	visit[startAsteroid.x][startAsteroid.y] = true;

	while (!queue.empty())
	{
		currCoord = queue.front();
		queue.pop();

		for (int i = 0; i < 4; i++)
		{
			newCoord = Coordinate(currCoord.x + dx[i], currCoord.y + dy[i]);

			if (checkInMap(newCoord, nLines, nColumns) && (!visit[newCoord.x][newCoord.y]))
			{
				queue.push(Coordinate(newCoord.x, newCoord.y));
				visit[newCoord.x][newCoord.y] = true;

				if (map[newCoord.x][newCoord.y] == '#')
				{
					asteroids.push_back(Coordinate(newCoord.x, newCoord.y));
				}
			}
		}
	}

	return asteroids;
}


void readInput(std::fstream& in, std::vector<std::vector<char>>& map)
{
	std::vector<char> v;
	std::string line;

	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			v.push_back(line[i]);
		}
		map.push_back(v);
		v.clear();
	}
}


int findMaxAsteroids(const std::vector<std::vector<char>>& map)
{
	int nLines = map.size(), nColumns = map[0].size();

	std::vector<std::vector<bool>> mapBlockedAsteroids(nLines, std::vector<bool>(nColumns));
	std::vector<Coordinate> sortedAsteroids;
	Coordinate asteroidBlocked, distance;
	int countAsteroids = 0, maxAsteroids = 0;

	for (int l = 0; l < nLines; l++)
	{
		for (int c = 0; c < nColumns; c++)
		{
			if (map[l][c] != '#')
			{
				continue;
			}

			countAsteroids = 0;
			std::for_each(mapBlockedAsteroids.begin(), mapBlockedAsteroids.end(),
				[](auto& mapBlockedAsteroids) {std::fill(mapBlockedAsteroids.begin(), mapBlockedAsteroids.end(), false); });

			sortedAsteroids = findClosestAsteroids(map, Coordinate(l, c), nLines, nColumns);

			for (const auto& currAsteroid : sortedAsteroids)
			{
				if (mapBlockedAsteroids[currAsteroid.x][currAsteroid.y])
				{
					continue;
				}

				countAsteroids++;
				calcDistBetweenBlockedAsteroids(distance, currAsteroid, l, c);

				asteroidBlocked = Coordinate(l + distance.x, c + distance.y);
				while (checkInMap(asteroidBlocked, nLines, nColumns))
				{
					mapBlockedAsteroids[asteroidBlocked.x][asteroidBlocked.y] = true;
					asteroidBlocked.x += distance.x;
					asteroidBlocked.y += distance.y;
				}
			}
			if (countAsteroids > maxAsteroids)
			{
				maxAsteroids = countAsteroids;
			}
		}
	}
	return maxAsteroids;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;

	readInput(in, map);

	out << findMaxAsteroids(map);

	in.close();
	out.close();
}