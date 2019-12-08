#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::fstream& out)
{
	std::vector<std::vector<int>> layers;
	std::vector<int>currLayer;
	int pixelsWide = 25, pixelsTall = 6;
	char aux{};

	while (!in.eof())
	{
		for (int i = 1; i <= pixelsWide * pixelsTall; i++)
		{
			in >> aux;
			currLayer.push_back(aux - '0');
		}

		layers.push_back(currLayer);
		currLayer.clear();
	}

	std::vector<int> image;
	for (int pixel = 0; pixel < pixelsWide * pixelsTall; pixel++)
	{
		for (int layout = 0; layout < layers.size(); layout++)
		{
			if (layers[layout][pixel] == 0)
			{
				image.push_back(0);
				break;
			}
			if (layers[layout][pixel] == 1)
			{
				image.push_back(1);
				break;
			}
		}
	}

	for (int pixel = 0; pixel < pixelsTall* pixelsWide; pixel++)
	{
		if (pixel % 25 == 0)
		{
			out << "\n";
		}

		if (image[pixel] == 0)
		{
			out << ". ";
		}
		else
		{
			out << "# ";
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