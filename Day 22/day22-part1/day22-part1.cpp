#include "../../AOCHeaders/stdafx.h"


void deal(std::vector<int>& v)
{
	std::reverse(v.begin(), v.end());
}


void cut(std::vector<int>& deck, int cut)
{
	cut = (deck.size() + cut) % deck.size();
	std::rotate(deck.begin(), deck.begin() + cut, deck.end());
}


void increment(std::vector<int>& deck, const int incr)
{
	std::vector<int> newDeck(deck.size());
	int pos = 0;

	for (int i = 0; i < deck.size(); i++)
	{
		newDeck[pos] = deck[i];
		pos = (pos + incr) % deck.size();
	}

	deck = newDeck;
}


void readInput(std::fstream& in, std::fstream& out)
{
	std::vector<int> deck(10007);
	for (int i = 0; i < deck.size(); i++)
	{
		deck[i] = i;
	}

	std::string op;
	int number{ 0 };

	while (in >> op)
	{
		if (op == "cut")
		{
			in >> number;
			cut(deck, number);
		}
		else
		{
			in >> op >> op;
			if (op == "increment")
			{
				in >> number;
				increment(deck, number);
			}
			else
			{
				in >> op;
				deal(deck);
			}
		}
	}

	for (int pos = 0; pos < deck.size(); pos++)
	{
		if (deck[pos] == 2019)
		{
			out << pos;
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	readInput(in, out);

	in.close();
	out.close();
}