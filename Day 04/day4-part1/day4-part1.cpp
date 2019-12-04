#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, int& firstNumber, int& secondNumber)
{
	char aux{};
	in >> firstNumber >> aux >> secondNumber;
}


bool meetCriteria(int currNumber)
{
	bool firstRule = false;
	bool secondRule = true;

	while (currNumber > 9)
	{
		// Checking if we have two consecutive digits identical
		if (currNumber % 10 == currNumber / 10 % 10)
		{
			firstRule = true;
		}
		// Comparing two consecutive digits 
		if (currNumber % 10 < currNumber / 10 % 10)
		{
			secondRule = false;
		}
		currNumber = currNumber / 10;
	}

	// If the number - has two consecutive digits identical and
	//				 - has the digits sorted ascending
	// Than it meets the criteria
	return (firstRule && secondRule);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int firstNumber = 0, secondNumber = 0;
	int count = 0;

	readInput(in, firstNumber, secondNumber);

	// Parsing the numbers
	for (int currNumber = firstNumber; currNumber <= secondNumber; currNumber++)
	{
		// Counting the numbers that meet the criteria
		if (meetCriteria(currNumber))
		{
			count++;
		}
	}

	out << count;

	in.close();
	out.close();
}
