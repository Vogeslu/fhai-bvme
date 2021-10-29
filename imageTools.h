#pragma once
#include "CImage.h"

using namespace bvme;

struct ImageCoordinate {
	int x;
	int y;
};

class ImageTools {
	public:

		// Übung 1

		static CImage getGrayscaleImage(CImage& image);
		static CImage getBinaryImage(CImage& image, int treshold);

		static ImageCoordinate getBrightestPoint(CImage& image);
		static ImageCoordinate getDarkestPoint(CImage& image);

		static CImage highlightPoint(CImage& image, ImageCoordinate coordinates, int radius);
		
		// Übung 2

		static int getAverageGrayValue(CImage& image);
		static int getIterativeTreshold(CImage& image);

		static CImage getBinaryImage(CImage& image);

		static CImage getLinearHistrogramImage(CImage& image);

		// Übung 3

		static CImage getSmoothenImage(CImage& image);
		static CImage getSharpenImageLaplace(CImage& image, int c);
		static CImage getSharpenImageUnsharpMask(CImage& image, int k);
};