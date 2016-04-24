#include <iostream>
#include <cv.h>

#include "highgui.h"

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("polandball.jpg");
	Mat dst;

	/* Gaussian filter */
	GaussianBlur(src,dst,Size(5,5),0,0);
	imwrite("output/gauss.jpg",dst);

	/* Median filter */
	blur(src,dst,Size(3,3),Point(-1,-1));
	imwrite("mean.jpg",dst);

	return 0;
}

