#include "../../AOCHeaders/stdafx.h"


class reaction
{
public:
	std::vector<std::string> inputChemical;
	std::vector<long long> inputQuant;
	std::string outputChemical;
	long long outputQuant;
};


class neededChemical
{
public:
	neededChemical(const std::string outputChemical = "", long long outputQuant = 0) : outputChemical(outputChemical), outputQuant(outputQuant) {}
public:
	std::string outputChemical;
	long long outputQuant;
};


void readInput(std::fstream& in, std::vector<reaction>& reactions)
{
	reaction currReaction;
	long long inputQuant = 0;
	std::string aux;

	while (in >> inputQuant)
	{
		currReaction.inputQuant.push_back(inputQuant);
		while (true)
		{
			in >> aux;
			if (aux[aux.size() - 1] == ',')
			{
				aux.erase(aux.end() - 1);
			}
			currReaction.inputChemical.push_back(aux);

			in >> aux;
			if (aux == "=>")
			{
				break;
			}
			else
			{
				inputQuant = stoi(aux);
			}
			currReaction.inputQuant.push_back(inputQuant);
		}
		in >> currReaction.outputQuant;
		in >> currReaction.outputChemical;

		reactions.push_back(currReaction);
		currReaction.inputQuant.clear();
		currReaction.inputChemical.clear();
	}

}

struct comparer {
	bool operator() (const neededChemical& nc1, const neededChemical& nc2) const
	{
		return nc1.outputChemical < nc2.outputChemical;
	}
};


long long produceFuel(const std::vector<reaction>& react, const long long input)
{
	std::queue<neededChemical> neededChemicals;
	std::set<neededChemical, comparer> leftovers;
	std::set<neededChemical, comparer>::iterator findLeftover;
	neededChemical currNeededChemical;
	long long countORE = 0, auxOutputQuant = 0, quantNeeded;

	neededChemicals.push(neededChemical("FUEL", input));

	while (!neededChemicals.empty())
	{
		currNeededChemical = neededChemicals.front();
		neededChemicals.pop();


		findLeftover = leftovers.find(currNeededChemical);

		if (findLeftover != leftovers.end())
		{
			if (currNeededChemical.outputQuant >= (*findLeftover).outputQuant)
			{
				currNeededChemical.outputQuant -= (*findLeftover).outputQuant;
				leftovers.erase(findLeftover);
			}
			else
			{
				auxOutputQuant = (*findLeftover).outputQuant;
				leftovers.erase(findLeftover);
				leftovers.insert(neededChemical(currNeededChemical.outputChemical, auxOutputQuant - currNeededChemical.outputQuant));
				continue;
			}
		}


		for (int currReact = 0; currReact < react.size(); currReact++)
		{
			if (currNeededChemical.outputChemical == react[currReact].outputChemical)
			{
				quantNeeded = currNeededChemical.outputQuant / react[currReact].outputQuant;
				while (currNeededChemical.outputQuant > react[currReact].outputQuant* quantNeeded)
				{
					quantNeeded++;
				}

				if (react[currReact].outputQuant * quantNeeded > currNeededChemical.outputQuant)
				{
					findLeftover = leftovers.find(currNeededChemical);

					if (findLeftover != leftovers.end())
					{
						auxOutputQuant = (*findLeftover).outputQuant;
						leftovers.erase(findLeftover);
						leftovers.insert(neededChemical(currNeededChemical.outputChemical, auxOutputQuant + react[currReact].outputQuant * quantNeeded - currNeededChemical.outputQuant));
					}
					else
					{
						leftovers.insert(neededChemical(currNeededChemical.outputChemical, react[currReact].outputQuant * quantNeeded - currNeededChemical.outputQuant));
					}
				}

				for (int currInputChemical = 0; currInputChemical < react[currReact].inputChemical.size(); currInputChemical++)
				{
					neededChemicals.push(neededChemical(react[currReact].inputChemical[currInputChemical], quantNeeded * react[currReact].inputQuant[currInputChemical]));
					if (react[currReact].inputChemical[currInputChemical] == "ORE")
					{
						countORE += quantNeeded * react[currReact].inputQuant[currInputChemical];
					}
				}
				break;
			}
		}
	}

	return countORE;
}


long long binarySearch(const std::vector<reaction>& reactions, const long long input)
{
	long long first = 0;
	long long last = input;
	long long middle = first + (last - first) / 2;

	while (first < last)
	{
		if (produceFuel(reactions, middle) < input)
		{
			first = middle + 1;
		}
		else
		{
			last = middle - 1;
		}
		middle = first + (last - first) / 2;
	}

	return middle;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<reaction> reactions;
	long long input = 1000000000000;

	readInput(in, reactions);
	out << binarySearch(reactions, input);

	in.close();
	out.close();
}