#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::fstream& out)
{
	std::vector<std::vector<int>> layers;
	std::vector<int>currLayer;
	int pixelsWide = 25, pixelsTall = 6;
	char currPixel{};

	while (!in.eof())
	{
		for (int it = 1; it <= pixelsWide * pixelsTall; it++)
		{
			in >> currPixel;
			currLayer.push_back(currPixel - '0');
		}

		layers.push_back(currLayer);
		currLayer.clear();
	}

	std::vector<int> image(pixelsWide * pixelsTall, 2);

	for (int pixel = 0; pixel < pixelsWide * pixelsTall; pixel++)
	{
		for (int layout = 0; layout < layers.size(); layout++)
		{
			if (layers[layout][pixel] == 2)
			{
				continue;
			}

			if (layers[layout][pixel] == 0)
			{
				image[pixel] = 0;
				break;
			}

			if (layers[layout][pixel] == 1)
			{
				image[pixel] = 1;
				break;
			}
		}
	}

	for (int pixel = 0; pixel < pixelsWide * pixelsTall; pixel++)
	{
		if (pixel % pixelsWide == 0)
		{
			out << "\n";
		}

		if (image[pixel] == 1)
		{
			out << "# ";
		}
		else
		{
			out << ". ";
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