#include "imageTools.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool sortValues(int i, int j) {
	return j > i;
}

CImage ImageTools::adaptiveMedianfilter(CImage& image, int sMax) {
	CImage greyscaleImage = image.getGreyscaleImage();
	CImage clone = image.getGreyscaleImage();

	for (int x = sMax; x < (greyscaleImage.getHeight() - sMax); x++) {
		for (int y = sMax; y < (greyscaleImage.getWidth() - sMax); y++) {
			int min;
			int max;
			int median;

			bool continueWithB = false;

			CColor point = clone.getPointValue(x, y);
			int pointValue = point.getGrey();

			for (int size = 1; size < sMax; size++) {
				vector<int> grid;
				
				for (int gX = x - size; gX <= x + size; gX++) {
					for (int gY = y - size; gY <= y + size; gY++) {
						grid.push_back(greyscaleImage.getPointValue(gX, gY).getGrey());
					}
				}

				sort(grid.begin(), grid.end(), sortValues);

				min = grid.at(0);
				max = grid.at(grid.size() - 1);

				median = grid.at(grid.size() / 2 - 1);

				int a1 = median - min;
				int a2 = median - max;

				if (a1 > 0 && a2 < 0) {
					continueWithB = true;
					break;
				}
			}

			if (!continueWithB)
				continue;

			int b1 = pointValue - min;
			int b2 = pointValue - max;

			if (b1 > 0 && b2 < 0)
				continue;

			point.setGrey(median);
			clone.setPointValue(x, y, point);
		}
	}

	return clone;
}