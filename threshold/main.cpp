#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	cv::Mat raw = imread("bird.jpg");
	cv::Mat threshold_image;

	if (raw.empty()) {
		std::cout << "> This image is empty" << std::endl;
		return 1;
	}

	cv::inRange(raw, cv::Scalar(0, 125, 0), cv::Scalar(255, 200, 255), threshold_image);
	cv::imshow("threshold image", threshold_image);

	waitKey(0);

	return 0;
}

