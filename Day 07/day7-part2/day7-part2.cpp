#include "../../AOCHeaders/stdafx.h"


class Amplifiers
{
public:
	Amplifiers(std::vector<int> integers, int currPosition = 0, int firstInput = 0, int secondInput = 0) :
		integers(integers), currPosition(currPosition), firstInput(firstInput), secondInput(secondInput) {}

public:
	std::vector<int> integers;
	int currPosition;
	int firstInput, secondInput;
};


void readInput(std::fstream& in, std::vector<int>& integers)
{
	int number = 0;
	char aux{};

	while (in >> number)
	{
		integers.push_back(number);
		in >> aux;
	}
}


void intCodeProgram(std::fstream& out, std::vector<int> integers, std::vector<Amplifiers> amplifiers, int& output)
{
	int currAmplifier = 0;
	int currPos = 0;
	int posMode1 = 0;
	int posMode2 = 0;
	int posMode3 = 0;

	while (integers[currPos] != 99)
	{
		posMode1 = (integers[currPos] / 100 % 10 == 1) ? currPos + 1 : (currPos + 1 < integers.size()) ? integers[currPos + 1] : posMode1;
		posMode2 = (integers[currPos] / 1000 % 10 == 1) ? currPos + 2 : (currPos + 2 < integers.size()) ? integers[currPos + 2] : posMode2;
		posMode3 = (integers[currPos] / 10000 % 10 == 1) ? currPos + 3 : (currPos + 3 < integers.size()) ? integers[currPos + 3] : posMode3;

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
			integers[integers[currPos + 1]] = amplifiers[currAmplifier].firstInput;
			amplifiers[currAmplifier].firstInput = amplifiers[currAmplifier].secondInput;
			currPos = currPos + 2;
			break;

		case 4:
			output = integers[integers[currPos + 1]];
			currPos = currPos + 2;

			// Save position of the current amplifier
			amplifiers[currAmplifier].integers = integers;
			amplifiers[currAmplifier].currPosition = currPos;

			// Move to the next amplifier
			currAmplifier = (currAmplifier + 1) % 5;

			// Initialize the integers and currPos with the integers and currPosition saved in the amplifier
			integers = amplifiers[currAmplifier].integers;
			currPos = amplifiers[currAmplifier].currPosition;
			if (amplifiers[currAmplifier].firstInput == amplifiers[currAmplifier].secondInput)
			{
				amplifiers[currAmplifier].firstInput = output;
			}
			amplifiers[currAmplifier].secondInput = output;
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
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> integers;

	readInput(in, integers);

	// Used a vector to save the states of every amplifier
	std::vector<Amplifiers> amplifiers(5, integers);
	std::vector<int> perm{ 5,6,7,8,9 };
	int highestSignal = 0;
	int output = 0;

	do {
		output = 0;
		for (int it = 0; it < perm.size(); it++)
		{
			amplifiers[it].firstInput = perm[it];
		}

		intCodeProgram(out, integers, amplifiers, output);

		highestSignal = std::max(highestSignal, output);

	} while (std::next_permutation(perm.begin(), perm.end()));

	out << highestSignal;

	in.close();
	out.close();
}