#include "imageTools.h"

int smoothenMatrix[3][3] = {
	{ 1, 2, 1 },
	{ 2, 4, 2 },
	{ 1, 2, 1 }
};

CImage ImageTools::getSmoothenImage(CImage& image) {
	CImage greyscaleImage = image.getGreyscaleImage();
	CImage clone = image.getGreyscaleImage();

	for(int x = 1; x < image.getHeight() - 1; x++)
		for (int y = 1; y < image.getWidth() - 1; y++) {
			int upperValue = 0;
			int lowerValue = 0;

			for(int s = -1; s <= 1; s++)
				for (int t = -1; t <= 1; t++) {
					int color = greyscaleImage.getPointValue(x + s, y + t).getGrey();

					upperValue += smoothenMatrix[s + 1][t + 1] * color;
					lowerValue += smoothenMatrix[s + 1][t + 1];
				}

			int value = upperValue / lowerValue;

			CColor color = clone.getPointValue(x, y);

			color.setGrey(value);

			clone.setPointValue(x, y, color);
		}

	return clone;
}

CImage ImageTools::getSharpenImageLaplace(CImage& image, int c) {
	CImage greyscaleImage = image.getGreyscaleImage();
	CImage clone = image.getGreyscaleImage();


	for (int x = 1; x < image.getHeight() - 1; x++)
		for (int y = 1; y < image.getWidth() - 1; y++) {
			int centerGrey = greyscaleImage.getPointValue(x, y).getGrey();

			int laplace1 =
				greyscaleImage.getPointValue(x + 1, y).getGrey() +
				greyscaleImage.getPointValue(x - 1, y).getGrey() -
				2 * centerGrey;

			int laplace2 =
				greyscaleImage.getPointValue(x, y + 1).getGrey() +
				greyscaleImage.getPointValue(x, y - 1).getGrey() -
				2 * centerGrey;

			int value = centerGrey + c * (laplace1 + laplace2);

			CColor color = clone.getPointValue(x, y);
			
			color.setGrey(value);

			clone.setPointValue(x, y, color);
		}

	return clone;
}

CImage ImageTools::getSharpenImageUnsharpMask(CImage& image, int k) {
	CImage smoothenImage = getSmoothenImage(image);
	CImage clone = image.getGreyscaleImage();


	for (int x = 1; x < image.getHeight() - 1; x++)
		for (int y = 1; y < image.getWidth() - 1; y++) {
			int smoothenValue = smoothenImage.getPointValue(x, y).getGrey();

			CColor color = clone.getPointValue(x, y);

			int cloneValue = color.getGrey();

			int maskValue = cloneValue - smoothenValue;

			color.setGrey(cloneValue + k * maskValue);

			clone.setPointValue(x, y, color);
		}

	return clone;
}