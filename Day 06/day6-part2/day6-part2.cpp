#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<std::string>& firstObjs, std::vector<std::string>& secondObjs)
{
	std::string line, firstObj, secondObj;

	int it = 0;

	while (std::getline(in, line))
	{
		it = 0;
		while (line[it] != ')')
		{
			firstObj += line[it++];
		}
		it++;
		while (it < line.size())
		{
			secondObj += line[it++];
		}

		firstObjs.push_back(firstObj);
		secondObjs.push_back(secondObj);

		firstObj.erase();
		secondObj.erase();
	}
}


int minOrbits(std::vector<std::string>& firstObjs, std::vector<std::string>& secondObj)
{
	std::queue<std::pair<std::string, int>> objects;
	std::pair<std::string, int> currObj;

	for (int it = 0; it < secondObj.size(); it++)
	{
		if (secondObj[it] == "YOU")
		{
			objects.push(std::pair<std::string, int>(secondObj[it], 0));
			break;
		}
	}


	while (!objects.empty())
	{
		currObj = objects.front();
		objects.pop();

		if (currObj.first == "SAN")
		{
			return currObj.second - 2;
		}
		else
		{
			for (int it = 0; it < firstObjs.size(); it++)
			{
				if ((firstObjs[it] == currObj.first) && (firstObjs[it] != ""))
				{
					objects.push(std::pair<std::string, int>(secondObj[it], currObj.second + 1));
					secondObj[it] = "";
				}
			}

			for (int it = 0; it < secondObj.size(); it++)
			{
				if ((secondObj[it] == currObj.first) && (secondObj[it] != ""))
				{
					objects.push(std::pair<std::string, int>(firstObjs[it], currObj.second + 1));
					firstObjs[it] = "";
				}
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::string> firstObjs;
	std::vector<std::string> secondObj;

	readInput(in, firstObjs, secondObj);

	out << minOrbits(firstObjs, secondObj);

	in.close();
	out.close();
}