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


int numberBugs(std::vector<std::vector<char>>& map, const int minutes)
{
	std::vector<std::vector<char>> emptyGrid(5, std::vector<char>(5, '.'));
	std::vector< std::vector<std::vector<char>>> levels;
	std::vector<int> dirX{ -1,0,0,1 };
	std::vector<int> dirY{ 0,-1,1,0 };
	int bugs = 0, lowestDepth{ minutes }, highestDepth{ minutes + 2 };

	emptyGrid[2][2] = '?';
	map[2][2] = '?';

	for (int i = 0; i <= minutes; i++)
	{
		levels.push_back(emptyGrid);
	}
	levels.push_back(map);
	for (int i = 0; i <= minutes; i++)
	{
		levels.push_back(emptyGrid);
	}

	std::vector< std::vector<std::vector<char>>> newLevels(levels);
	std::vector<std::vector<char>> newMap(emptyGrid);

	for (int it = 0; it < minutes; it++)
	{
		for (int lvl = lowestDepth; lvl <= highestDepth; lvl++)
		{
			newMap = levels[lvl];
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					bugs = 0;
					for (int k = 0; k < 4; k++)
					{
						if (checkInMap(i + dirX[k], j + dirY[k], 5, 5))
						{
							if (levels[lvl][i + dirX[k]][j + dirY[k]] == '?')
							{
								switch (k)
								{
								case 0:
									for (int l = 0; l < 5; l++)
									{
										if (levels[lvl + 1][4][l] == '#')
										{
											bugs++;
										}
									}
									break;

								case 1:
									for (int l = 0; l < 5; l++)
									{
										if (levels[lvl + 1][l][4] == '#')
										{
											bugs++;
										}
									}
									break;

								case 2:
									for (int l = 0; l < 5; l++)
									{
										if (levels[lvl + 1][l][0] == '#')
										{
											bugs++;
										}
									}
									break;

								case 3:
									for (int l = 0; l < 5; l++)
									{
										if (levels[lvl + 1][0][l] == '#')
										{
											bugs++;
										}
									}
									break;
								}
							}
							else
							{
								if (levels[lvl][i + dirX[k]][j + dirY[k]] == '#')
								{
									bugs++;
								}
							}
						}
						else
						{
							if (levels[lvl - 1][2 + dirX[k]][2 + dirY[k]] == '#')
							{
								bugs++;
							}
						}
					}

					if ((levels[lvl][i][j] == '#') && (bugs != 1))
					{
						newMap[i][j] = '.';
					}
					if ((levels[lvl][i][j] == '.') && ((bugs == 1) || (bugs == 2)))
					{
						newMap[i][j] = '#';
					}
				}
			}
			newLevels[lvl] = newMap;
		}
		lowestDepth--;
		highestDepth++;
		levels = newLevels;
	}

	int countBugs = 0;
	for (int i = 0; i <= minutes * 2 + 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (levels[i][j][k] == '#')
				{
					countBugs++;
				}
			}
		}
	}

	return countBugs;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;
	const int minutes = 200;

	readInput(in, map);

	out << numberBugs(map, minutes);

	in.close();
	out.close();
}