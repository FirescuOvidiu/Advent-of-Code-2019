#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

public:
	int x, y;
};


class state
{
public:
	state(std::vector<long long> integers, Coordinate droid, long long currPos, long long relativeBase) : integers(integers), droid(droid), currPos(currPos), relativeBase(relativeBase) {}

public:
	std::vector<long long> integers;
	Coordinate droid;
	long long currPos;
	long long relativeBase;
};


class node
{
public:
	node(int x = 0, int y = 0, int steps = 0) : x(x), y(y), steps(steps) {}

public:
	int x, y;
	int steps;
};


void readInput(std::fstream& in, std::vector<long long>& integers)
{
	long long number = 0;
	char aux{};

	while (in >> number)
	{
		integers.push_back(number);
		in >> aux;
	}
}


void setPosModes(std::vector<long long>& integers, long long currPos, long long relativeBase, long long& posMode1, long long& posMode2, long long& posMode3, long long opcode)
{
	if (currPos + 3 >= integers.size())
	{
		integers.resize(currPos + 4);
	}

	switch (integers[currPos] / 100 % 10)
	{
	case 0:
		posMode1 = integers[currPos + 1];
		break;

	case 1:
		posMode1 = currPos + 1;
		break;

	case 2:
		posMode1 = relativeBase + integers[currPos + 1];
		break;
	}

	switch (integers[currPos] / 1000 % 10)
	{
	case 0:
		posMode2 = integers[currPos + 2];
		break;

	case 1:
		posMode2 = currPos + 2;
		break;

	case 2:
		posMode2 = relativeBase + integers[currPos + 2];
		break;
	}

	switch (integers[currPos] / 10000 % 10)
	{
	case 0:
		posMode3 = integers[currPos + 3];
		break;

	case 1:
		posMode3 = currPos + 3;
		break;

	case 2:
		posMode3 = relativeBase + integers[currPos + 3];
		break;
	}

	if (posMode1 >= integers.size())
	{
		integers.resize(posMode1 + 1);
	}

	if (posMode2 >= integers.size() &&
		((opcode == 1) || (opcode == 2) || (opcode == 5) || (opcode == 6) || (opcode == 7) || (opcode == 8)))
	{
		integers.resize(posMode2 + 1);
	}

	if ((posMode3 >= integers.size()) &&
		((opcode == 1) || (opcode == 2) || (opcode == 7) || (opcode == 8)))
	{
		integers.resize(posMode3 + 1);
	}
}


void intCodeProgram(std::fstream& out, std::vector<long long>& integers, const long long input, std::vector<std::vector<char>>& map, Coordinate& droid, long long& currPos, long long& relativeBase, Coordinate& oxygenSystem)
{
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;

	while (integers[currPos] != 99)
	{
		setPosModes(integers, currPos, relativeBase, posMode1, posMode2, posMode3, integers[currPos] % 100);

		switch (integers[currPos] % 100)
		{
		case 1:
			integers[posMode3] = integers[posMode2] + integers[posMode1];
			currPos = currPos + 4;
			break;

		case 2:
			integers[posMode3] = integers[posMode2] * integers[posMode1];
			currPos = currPos + 4;
			break;

		case 3:
			integers[posMode1] = input;
			currPos = currPos + 2;
			break;

		case 4:
			switch (integers[posMode1])
			{
			case 0:
				switch (input)
				{
				case 1:
					map[droid.x - 1][droid.y] = '#';
					break;

				case 2:
					map[droid.x + 1][droid.y] = '#';
					break;

				case 3:
					map[droid.x][droid.y - 1] = '#';
					break;

				case 4:
					map[droid.x][droid.y + 1] = '#';
					break;
				}
				break;

			case 1:
				switch (input)
				{
				case 1:
					droid.x--;
					break;

				case 2:
					droid.x++;
					break;

				case 3:
					droid.y--;
					break;

				case 4:
					droid.y++;
					break;
				}
				map[droid.x][droid.y] = '.';
				break;

			case 2:
				oxygenSystem = droid;
				break;
			}

			currPos = currPos + 2;
			return;

		case 5:
			currPos = integers[posMode1] != 0 ? integers[posMode2] : currPos + 3;
			break;

		case 6:
			currPos = integers[posMode1] == 0 ? integers[posMode2] : currPos + 3;
			break;

		case 7:
			integers[posMode3] = integers[posMode1] < integers[posMode2];
			currPos = currPos + 4;
			break;

		case 8:
			integers[posMode3] = integers[posMode1] == integers[posMode2];
			currPos = currPos + 4;
			break;

		case 9:
			relativeBase += integers[posMode1];
			currPos = currPos + 2;
			break;
		}
	}
}


Coordinate findOxygenSystem(std::fstream& out, std::vector<long long>& integers, std::vector<std::vector<char>>& map)
{
	std::vector<int> dirX { 2,-1,1,0,0 };
	std::vector<int> dirY { 2,0,0,-1,1 };
	std::queue<state> states;
	Coordinate droid(map.size() / 2, map.size() / 2), oxygenSystem;
	state currState(integers, droid, 0, 0);
	long long auxCurrPos = 0, auxRelativeBase = 0;

	states.push(state(integers, droid, 0, 0));
	map[droid.x][droid.y] = '.';

	while (!states.empty())
	{
		currState = states.front();
		states.pop();

		for (int moveCommand = 1; moveCommand <= 4; moveCommand++)
		{
			if (map[currState.droid.x + dirX[moveCommand]][currState.droid.y + dirY[moveCommand]] != '-')
			{
				continue;
			}
			
			integers = currState.integers;
			droid = currState.droid;
			auxCurrPos = currState.currPos;
			auxRelativeBase = currState.relativeBase;

			intCodeProgram(out, integers, moveCommand, map, droid, auxCurrPos, auxRelativeBase, oxygenSystem);

			if (map[currState.droid.x + dirX[moveCommand]][currState.droid.y + dirY[moveCommand]] == '.')
			{
				states.push(state(integers, Coordinate(currState.droid.x + dirX[moveCommand], currState.droid.y + dirY[moveCommand]), auxCurrPos, auxRelativeBase));
			}
		}
	}

	return oxygenSystem;
}


void BFS(std::fstream& out, std::vector<std::vector<char>>& map, const Coordinate oxygenSystem)
{
	std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map.size(), false));
	std::queue<node> queue;
	std::vector<int> dirX{ 2,-1,1,0,0 };
	std::vector<int> dirY{ 2,0,0,-1,1 };
	queue.push(node(map.size() / 2, map.size() / 2, 1));
	visited[map.size() / 2][map.size() / 2] = true;

	node currNode;
	while (!queue.empty())
	{
		currNode = queue.front();
		queue.pop();

		if ((currNode.x == oxygenSystem.x) && (currNode.y == oxygenSystem.y))
		{
			out << currNode.steps;
			break;
		}
		else
		{
			for (int i = 1; i <= 4; i++)
			{
				if ((map[currNode.x + dirX[i]][currNode.y + dirY[i]] == '.') && (!visited[currNode.x + dirX[i]][currNode.y + dirY[i]]))
				{
					queue.push(node(currNode.x + dirX[i], currNode.y + dirY[i], currNode.steps + 1));
					visited[currNode.x + dirX[i]][currNode.y + dirY[i]] = true;
				}
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map(5000, std::vector<char>(5000, '-'));
	std::vector<long long> integers;

	readInput(in, integers);

	BFS(out, map, findOxygenSystem(out, integers, map));

	in.close();
	out.close();
}