#include "../../AOCHeaders/stdafx.h"


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


void intCodeProgram(std::fstream& out, std::vector<long long>& integers, std::queue<long long>& input,
	std::vector<std::vector<char>>& map)
{
	std::vector<char> line;
	long long currPos = 0;
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;
	long long relativeBase = 0;

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
			integers[posMode1] = input.front();
			input.pop();
			currPos = currPos + 2;
			break;

		case 4:
			switch (integers[posMode1])
			{
			case 10:
				map.push_back(line);
				line.clear();
				break;

			default:
				line.push_back((char)integers[posMode1]);
				break;
			}
			currPos = currPos + 2;
			if (integers[posMode1] > 127)
			{
				out << integers[posMode1] << " ";
			}
			break;

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


void initQueue(const std::string& s, std::queue<long long>& input)
{
	for (int it = 0; it < s.size(); it++)
	{
		input.push((long long)s[it]);
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::vector<char>> map;
	std::vector<long long> integers;
	std::queue<long long> input;

	readInput(in, integers);

	integers[0] = 2;

	// Calculated by hand
	// Sequence L,12,L,12,R,4,R,10,R,6,R,4,R,4,L,12,L,12,R,4,R,6,L,12,L,12,R,10,R,6,R,4,R,4,L,12,L,12,R,4,R,10,R,6,R,4,R,4,R,6,L,12,L,12,R,6,L,12,L,12,R,10,R,6,R,4,R,4
	
	// Main Routine: A,B,A,C,B,A,B,C,C,B
	// (ASCII input: 65, 44, 66, 44, 65, 44, 67, 44, 66, 44, 65, 44, 66, 44, 67, 44, 67, 44, 66, 10)

	// Function A: L,12,L,12,R,4
	// (ASCII input: 76, 44, 49, 50, 44, 76, 44, 49, 50, 44, 82, 44, 52, 10)

	// Function B: R,10,R,6,R,4,R,4
	// (ASCII input: 82, 44, 49, 48, 44, 82, 44, 54, 44, 82, 44, 52, 44, 82, 44, 52, 10)

	// Function C: R,6,L,12,L,12
	// (ASCII input: 82, 44, 54, 44, 76, 44, 49, 50, 44, 76, 44, 49, 50, 10)

	std::string mainRoutine = "A,B,A,C,B,A,B,C,C,B\n";
	std::string A = "L,12,L,12,R,4\n";
	std::string B = "R,10,R,6,R,4,R,4\n";
	std::string C = "R,6,L,12,L,12\n";

	initQueue(mainRoutine, input);
	initQueue(A, input);
	initQueue(B, input);
	initQueue(C, input);
	initQueue("n\n", input);

	intCodeProgram(out, integers, input, map);

	in.close();
	out.close();
}