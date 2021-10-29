#include "imageTools.h"
#include <iostream>

int ImageTools::getAverageGrayValue(CImage& image) {
	CImage clone = image.getGreyscaleImage();

	int combinedColors = 0;
	int total = 0;

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor color = image.getPointValue(x, y);

			combinedColors += color.getRed();
			total++;
		}

	return combinedColors / total;
}

int ImageTools::getIterativeTreshold(CImage& image) {
	int average = getAverageGrayValue(image);
	int newAverage = -1;

	do {
		if (newAverage != -1)
			average = newAverage;

		int combinedColorsAbove = 0;
		int combinedColorsBelow = 0;
		int totalAbove = 0;
		int totalBelow = 0;


		for (int x = 0; x < image.getHeight(); x++)
			for (int y = 0; y < image.getWidth(); y++) {
				CColor color = image.getPointValue(x, y);

				int value = color.getRed();

				if (value < average) {
					combinedColorsAbove += value;
					totalAbove++;
				}
				else {
					combinedColorsBelow += value;
					totalBelow++;
				}
			}

		int aboveValue = combinedColorsAbove / totalAbove;
		int belowValue = combinedColorsBelow / totalBelow;

		newAverage = (aboveValue + belowValue) / 2;
	} while (abs(average - newAverage) > 0);

	return newAverage;
}

CImage ImageTools::getBinaryImage(CImage& image) {
	return getBinaryImage(image, getIterativeTreshold(image));
}

CImage ImageTools::getLinearHistrogramImage(CImage& image) {
	CImage clone = image.getGreyscaleImage();

	int histogram[256] = { 0 };
	int outputHistogram[256] = { 0 };

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor color = image.getPointValue(x, y);

			histogram[color.getRed()] += 1;
		}

	for (int k = 0; k < 256; k++) {
		for (int i = 0; i < k; i++) {
			outputHistogram[k] += histogram[i];
		}
	}

	double widthHeight = (double) image.getWidth() * (double) image.getHeight();

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor color = clone.getPointValue(x, y);
			
			int value = 255 * ((double) outputHistogram[color.getGrey()] / widthHeight);

			color.setGrey(value);

			clone.setPointValue(x, y, color);
		}

	return clone;
}