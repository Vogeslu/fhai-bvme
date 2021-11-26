#include "imageTools.h"

using namespace bvme;

int main()
{
	// relativ ausgehend von main.cpp, absolute Pfadangaben sind auch möglich
	CImage imageRose("Images/rose.bmp");

	CImage result1 = ImageTools::sobelfilter2Sides(imageRose);

	result1.showImage("Sobelfilter Ergebnis");

	system("pause");
	return 0;
}