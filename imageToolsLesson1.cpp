#include "imageTools.h"

CImage ImageTools::getGrayscaleImage(CImage& image) {
	CImage clone(image.getHeight(), image.getWidth(), false);

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor originColor = image.getPointValue(x, y);
			CColor cloneColor = clone.getPointValue(x, y);

			int grayValue = (originColor.getRed() + originColor.getGreen() + originColor.getBlue()) / 3;

			cloneColor.setRed(grayValue);
			cloneColor.setGreen(grayValue);
			cloneColor.setBlue(grayValue);

			clone.setPointValue(x, y, cloneColor);
		}

	return clone;
}

CImage ImageTools::getBinaryImage(CImage& image, int treshold) {
	CImage clone(image.getHeight(), image.getWidth(), false);

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor originColor = image.getPointValue(x, y);
			CColor cloneColor = clone.getPointValue(x, y);

			int grayValue = (originColor.getRed() + originColor.getGreen() + originColor.getBlue()) / 3;
			int binaryColor = 0;

			if (grayValue >= treshold)
				binaryColor = 255;

			cloneColor.setRed(binaryColor);
			cloneColor.setGreen(binaryColor);
			cloneColor.setBlue(binaryColor);

			clone.setPointValue(x, y, cloneColor);
		}

	return clone;
}

ImageCoordinate ImageTools::getBrightestPoint(CImage& image) {
	ImageCoordinate brightestCoordinate;

	brightestCoordinate.x = 0;
	brightestCoordinate.y = 0;

	int brightestValue = -1;

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor originColor = image.getPointValue(x, y);

			int grayValue = (originColor.getRed() + originColor.getGreen() + originColor.getBlue()) / 3;

			if (grayValue > brightestValue) {
				brightestCoordinate.x = x;
				brightestCoordinate.y = y;
				brightestValue = grayValue;
			}
		}

	return brightestCoordinate;
}

ImageCoordinate ImageTools::getDarkestPoint(CImage& image) {
	ImageCoordinate darkestCoordinate;

	darkestCoordinate.x = 0;
	darkestCoordinate.y = 0;

	int darkestValue = 256;

	for (int x = 0; x < image.getHeight(); x++)
		for (int y = 0; y < image.getWidth(); y++) {
			CColor originColor = image.getPointValue(x, y);

			int grayValue = (originColor.getRed() + originColor.getGreen() + originColor.getBlue()) / 3;

			if (grayValue < darkestValue) {
				darkestCoordinate.x = x;
				darkestCoordinate.y = y;
				darkestValue = grayValue;
			}
		}

	return darkestCoordinate;
}

CImage ImageTools::highlightPoint(CImage& image, ImageCoordinate coordinates, int radius) {
	CImage grayscaleClone = image.getGreyscaleImage();

	CColor highlightColor = CColor(255, 0, 255);

	if(radius == 0)
		grayscaleClone.setPointValue(coordinates.x, coordinates.y, highlightColor);
	else {
		int width = grayscaleClone.getWidth();
		int height = grayscaleClone.getHeight();

		for (int x = -radius; x < radius; x++)
			for (int y = -radius; y < radius; y++) {
				int positionX = coordinates.x - x;
				int positionY = coordinates.y - y;

				if (positionX >= 0 && positionY >= 0 && positionX < height && positionY < width)
					grayscaleClone.setPointValue(positionX, positionY, highlightColor);
			}
	}

	return grayscaleClone;
}