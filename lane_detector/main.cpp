#include <highgui.h>
#include <cv.h>

#include "lane_detector.hpp"

using namespace cv;

void on_trackbar(int, void *)
{
}

void LaneDetector::tune_hsv_thresholding()
{
	//create window for trackbars
	namedWindow("tune hsv", 0);
	
	//create trackbars and insert them into window
	createTrackbar("H_MIN", "tune hsv", &threshold_h_min, 256, on_trackbar);
	createTrackbar("H_MAX", "tune hsv", &threshold_h_max, 256, on_trackbar);
	createTrackbar("S_MIN", "tune hsv", &threshold_s_min, 256, on_trackbar);
	createTrackbar("S_MAX", "tune hsv", &threshold_s_max, 256, on_trackbar);
	createTrackbar("V_MIN", "tune hsv", &threshold_v_min, 256, on_trackbar);
	createTrackbar("V_MAX", "tune hsv", &threshold_v_max, 256, on_trackbar);
}

void LaneDetector::lane_detect(cv::Mat& image)
{
	cv::Mat hsv_image, canny_image, threshold_image, hough_image;

	//cv::imshow("hsv image", hsv_image);

	Canny(image, canny_image, 100, 200, 3);

	cv::Mat test;
	test = Scalar::all(0); 

	image.copyTo(test, canny_image);

	cv::imshow("original rgb image", test);

	cv::imshow("Canny image", canny_image);

	cv::cvtColor(test, hsv_image, COLOR_BGR2HSV);

	cv::inRange(
		hsv_image,
		Scalar(threshold_h_min, threshold_s_min, threshold_v_min),
		Scalar(threshold_h_max, threshold_s_max, threshold_v_max),
		threshold_image
	);

	//blur(threshold_image, hough_image, Size(3, 3));

	threshold_image.copyTo(hough_image);

	std::vector<Vec2f> lines;
	HoughLines(hough_image, lines, 1, CV_PI/180, 50);

	for(size_t i = 0; i < lines.size(); i++ ) {  
		float rho = lines[i][0], theta = lines[i][1];  
		Point pt1, pt2;  
		double a = cos(theta), b = sin(theta);  
		double x0 = a*rho, y0 = b*rho;  
		pt1.x = cvRound(x0 + 1000 * (-b));  
		pt1.y = cvRound(y0 + 1000 * (a));  
		pt2.x = cvRound(x0 - 1000 * (-b));  
		pt2.y = cvRound(y0 - 1000 * (a));  
		line(hough_image, pt1, pt2, Scalar(55,15,195), 1, CV_AA);  
	} 

	cv::imshow("threshold image", threshold_image);	
	cv::imshow("hough tranform image", hough_image);
}

int main()
{
	cv::Mat frame;
	cv::VideoCapture cap(0);

	LaneDetector lane_detector;

	if(cap.isOpened() != true) {
        	return -1;
	}

	lane_detector.tune_hsv_thresholding();

	while(cap.read(frame)){   
		cv::Mat src = cv::Mat(frame);

		lane_detector.lane_detect(frame);

		cv::waitKey(30);
	}

	return 0;
}
