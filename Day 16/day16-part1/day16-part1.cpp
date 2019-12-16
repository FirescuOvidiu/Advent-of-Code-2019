#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<int>& sequence)
{
	std::string number;

	in >> number;
	for (int i = 0; i < number.size(); i++)
	{
		sequence.push_back(number[i] - '0');
	}
}


void FFTAlgorithm(std::vector<int>& sequence, const std::vector<int>& basePattern)
{
	std::vector<int> newSequence(sequence.size());
	std::vector<int> pattern;
	int it = 1, sum = 0, phase = 0;

	while (phase < 100)
	{
		for (int digit = 0; digit < sequence.size(); digit++)
		{
			// New pattern
			pattern.clear();
			for (int itBasePattern = 0; itBasePattern < basePattern.size(); itBasePattern++)
			{
				for (int it = 0; it <= digit; it++)
				{
					pattern.push_back(basePattern[itBasePattern]);
				}
			}

			sum = 0;
			for (int currDigit = digit; currDigit < sequence.size(); currDigit++)
			{
				it = (currDigit + 1) % pattern.size();
				sum += sequence[currDigit] * pattern[it++];
			}
			newSequence[digit] = abs(sum) % 10;
		}
		sequence = newSequence;
		phase++;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<int> basePattern{ 0,1,0,-1 };
	std::vector<int> sequence;
	
	readInput(in, sequence);

	FFTAlgorithm(sequence, basePattern);

	for (int it = 0; it < 8; it++)
	{
		out << sequence[it];
	}

	in.close();
	out.close();
}