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


int findTotalOrbits(const std::vector<std::string>& firstObjs, const std::vector<std::string>& secondObjs)
{

	std::queue<std::pair<std::string, int>> objects;
	bool check = true;

	for (int it = 0; it < firstObjs.size(); it++)
	{
		if (firstObjs[it] == "COM")
		{
			objects.push(std::pair<std::string, int>(firstObjs[it], 0));
			break;
		}
	}

	std::pair<std::string, int> currObj;
	int totalOrbits = 0;

	while (!objects.empty())
	{
		currObj = objects.front();
		objects.pop();

		totalOrbits += currObj.second;

		for (int it = 0; it < firstObjs.size(); it++)
		{
			if (currObj.first == firstObjs[it])
			{
				objects.push(std::pair<std::string, int>(secondObjs[it], currObj.second + 1));
			}
		}
	}
	
	return totalOrbits;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::string> firstObjs;
	std::vector<std::string> secondObjs;

	readInput(in, firstObjs, secondObjs);

	out << findTotalOrbits(firstObjs, secondObjs);

	in.close();
	out.close();
}