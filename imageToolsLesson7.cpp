#include "imageTools.h"
#include <iostream>

int filterS1[3][3] = {
	{ 1, 2, 1 },
	{ 0, 0, 0 },
	{-1,-2,-1 }
};

int filterS2[3][3] = {
	{ 1, 0,-1 },
	{ 2, 0,-2 },
	{ 1, 0,-1 }
};

int filterS3[3][3] = {
	{-1,-2,-1 },
	{ 0, 0, 0 },
	{ 1, 2, 1 }
};

int filterS4[3][3] = {
	{-1, 0, 1 },
	{-2, 0, 2 },
	{-1, 0, 1 }
};

CImage getSmoothenImageWithSobel(CImage& original, CImage& clone, int direction) {
	for (int x = 1; x < original.getHeight() - 1; x++)
		for (int y = 1; y < original.getWidth() - 1; y++) {
			int sum = 0;

			for (int s = -1; s <= 1; s++)
				for (int t = -1; t <= 1; t++) {


					int color = original.getPointValue(x + s, y + t).getGrey();

					if (direction == 0) {
						sum += filterS1[s + 1][t + 1] * color;
					} else if (direction == 1) {
						sum += filterS2[s + 1][t + 1] * color;
					} else if (direction == 2) {
						sum += filterS3[s + 1][t + 1] * color;
					} else {
					sum += filterS4[s + 1][t + 1] * color;
					}
				}

			CColor color = clone.getPointValue(x, y);

			color.setGrey(sum);

			clone.setPointValue(x, y, color);
		}

	return clone;
}

CImage ImageTools::sobelfilter2Sides(CImage& image)
{
	CImage greyscaleImage = image.getGreyscaleImage();

	CImage smoothenS1(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);
	CImage smoothenS2(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);

	CImage output(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);

	getSmoothenImageWithSobel(greyscaleImage, smoothenS1, 0);
	getSmoothenImageWithSobel(greyscaleImage, smoothenS2, 1);

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			int greyS1 = smoothenS1.getPointValue(x, y).getGrey();
			int greyS2 = smoothenS2.getPointValue(x, y).getGrey();

			CColor outputColor = output.getPointValue(x, y);

			outputColor.setGrey((greyS1 + greyS2) / 2);

			output.setPointValue(x, y, outputColor);
		}

	smoothenS1.showImage("Sobelfilter Horizontal");
	smoothenS2.showImage("Sobelfilter Vertikal");

	return output;
}

CImage ImageTools::sobelfilter4Sides(CImage& image)
{
	CImage greyscaleImage = image.getGreyscaleImage();

	CImage smoothenS1(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);
	CImage smoothenS2(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);
	CImage smoothenS3(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);
	CImage smoothenS4(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);

	CImage output(greyscaleImage.getHeight(), greyscaleImage.getWidth(), true);

	getSmoothenImageWithSobel(greyscaleImage, smoothenS1, 0);
	getSmoothenImageWithSobel(greyscaleImage, smoothenS2, 1);
	getSmoothenImageWithSobel(greyscaleImage, smoothenS3, 2);
	getSmoothenImageWithSobel(greyscaleImage, smoothenS4, 3);

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			int greyS1 = smoothenS1.getPointValue(x, y).getGrey();
			int greyS2 = smoothenS2.getPointValue(x, y).getGrey();
			int greyS3 = smoothenS3.getPointValue(x, y).getGrey();
			int greyS4 = smoothenS4.getPointValue(x, y).getGrey();

			CColor outputColor = output.getPointValue(x, y);

			outputColor.setGrey((greyS1 + greyS2 + greyS3 + greyS4) / 4);

			output.setPointValue(x, y, outputColor);
		}

	smoothenS1.showImage("Sobelfilter Horizontal");
	smoothenS2.showImage("Sobelfilter Vertikal");
	smoothenS3.showImage("Sobelfilter Horizontal 2");
	smoothenS4.showImage("Sobelfilter Vertikal 2");

	return output;
}