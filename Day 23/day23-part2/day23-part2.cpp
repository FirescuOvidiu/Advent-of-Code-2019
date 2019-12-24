#include "../../AOCHeaders/stdafx.h"


class NIC
{
public:
	NIC(std::vector<long long> integers = {}, long long currPos = 0) : integers(integers), currPos(currPos) {}

public:
	std::vector<long long> integers;
	std::queue<long long> q;
	long long currPos;
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


void intCodeProgram(std::fstream& out, std::vector<long long> integers, std::vector<NIC>& NIC, long long input)
{
	long long currPos = 0;
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;
	long long relativeBase = 0;

	long long outputAddress = 0;
	int nextInstruction = 0;
	std::vector<int> NAT;
	long long lastNATq = 0;
	bool stateIdle = false;

	for (int i = 0; i < 50; i++)
	{
		NIC[i].q.push(i);
	}

	while (true)
	{
		for (int i = 0; i < 50; i++)
		{
			currPos = NIC[i].currPos;
			integers = NIC[i].integers;

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
						// The incoming packet queue is empty
						input = -1;
						integers[posMode1] = input;
						currPos = currPos + 2;
						// Save the state of the NIC computer
						NIC[i].currPos = currPos;
						NIC[i].integers = integers;
						// Move to the next computer
						integers[currPos] = 99;
						break;
					}
					else
					{
						input = NIC[i].q.front();
						NIC[i].q.pop();
					}

					integers[posMode1] = input;
					currPos = currPos + 2;
					break;

				case 4:
					if (nextInstruction == 0)
					{
						outputAddress = integers[posMode1];
						nextInstruction++;
					}
					else
					{
						if (outputAddress < 50)
						{
							NIC[outputAddress].q.push(integers[posMode1]);
						}
						else
						{
							if (NAT.size() == 2)
							{
								NAT.clear();
							}
							NAT.push_back(integers[posMode1]);
						}

						nextInstruction = (nextInstruction + 1) % 3;
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

		if ((stateIdle) && (!NAT.empty()))
		{
			if (lastNATq == NAT[1])
			{
				out << NAT[1];
				return;
			}

			NIC[0].q.push(NAT[0]);
			NIC[0].q.push(NAT[1]);
			lastNATq = NAT[1];
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