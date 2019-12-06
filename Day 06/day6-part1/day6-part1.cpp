#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::unordered_map<std::string, std::vector<std::string>>& graph)
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
		graph[firstObj].push_back(secondObj);

		firstObj.erase();
		secondObj.erase();
	}
}


int findTotalOrbits(std::unordered_map<std::string, std::vector<std::string>>& graph)
{

	std::queue<std::pair<std::string, int>> objects;
	std::pair<std::string, int> currObj;
	int totalOrbits = 0;

	objects.push(std::pair < std::string, int >("COM", 0));
	while (!objects.empty())
	{
		currObj = objects.front();
		objects.pop();

		totalOrbits += currObj.second;

		for (const auto& adjacent : graph[currObj.first])
		{
			objects.push(std::pair<std::string, int>(adjacent, currObj.second + 1));
		}
	}
	
	return totalOrbits;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::unordered_map<std::string, std::vector<std::string>> graph;

	readInput(in, graph);

	out << findTotalOrbits(graph);

	in.close();
	out.close();
}