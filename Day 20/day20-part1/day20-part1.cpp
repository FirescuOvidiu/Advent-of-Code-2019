#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int steps = 0) : x(x), y(y), steps(steps) {}

	bool operator==(const Coordinate& c) const
	{
		return ((this->x == c.x) && (this->y == c.y));
	}

public:
	int x, y;
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

					if (foundCoordinate)
					{
						break;
					}

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


int BFS(const std::vector<std::vector<char>>& map,std::map<std::string, std::pair<Coordinate, Coordinate>>& portals,
	const Coordinate& start, const Coordinate& end)
{
	std::vector<std::vector<bool>> visit(map.size(), std::vector<bool>(map[0].size()));
	int dirX[] = { -1,0,0,1 };
	int dirY[] = { 0,-1,1,0 };
	std::queue<Coordinate> q;
	std::string portalName;
	Coordinate curr, first, second;
	int x = 0, y = 0;

	q.push(start);
	visit[start.x][start.y] = true;

	while (!q.empty())
	{
		curr = q.front();
		q.pop();

		if (curr == end)
		{
			return curr.steps;
		}

		for (int i = 0; i < 4; i++)
		{
			x = curr.x + dirX[i];
			y = curr.y + dirY[i];

			if ((!checkInMap(x, y, map.size(), map[0].size()))
				|| (visit[x][y]) || (map[x][y] == '#'))
			{
				continue;
			}

			if (map[x][y] == '.')
			{
				q.push(Coordinate(x, y, curr.steps + 1));
				visit[x][y] = true;
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

				std::sort(portalName.begin(), portalName.end());
				if (curr == portals[portalName].first)
				{
					q.push(Coordinate(portals[portalName].second.x, portals[portalName].second.y, curr.steps + 1));
					visit[portals[portalName].second.x][portals[portalName].second.y] = true;
				}
				else
				{
					q.push(Coordinate(portals[portalName].first.x, portals[portalName].first.y, curr.steps + 1));
					visit[portals[portalName].first.x][portals[portalName].first.y] = true;
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