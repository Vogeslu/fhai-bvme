#include "imageTools.h"
#include <iostream>

CImage ImageTools::gaussianFilter(CImage& image, int radius, bool high) {
	CImage fourierImage = image.FourierTransformation(false);

	Complex value;
	double temp;

	double real;
	double imag;

	int m = image.getHeight();
	int n = image.getWidth();

	for (int x = 0; x < m; x++) {
		for (int y = 0; y < n; y++) {
			double distance = pow(pow(x - m / 2, 2) + pow(y - n / 2, 2), 2);

			temp = exp(-distance / (2 * pow(radius, 2)));
			if (high) temp = 2 - temp;

			value = fourierImage.getComplexPointValue(x, y);

			real = value.real();
			imag = value.imag();

			value.real(real * temp);
			value.imag(imag * temp);

			fourierImage.setComplexPointValue(x, y, value);
		}
	}

	CImage output = fourierImage.FourierTransformation(true);

	return output;
}

CImage ImageTools::gaussianLowPassFilter(CImage& image, int radius) {
	return gaussianFilter(image, radius, false);
}

CImage ImageTools::gaussianHighPassFilter(CImage& image, int radius) {
	return gaussianFilter(image, radius, true);
}