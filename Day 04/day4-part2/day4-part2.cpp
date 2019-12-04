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
	int lastDigit = 0;

	while (currNumber > 9)
	{
		// Checking if we have exactly two consecutive digits for first two digits of the number
		// Example: currNumber = abc we check if b==a and b!=c 
		// where b = currNumber % 10, a = currNumber / 10 % 10 and c = lastDigit
		if (currNumber < 100)
		{
			if ((currNumber % 10 == currNumber / 10 % 10) && (currNumber % 10 != lastDigit))
			{
				firstRule = true;
			}
		}
		else
		{
			// Checking if we have exactly two consecutive digits for last two digits of the number
		    // Example currNumber = abcdef we check if f==e and if f!=d 
		    // where f = currNumber % 10, e = currNumber / 10 % 10 and d = currNumber / 100 % 10
			if (currNumber >= 172930)
			{
				if ((currNumber % 10 == currNumber / 10 % 10) && (currNumber % 10 != currNumber / 100 % 10))
				{
					firstRule = true;
				}
			}
			else
			{
				// Checking if we have exactly two consecutive digits for every interior two digits of the number
			    // Example currNumber = abcdef we check if c==b and c!=a and c!=e 
			    // where c = currNumber % 10, b = currNumber / 10 % 10, d = currNumber / 100 % 10 and e = lastDigit
				if ((currNumber % 10 == currNumber / 10 % 10) && (currNumber % 10 != currNumber / 100 % 10) && (currNumber % 10 != lastDigit))
				{
					firstRule = true;
				}
			}
		}

		// Comparing two consecutive digits 
		if (currNumber % 10 < currNumber / 10 % 10)
		{
			secondRule = false;
		}

		lastDigit = currNumber % 10;
		currNumber = currNumber / 10;
	}
	// If the number - has exactly two consecutive digits identical 
	//				 - has the digits sorted ascending
	// Than it meets the criteria
	if (firstRule && secondRule)
	{
		return true;
	}
	return false;
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