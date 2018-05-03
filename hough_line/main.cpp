#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main()
{
	Mat src = imread("building.jpg", 0);
 
	Mat dst, cdst;
	Canny(src, dst, 10, 240, 3); 
	cvtColor(dst, cdst, CV_GRAY2BGR); 
 
	vector<Vec2f> lines;
	// detect lines
	HoughLines(dst, lines, 1, CV_PI/180, 70, 0, 0 );
 
	// draw lines
	for( size_t i = 0; i < lines.size(); i++ )
		{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( cdst, pt1, pt2, Scalar(0,0,255), 1, CV_AA);
	}
 
	imshow("source", src);
	imshow("detected lines", cdst);
 
	waitKey();
	return 0;
}
