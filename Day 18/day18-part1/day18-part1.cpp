#include "../../AOCHeaders/stdafx.h"


const int letters = 26;


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0, int steps = 0, long long visited = 0) : x(x), y(y), steps(steps), visited(visited) {}

public:
	int x, y;
	int steps;
	long long visited;
};


void readInput(std::fstream& in, std::vector<std::vector<char>>& map, Coordinate& startCoordinate)
{
	std::vector<char> v;
	std::string line;

	while (std::getline(in, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			v.push_back(line[i]);
			if (v[i] == '@')
			{
				startCoordinate.x = map.size();
				startCoordinate.y = i;
				v[i] = '.';
			}
		}
		map.push_back(v);
		v.clear();
	}
}


bool checkInMap(int x, int y, int lines, int columns)
{
	return x >= 0 && y >= 0 && x < lines && y < columns;
}


int BFS(const std::vector<std::vector<char>>& map, const Coordinate& startCoordinate)
{
	std::set<std::tuple<int, int, long long>> repeated;
	std::vector<int> dirX{ -1,0,0,1 };
	std::vector<int> dirY{ 0,-1,1,0 };
	std::bitset<letters> auxVisited;
	std::queue<Coordinate> q;
	Coordinate curr;

	q.push(startCoordinate);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		auxVisited = curr.visited;

		if (auxVisited.all())
		{
			return curr.steps;
		}

		for (int i = 0; i < 4; i++)
		{
			if ((!checkInMap(curr.x, curr.y, map.size(), map[0].size()))
				|| (map[curr.x + dirX[i]][curr.y + dirY[i]] == '#')
				|| repeated.find(std::make_tuple(curr.x + dirX[i], curr.y + dirY[i], curr.visited)) != repeated.end())
			{
				continue;
			}

			if (isupper(map[curr.x + dirX[i]][curr.y + dirY[i]])
				&& (!auxVisited[map[curr.x + dirX[i]][curr.y + dirY[i]] - 'A']))
			{
				continue;
			}

			if (islower(map[curr.x + dirX[i]][curr.y + dirY[i]]))
			{
				auxVisited[map[curr.x + dirX[i]][curr.y + dirY[i]] - 'a'] = true;
			}

			q.push(Coordinate(curr.x + dirX[i], curr.y + dirY[i], curr.steps + 1, auxVisited.to_ullong()));
			repeated.insert(std::make_tuple(curr.x + dirX[i], curr.y + dirY[i], auxVisited.to_ullong()));

			if (islower(map[curr.x + dirX[i]][curr.y + dirY[i]]))
			{
				auxVisited[map[curr.x + dirX[i]][curr.y + dirY[i]] - 'a'] = false;
			}
		}
	}
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;
	Coordinate startCoordinate;

	readInput(in, map, startCoordinate);

	out << BFS(map, startCoordinate);

	in.close();
	out.close();
}