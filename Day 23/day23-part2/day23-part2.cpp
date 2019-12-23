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


class Coordinate
{
public:
	Coordinate(long long x = 0, long long y = 0, long long address = 0, int nextInstruction = 3) : x(x), y(y), address(address), nextInstruction(nextInstruction) {}

public:
	long long x, y, address;
	int nextInstruction;
};


class NIC
{
public:
	NIC(std::vector<long long> integers = {}, long long currPos = 0) : integers(integers), currPos(currPos) {}

public:
	std::vector<long long> integers;
	std::queue<Coordinate> q;
	long long currPos;
};


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


void intCodeProgram(std::fstream& out, std::vector<long long> integers, std::vector<NIC>& NIC, long long input)
{
	long long currPos = 0;
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;
	long long relativeBase = 0;

	Coordinate output(0, 0, 0, 0);
	Coordinate NAT, lastNAT;
	int it = 0;
	bool stateIdle = true;

	for (int i = 0; i < 50; i++)
	{
		NIC[i].q.push(Coordinate(0, 0, 3));
	}

	while (true)
	{
		for (int i = 0; i < 50; i++)
		{
			currPos = NIC[i].currPos;
			integers = NIC[i].integers;
			it = 0;

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
					if (NIC[i].q.empty())
					{
						input = -1;
					}
					else
					{
						switch (NIC[i].q.front().nextInstruction)
						{
						case 1:
							input = NIC[i].q.front().x;
							NIC[i].q.front().nextInstruction++;
							break;

						case 2:
							input = NIC[i].q.front().y;
							NIC[i].q.pop();
							break;

						default:
							input = i;
							NIC[i].q.pop();
							break;
						}
					}

					integers[posMode1] = input;
					currPos = currPos + 2;
					break;

				case 4:
					switch (output.nextInstruction)
					{
					case 0:
						output.address = integers[posMode1];
						output.nextInstruction++;
						break;

					case 1:
						output.x = integers[posMode1];
						output.nextInstruction++;
						break;

					case 2:
						output.nextInstruction--;
						output.y = integers[posMode1];

						if (output.address < 50)
						{
							NIC[output.address].q.push(output);
						}
						else
						{
							NAT = output;
						}

						output.nextInstruction = 0;
					}

					currPos = currPos + 2;
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

				if (it++ > 10000)
				{
					NIC[i].currPos = currPos;
					NIC[i].integers = integers;
					break;
				}
			}
		}

		stateIdle = true;
		for (int i = 0; i < 50; i++)
		{
			if (!NIC[i].q.empty())
			{
				stateIdle = false;
				break;
			}
		}

		if (stateIdle)
		{
			if (lastNAT.y == NAT.y)
			{
				out << NAT.y;
				return;
			}
			lastNAT = NAT;
			NIC[0].q.push(NAT);
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<long long> integers;
	long long input = -1;

	readInput(in, integers);

	std::vector<NIC> NIC(50, NIC(integers, 0));

	intCodeProgram(out, integers, NIC, input);

	in.close();
	out.close();
}