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


void findPortals(const std::vector<std::vector<char>>& map, std::vector<std::tuple<std::string, Coordinate, Coordinate>>& portals
	, Coordinate& start, Coordinate& end)
{
	int dirX[] = { -1,0,0,1 };
	int dirY[] = { 0,-1,1,0 };
	std::string portalName;
	Coordinate portalCoord;
	bool foundCoordinate = true;
	bool foundPortal = true;

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

			foundPortal = false;
			for (auto& portal : portals)
			{
				std::sort(portalName.begin(), portalName.end());
				if (std::get<0>(portal) == portalName)
				{
					std::get<2>(portal) = portalCoord;
					foundPortal = true;
					break;
				}
			}

			if (!foundPortal)
			{
				std::sort(portalName.begin(),portalName.end());
				portals.push_back(std::make_tuple(portalName, portalCoord, portalCoord));
			}
		}
	}

	for (auto& portal : portals)
	{
		if (std::get<0>(portal) == "AA")
		{
			start = std::get<1>(portal);
		}
		if (std::get<0>(portal) == "ZZ")
		{
			end = std::get<1>(portal);
		}
	}
}


int BFS(const std::vector<std::vector<char>>& map,const std::vector<std::tuple<std::string, Coordinate, Coordinate>>& portals,
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

				for (const auto& portal : portals)
				{
					std::sort(portalName.begin(), portalName.end());

					if (std::get<0>(portal) != portalName)
					{
						continue;
					}

					first = std::get<1>(portal);
					second = std::get<2>(portal);

					if (curr == first)
					{
						q.push(Coordinate(second.x, second.y, curr.steps + 1));
						visit[second.x][second.y] = true;
					}
					else
					{
						q.push(Coordinate(first.x, first.y, curr.steps + 1));
						visit[first.x][first.y] = true;
					}
					break;
				}
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;
	std::vector<std::tuple<std::string, Coordinate, Coordinate>> portals;
	Coordinate start, end;

	readInput(in, map);
	findPortals(map, portals, start, end);

	out << BFS(map, portals, start, end);

	in.close();
	out.close();
}