#include "../../AOCHeaders/stdafx.h"


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


bool checkInMap(int x, int y, int lines, int columns)
{
	return x >= 0 && y >= 0 && x < lines && y < columns;
}


int findBiodiversityRating(std::vector<std::vector<char>>& map)
{
	std::vector< std::vector<std::vector<char>>> visit;
	std::vector<std::vector<char>> currMap(map);
	std::vector<int> dx{ -1,0,0,1 };
	std::vector<int> dy{ 0,-1,1,0 };
	int bugs{ 0 };

	visit.push_back(map);
	while (true)
	{
		for (int l = 0; l < 5; l++)
		{
			for (int c = 0; c < 5; c++)
			{
				bugs = 0;
				for (int k = 0; k < 4; k++)
				{
					if (checkInMap(l + dx[k], c + dy[k], 5, 5))
					{

						if (map[l + dx[k]][c + dy[k]] == '#')
						{
							bugs++;
						}
					}
				}

				if ((map[l][c] == '#') && (bugs != 1))
				{
					currMap[l][c] = '.';
				}
				if ((map[l][c] == '.') && ((bugs == 1) || (bugs == 2)))
				{
					currMap[l][c] = '#';
				}
			}
		}

		map = currMap;

		for (int it = 0; it < visit.size(); it++)
		{
			if (visit[it] == map)
			{
				int sum = 0;
				for (int l = 0; l < 5; l++)
				{
					for (int c = 0; c < 5; c++)
					{
						if (map[l][c] == '#')
						{
							sum += pow(2, l * 5 + c);
						}
					}
				}
				return sum;
			}
		}

		visit.push_back(map);
	}
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;

	readInput(in, map);

	out << findBiodiversityRating(map);

	in.close();
	out.close();
}