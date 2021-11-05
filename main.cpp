#include "imageTools.h"

using namespace bvme;

int main()
{
	// relativ ausgehend von main.cpp, absolute Pfadangaben sind auch möglich
	CImage imageRose("Images/rose_fourier.bmp");
	CImage imageRoseGrey = imageRose.getGreyscaleImage();

	CImage result1 = ImageTools::gaussianHighPassFilter(imageRoseGrey, 240);
	CImage result2 = ImageTools::gaussianLowPassFilter(imageRoseGrey, 240);

	imageRoseGrey.showImage("Graubild");
	result1.showImage("Hochpassfilter");
	result2.showImage("Tiefpassfilter");

	system("pause");
	return 0;
}