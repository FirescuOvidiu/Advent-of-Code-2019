#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<int>& sequence, int& messageOffset)
{
	std::string number;

	in >> number;
	for (int i = 0; i < number.size(); i++)
	{
		sequence.push_back(number[i] - '0');
	}

	for (int i = 1; i < 10000; i++)
	{
		for (int it = 0; it < number.size(); it++)
		{
			sequence.push_back(sequence[it]);
		}
	}
	
	for (int i = 0; i < 7; i++)
	{
		messageOffset = messageOffset * 10 + sequence[i];
	}
}


void calcSecondHalfOfOutput(std::vector<int>& sequence)
{
	std::vector<int> newSequence(sequence.size());
	int sizeSequence = sequence.size();
	int sum = 0;
	int phase = 0;

	while(phase<100)
	{
		// We can observe that all the digits from the second half of the sequence
		// are calculated as (the sum of digits from the last digit to the current digit) % 10
		sum = 0;
		for (int it = sizeSequence - 1; it >= sizeSequence / 2; it--)
		{
			sum += sequence[it];
			newSequence[it] = sum % 10;
		}
		sequence = newSequence;
		phase++;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> sequence;
	int messageOffset = 0;

	readInput(in, sequence, messageOffset);

	calcSecondHalfOfOutput(sequence);

	for (int it = messageOffset; it < messageOffset + 8; it++)
	{
		out << sequence[it];
	}

	in.close();
	out.close();
}