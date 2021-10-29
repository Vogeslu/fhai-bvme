#include "imageTools.h"

using namespace bvme;

int main()
{
	// relativ ausgehend von main.cpp, absolute Pfadangaben sind auch m�glich
	CImage imageRose("Images/mond.bmp");

	CImage smoothenImage = ImageTools::getSharpenImageUnsharpMask(imageRose, 2);

	imageRose.showImage();
	smoothenImage.showImage();

	system("pause");
	return 0;
}