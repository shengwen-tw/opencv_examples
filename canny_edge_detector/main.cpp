#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat raw = imread("football.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat canny;

	double low_threshold = 50, up_threshold = 150;

	Canny(raw, canny, 50, 150, 3);

	imshow("canny image", canny);

	waitKey(0);

	return 0;
}

