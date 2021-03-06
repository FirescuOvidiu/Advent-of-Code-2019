#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int level = 0, int steps = 0) : x(x), y(y), level(level), steps(steps) {}

	bool operator==(const Coordinate& c) const
	{
		return ((this->x == c.x) && (this->y == c.y));
	}

public:
	int x, y;
	int level;
	int steps;
};


bool checkInMap(int x, int y, int lines, int columns)
{
	return x >= 0 && y >= 0 && x < lines && y < columns;
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


void findPortals(const std::vector<std::vector<char>>& map, std::map<std::string, std::pair<Coordinate, Coordinate>>& portals
	, Coordinate& start, Coordinate& end)
{
	int dirX[] = { -1,0,0,1 };
	int dirY[] = { 0,-1,1,0 };
	std::string portalName;
	Coordinate portalCoord;
	bool foundCoordinate = true;

	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[0].size(); y++)
		{
			if (!isupper(map[x][y]))
			{
				continue;
			}
			foundCoordinate = false;
			portalName.clear();
			portalName += map[x][y];

			for (int i = 0; i < 4; i++)
			{
				if ((!checkInMap(x + dirX[i], y + dirY[i], map.size(), map[0].size()))
					|| (map[x + dirX[i]][y + dirY[i]] == '#'))
				{
					continue;
				}

				if (map[x + dirX[i]][y + dirY[i]] == '.')
				{
					portalCoord.x = x + dirX[i];
					portalCoord.y = y + dirY[i];
					foundCoordinate = true;
					continue;
				}

				if (isupper(map[x + dirX[i]][y + dirY[i]]))
				{
					portalName += map[x + dirX[i]][y + dirY[i]];
					if (!foundCoordinate)
					{
						for (int j = 0; j < 4; j++)
						{
							if ((checkInMap(x + dirX[i] + dirX[j], y + dirY[i] + dirY[j], map.size(), map[0].size()))
								&& (map[x + dirX[i] + dirX[j]][y + dirY[i] + dirY[j]] == '.'))
							{
								portalCoord.x = x + dirX[i] + dirX[j];
								portalCoord.y = y + dirY[i] + dirY[j];
								foundCoordinate = true;
								break;
							}
						}
					}
					if (foundCoordinate)
					{
						break;
					}
				}
			}

			std::sort(portalName.begin(), portalName.end());
			if (portals.find(portalName) != portals.end())
			{
				portals[portalName].second = portalCoord;
			}
			else
			{
				portals[portalName].first = portalCoord;
			}
		}
	}

	start = portals["AA"].first;
	end = portals["ZZ"].first;
}


void teleport(std::queue<Coordinate>& q, std::vector<std::vector<std::vector<bool>>>& visit, Coordinate curr, Coordinate first, Coordinate second,
	int lines, int columns)
{
	if (((first.x > 3) && (first.y > 3)) &&
		((first.x < lines - 3) && (first.y < columns - 3)))
	{
		q.push(Coordinate(second.x, second.y, curr.level + 1, curr.steps + 1));
		visit[curr.level + 1][second.x][second.y] = true;
	}
	else
	{
		if (curr.level - 1 >= 0)
		{
			q.push(Coordinate(second.x, second.y, curr.level - 1, curr.steps + 1));
			visit[curr.level - 1][second.x][second.y] = true;
		}
	}
}



int BFS(const std::vector<std::vector<char>>& map, std::map<std::string, std::pair<Coordinate, Coordinate>>& portals, const Coordinate& start, const Coordinate& end)
{
	std::vector<std::vector<std::vector<bool>>> visit(1000, std::vector<std::vector<bool>>(1000, std::vector<bool>(1000)));
	std::vector<int> dirX { -1,0,0,1 };
	std::vector<int> dirY{ 0,-1,1,0 };
	std::queue<Coordinate> q;
	std::string portalName;
	Coordinate curr;
	int x = 0, y = 0;

	q.push(start);
	visit[start.level][start.x][start.y] = true;

	while (!q.empty())
	{
		curr = q.front();
		q.pop();


		if ((curr == end) && (curr.level == end.level))
		{
			return curr.steps;
		}

		for (int i = 0; i < 4; i++)
		{
			x = curr.x + dirX[i];
			y = curr.y + dirY[i];

			if ((!checkInMap(x, y, map.size(), map[0].size()))
				|| (visit[curr.level][x][y]) || (map[x][y] == '#'))
			{
				continue;
			}

			if (map[x][y] == '.')
			{
				q.push(Coordinate(x, y, curr.level, curr.steps + 1));
				visit[curr.level][x][y] = true;
				continue;
			}

			if (isupper(map[x][y]))
			{
				portalName.clear();
				portalName += map[x][y];
				for (int j = 0; j < 4; j++)
				{
					if (isupper(map[x + dirX[j]][y + dirY[j]]))
					{
						portalName += map[x + dirX[j]][y + dirY[j]];
						break;
					}
				}

				if ((portalName == "AA") || (portalName == "ZZ"))
				{
					continue;
				}

				std::sort(portalName.begin(), portalName.end());

				if (curr == portals[portalName].first)
				{
					teleport(q, visit, curr, portals[portalName].first, portals[portalName].second, map.size(), map[0].size());
				}
				else
				{
					teleport(q, visit, curr, portals[portalName].second, portals[portalName].first, map.size(), map[0].size());
				}
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::map<std::string, std::pair<Coordinate, Coordinate>> portals;
	std::vector<std::vector<char>> map;
	Coordinate start, end;

	readInput(in, map);
	findPortals(map, portals, start, end);

	out << BFS(map, portals, start, end);

	in.close();
	out.close();
}