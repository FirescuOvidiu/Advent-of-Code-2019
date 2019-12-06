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
		graph[secondObj].push_back(firstObj);

		firstObj.erase();
		secondObj.erase();
	}
}


int minOrbits(std::unordered_map<std::string, std::vector<std::string>>& graph)
{
	std::unordered_map<std::string, bool> visit;
	std::queue<std::pair<std::string, int>> objects;
	std::pair<std::string, int> currObj;

	objects.push(std::pair<std::string, int>("YOU", 0));
	visit["YOU"] = true;

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
			for (const auto& adjacent : graph[currObj.first])
			{
				if (!visit[adjacent])
				{
					objects.push(std::pair<std::string, int>(adjacent, currObj.second + 1));
					visit[adjacent] = true;
				}
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::unordered_map<std::string, std::vector<std::string>> graph;

	readInput(in, graph);

	out << minOrbits(graph);

	in.close();
	out.close();
}