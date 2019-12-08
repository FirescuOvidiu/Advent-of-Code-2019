#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::fstream& out)
{
	int pixelsWide = 25, pixelsTall = 6;
	int currLayout = 0, lengthLayout = pixelsTall * pixelsWide;
	std::string pixels;

	in >> pixels;

	int numberLayouts = pixels.size() / lengthLayout;

	for (int posPixel = 0; posPixel < lengthLayout; posPixel++)
	{
		if (posPixel % pixelsWide == 0)
		{
			out << "\n";
		}

		currLayout = 0;
		while ((currLayout < numberLayouts) && (pixels[currLayout * lengthLayout + posPixel] == '2'))
		{
			currLayout++;
		}
		
		if (currLayout == numberLayouts)
		{
			// In case a pixel is transparent
			out << "  ";
		}
		else
		{
			if (pixels[currLayout * lengthLayout + posPixel] == '1')
			{
				out << "# ";
			}
			else
			{
				out << ". ";
			}
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