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


Coordinate startAsteroid;


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


Coordinate findCoordMaxAsteroids(const std::vector<std::vector<char>>& map)
{
	int nLines = map.size(), nColumns = map[0].size();

	std::vector<std::vector<bool>> mapBlockedAsteroids(nLines, std::vector<bool>(nColumns));
	std::vector<Coordinate> sortedAsteroids;
	Coordinate asteroidBlocked, distance;
	int countAsteroids = 0, maxAsteroids = 0;
	Coordinate coordMaxAsteroids;

	for (int l = 0; l < nLines; l++)
	{
		for (int c = 0; c < nColumns; c++)
		{
			countAsteroids = 0;

			std::for_each(mapBlockedAsteroids.begin(), mapBlockedAsteroids.end(),
				[](auto& mapBlockedAsteroids) {std::fill(mapBlockedAsteroids.begin(), mapBlockedAsteroids.end(), false); });

			if (map[l][c] == '#')
			{
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
					coordMaxAsteroids = Coordinate(l, c);
					maxAsteroids = countAsteroids;
				}
			}
		}
	}
	return coordMaxAsteroids;
}


bool sortingRule(const Coordinate& firstAst, const Coordinate& secondAst)
{
	return (atan2(firstAst.x - startAsteroid.x, firstAst.y - startAsteroid.y) * 180 / 3.1415 <=
		atan2(secondAst.x - startAsteroid.x, secondAst.y - startAsteroid.y) * 180 / 3.1415);

}

Coordinate find200thAsteroid(std::vector<std::vector<char>>& map, const Coordinate& startAsteroid)
{
	int nLines = map.size(), nColumns = map[0].size();

	std::vector<std::vector<bool>> mapBlockedAsteroids(nLines, std::vector<bool>(nColumns));
	std::vector<Coordinate> sortedAsteroids, visibleAsteroids;
	Coordinate asteroidBlocked, distance;
	int count = 0, it = 0;

	while (true)
	{
		std::for_each(mapBlockedAsteroids.begin(), mapBlockedAsteroids.end(),
			[](auto& mapBlockedAsteroids) {std::fill(mapBlockedAsteroids.begin(), mapBlockedAsteroids.end(), false); });

		sortedAsteroids = findClosestAsteroids(map, startAsteroid, nLines, nColumns);

		if (sortedAsteroids.empty())
		{
			break;
		}

		for (const auto& currAsteroid : sortedAsteroids)
		{
			if (mapBlockedAsteroids[currAsteroid.x][currAsteroid.y])
			{
				continue;
			}

			visibleAsteroids.push_back(Coordinate(currAsteroid.x, currAsteroid.y));
			calcDistBetweenBlockedAsteroids(distance, currAsteroid, startAsteroid.x, startAsteroid.y);

			asteroidBlocked = Coordinate(startAsteroid.x + distance.x, startAsteroid.y + distance.y);
			while (checkInMap(asteroidBlocked, nLines, nColumns))
			{
				mapBlockedAsteroids[asteroidBlocked.x][asteroidBlocked.y] = true;
				asteroidBlocked.x += distance.x;
				asteroidBlocked.y += distance.y;
			}
		}

		std::sort(visibleAsteroids.begin(), visibleAsteroids.end(), sortingRule);
		it = 0;

		while ((it < visibleAsteroids.size()) && 
			(atan2(visibleAsteroids[it].x - startAsteroid.x, visibleAsteroids[it].y - startAsteroid.y) * 180 / 3.1415 < -90))
		{

			it++;
		}

		it--;
		for (int currAst = it; currAst < visibleAsteroids.size() + it; currAst++)
		{
			currAst = currAst % visibleAsteroids.size();
			count++;
			if (count == 200)
			{
				return visibleAsteroids[currAst];
			}
			map[visibleAsteroids[currAst].x][visibleAsteroids[currAst].y] = '.';
		}

		visibleAsteroids.clear();
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;

	readInput(in, map);

	startAsteroid = findCoordMaxAsteroids(map);

	Coordinate Asteroid200 = find200thAsteroid(map, startAsteroid);

	out << Asteroid200.y * 100 + Asteroid200.x;
	in.close();
	out.close();
}