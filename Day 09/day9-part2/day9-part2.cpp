#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<long long>& integers)
{
	long long number = 0;
	char aux{};
	int it = 0;

	while (in >> number)
	{
		integers[it++] = number;
		in >> aux;
	}
}


void intCodeProgram(std::fstream& out, std::vector<long long>& integers)
{
	long long currPos = 0;
	long long posMode1 = 0;
	long long posMode2 = 0;
	long long posMode3 = 0;
	long long relativeBase = 0;

	while (integers[currPos] != 99)
	{
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
			integers[posMode1] = 2;
			currPos = currPos + 2;
			break;

		case 4:
			out << integers[posMode1] << " ";
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


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<long long> integers(100000000);

	readInput(in, integers);
	intCodeProgram(out, integers);

	in.close();
	out.close();
}