#include "imageTools.h"

CImage ImageTools::getLinearHistogramImageForColorChannel(CImage& image, int channel)
{
	CImage clone = image.getGreyscaleImage();

	int histogram[256] = { 0 };
	int outputHistogram[256] = { 0 };

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor color = image.getPointValue(x, y);

			if(channel == 0)
				histogram[color.getRed()] += 1;
			else if(channel == 1)
				histogram[color.getGreen()] += 1;
			else
				histogram[color.getBlue()] += 1;
		}

	for (int k = 0; k < 256; k++) {
		for (int i = 0; i < k; i++) {
			outputHistogram[k] += histogram[i];
		}
	}

	double widthHeight = (double)image.getWidth() * (double)image.getHeight();

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor color = clone.getPointValue(x, y);

			int value = 255 * ((double)outputHistogram[color.getGrey()] / widthHeight);

			color.setGrey(value);

			clone.setPointValue(x, y, color);
		}

	return clone;
}

CImage ImageTools::getLinearHistogramImageRGB(CImage& image)
{
	CImage clone(image.getHeight(), image.getWidth(), false);

	double widthHeight = (double)image.getWidth() * (double)image.getHeight();

	CImage redHistogram = getLinearHistogramImageForColorChannel(image, 0);
	CImage greenHistogram = getLinearHistogramImageForColorChannel(image, 1);
	CImage blueHistogram = getLinearHistogramImageForColorChannel(image, 2);

	redHistogram.showImage("red");
	greenHistogram.showImage("green");
	blueHistogram.showImage("blue");
	
	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor cloneColor = clone.getPointValue(x, y);

			int redValue = redHistogram.getPointValue(x, y).getGrey();
			int greenValue = greenHistogram.getPointValue(x, y).getGrey();
			int blueValue = blueHistogram.getPointValue(x, y).getGrey();

			cloneColor.setRed(redValue);
			cloneColor.setGreen(greenValue);
			cloneColor.setBlue(blueValue);

			clone.setPointValue(x, y, cloneColor);
		}

	return clone;
}