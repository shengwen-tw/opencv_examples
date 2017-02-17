#include <sstream>
#include <string>
#include <iostream>
#include <highgui.h>
#include <cv.h>

#include "object_tracking.h"

using namespace cv;

#if USE_CALIBRATED_SETTING
int h_min_threshold = FINE_CALIBRATED_H_MIN;
int h_max_threshold = FINE_CALIBRATED_H_MAX;
int s_min_threshold = FINE_CALIBRATED_S_MIN;
int s_max_threshold = FINE_CALIBRATED_S_MAX;
int v_min_threshold = FINE_CALIBRATED_V_MIN;
int v_max_threshold = FINE_CALIBRATED_V_MAX;
#else
int h_min_threshold = 0;
int h_max_threshold = 256;
int s_min_threshold = 0;
int s_max_threshold = 256;
int v_min_threshold = 0;
int v_max_threshold = 256;
#endif

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;

//minimum and maximum object area
const int MIN_OBJECT_AREA = 20 * 20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1.5;

//names that will appear at the top of each window
const string original_window = "Original Image";
const string hsv_window = "HSV Image";
const string threshold_window = "Thresholded Image";
const string morphological_window = "After Morphological Operations";
const string trackbar_window = "Trackbars";

void on_trackbar(int, void *)
{
	//This function gets called whenever a trackbar position is changed
}

string intToString(int number)
{
	std::stringstream str;
	str << number;
	return str.str();
}

void create_trackbars()
{
	//create window for trackbars
	namedWindow(trackbar_window, 0);
	
	//create trackbars and insert them into window
	createTrackbar("H_MIN", trackbar_window, &h_min_threshold, 256, on_trackbar);
	createTrackbar("H_MAX", trackbar_window, &h_max_threshold, 256, on_trackbar);
	createTrackbar("S_MIN", trackbar_window, &s_min_threshold, 256, on_trackbar);
	createTrackbar("S_MAX", trackbar_window, &s_max_threshold, 256, on_trackbar);
	createTrackbar("V_MIN", trackbar_window, &v_min_threshold, 256, on_trackbar);
	createTrackbar("V_MAX", trackbar_window, &v_max_threshold, 256, on_trackbar);
}

/* Draw a crosshair on the tracked object */
void draw_object_location(int x, int y, Mat &frame)
{
	/* Use if-else statements to prevent memory errors from writing off the screen 
	 * ie. (-25,-25) is not within the window! */

	circle(frame, Point(x,y), 20, Scalar(0, 255, 0), 2);

	if(y - 25 > 0) {
    		line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
	} else {
		line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
	}

	if(y + 25 < FRAME_HEIGHT) {
		line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
	} else {
		line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
	}

	if(x - 25 > 0) {
		line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
	} else {
		line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
	}

	if(x + 25 < FRAME_WIDTH) {
		line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
	} else {
		line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);
	}

	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
}

void morphological_filter(Mat &thresh)
{
	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3,3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8,8));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);

	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
}

void track_filtered_object(int &x, int &y, Mat threshold, Mat &cameraFeed)
{
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();

        	//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if(numObjects < MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
					refArea = area;
				} else {
					objectFound = false;
				}
			}

			//Draw object location if found the object
			if(objectFound == true){
				putText(cameraFeed, "Tracking Object", Point(0,50), 2, 1, Scalar(0,255,0), 2);
				draw_object_location(x , y, cameraFeed);
			}

		} else {
			putText(cameraFeed,"TOO MUCH NOISE! ADJUST THE FILTER!",Point(0,50),1,2,Scalar(0,0,255),2);
		}
	}
}
int main(int argc, char* argv[])
{
	Mat cameraFeed; //Matrix to store each frame of the webcam feed
	Mat HSV;        //matrix storage for HSV image
	Mat threshold;  //matrix storage for binary threshold image

	int x = 0, y = 0; //(x, y) location of the object

	/* Enable the camera */
	VideoCapture capture;
	capture.open(0);

	/* set height and width of capture frame */
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	create_trackbars(); //create slider bars for HSV filtering

	while(1){
		/* Store image to matrix */
		capture.read(cameraFeed);

		/* Convert frame from BGR to HSV colorspace */
		cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
		
		/* HSV image thresholding */
		inRange(
			HSV,
			Scalar(h_min_threshold, s_min_threshold, v_min_threshold),
			Scalar(h_max_threshold, s_max_threshold, v_max_threshold),
			threshold
		);
		
#if USE_MORPHOLOGICAL_FILTER
		/* Perform morphological operations on thresholded image to eliminate noise
		 * and emphasize the filtered object(s) */
		morphological_filter(threshold);
#endif

#if ENABLE_OBJECT_TRACKING
		track_filtered_object(x, y, threshold, cameraFeed);
#endif

		//Show frame on windows 
		imshow(threshold_window, threshold);
		imshow(original_window, cameraFeed);
		imshow(hsv_window, HSV);

		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		waitKey(30);
	}

	return 0;
}
