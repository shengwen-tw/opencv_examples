#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat raw = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	Mat avg_blur1;
	Mat avg_blur2;

	Mat guass_blur_1;
	Mat guass_blur_2;

	blur(raw, avg_blur1, Size(3,3));
	blur(raw, avg_blur2, Size(5,5));
	
	GaussianBlur(raw, guass_blur_1, Size(3,3) ,0 ,0);
	GaussianBlur(raw, guass_blur_2, Size(5,5) ,0 ,0);

	imshow("raw", raw);
	imshow("average blur 3", avg_blur1);
	imshow("average blur 5", avg_blur2);
	imshow("gaussian blur 3", guass_blur_1);
	imshow("gaussian blur 5", guass_blur_2);

	waitKey(0);

	return 0;
}
