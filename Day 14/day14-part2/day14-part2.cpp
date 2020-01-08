#include "../../AOCHeaders/stdafx.h"


class chemical
{
public:
	chemical(const std::string name = "", long long quant = 0) : name(name), quant(quant) {}

	bool operator<(const chemical& c) const
	{
		return this->name < c.name;
	}

public:
	std::string name;
	long long quant;
};


class reaction
{
public:
	bool operator<(const reaction& r) const
	{
		return output.name < r.output.name;
	}

public:
	std::vector<chemical> input;
	chemical output;
};


void readInput(std::fstream& in, std::set<reaction>& reactions)
{
	chemical currChemical;
	reaction currReaction;
	std::string aux;

	while (in >> aux)
	{
		while (aux != "=>")
		{
			currChemical.quant = stoll(aux);

			in >> aux;
			if (aux[aux.size() - 1] == ',')
			{
				aux.erase(aux.end() - 1);
			}
			currChemical.name = aux;
			currReaction.input.push_back(currChemical);

			in >> aux;
		}
		in >> currReaction.output.quant;
		in >> currReaction.output.name;

		reactions.insert(currReaction);

		currReaction.input.clear();
	}

}


long long produceFuel(const std::set<reaction>& react, const long long input)
{
	std::queue<chemical> neededChemical;
	std::set<chemical> leftovers;
	std::set<chemical>::iterator findLeftover;
	std::set<reaction>::iterator currReact;
	chemical currNC;
	reaction auxReaction;
	long long countORE = 0, auxOutputQuant = 0, quantNeeded = 0;

	neededChemical.push(chemical("FUEL", input));

	while (!neededChemical.empty())
	{
		currNC = neededChemical.front();
		neededChemical.pop();

		findLeftover = leftovers.find(currNC);

		// If we find leftover chemical that can be used then
		if (findLeftover != leftovers.end())
		{
			// We check if we have less or more leftover than we actually need
			// Depending on which we update the leftovers and the current chemical
			if (currNC.quant >= (*findLeftover).quant)
			{
				currNC.quant -= (*findLeftover).quant;
				leftovers.erase(findLeftover);
			}
			else
			{
				auxOutputQuant = (*findLeftover).quant;
				leftovers.erase(findLeftover);
				leftovers.insert(chemical(currNC.name, auxOutputQuant - currNC.quant));
				continue;
			}
		}

		// Finding the needed chemical in the reactions
		auxReaction.output.name = currNC.name;
		currReact = react.find(auxReaction);

		// Calculate the quantity needed 
		quantNeeded = currNC.quant / (*currReact).output.quant;
		while (currNC.quant > (*currReact).output.quant* quantNeeded)
		{
			quantNeeded++;
		}

		// Checking if we will have leftovers after making this chemical
		// (*currReact).output.quant * quantNeeded represents the chemical quantity that we will make
		if ((*currReact).output.quant * quantNeeded > currNC.quant)
		{
			findLeftover = leftovers.find(currNC);

			if (findLeftover != leftovers.end())
			{
				auxOutputQuant = (*findLeftover).quant;
				leftovers.erase(findLeftover);
				leftovers.insert(chemical(currNC.name, auxOutputQuant + (*currReact).output.quant * quantNeeded - currNC.quant));
			}
			else
			{
				leftovers.insert(chemical(currNC.name, (*currReact).output.quant * quantNeeded - currNC.quant));
			}
		}

		// Adding the input chemical needed 
		for (const auto& inputReact : (*currReact).input)
		{
			if (inputReact.name == "ORE")
			{
				countORE += (long long)quantNeeded * inputReact.quant;
			}
			else
			{
				neededChemical.push(chemical(inputReact.name, quantNeeded * inputReact.quant));
			}
		}
	}

	return countORE;
}


long long binarySearch(const std::set<reaction>& reactions, const long long input)
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
	std::set<reaction> reactions;
	long long input = 1000000000000;

	readInput(in, reactions);
	out << binarySearch(reactions, input);

	in.close();
	out.close();
}