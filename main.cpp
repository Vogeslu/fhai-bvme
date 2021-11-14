#include "imageTools.h"

using namespace bvme;

int main()
{
	// relativ ausgehend von main.cpp, absolute Pfadangaben sind auch möglich
	CImage image("Images/schmetterling_saltpepper.bmp");

	CImage result2 = ImageTools::adaptiveMedianfilter(image, 2);
	CImage result4 = ImageTools::adaptiveMedianfilter(image, 4);
	CImage result8 = ImageTools::adaptiveMedianfilter(image, 8);
	CImage result12 = ImageTools::adaptiveMedianfilter(image, 12);

	image.showImage("Original");
	result2.showImage("Adaptiver Medianfilter (sMax: 5)");
	result4.showImage("Adaptiver Medianfilter (sMax: 9)");
	result8.showImage("Adaptiver Medianfilter (sMax: 17)");
	result12.showImage("Adaptiver Medianfilter (sMax: 25)");

	system("pause");
	return 0;
}