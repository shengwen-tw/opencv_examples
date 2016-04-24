#include <iostream>
#include <cv.h>

#include "highgui.h"

using namespace std;
using namespace cv;

int main()
{
	char file_path[] = "polandball.jpg";
	char windows_name[] = "press any key to leave";

	/* Create window */
	cvNamedWindow(windows_name, 0);
	cvResizeWindow(windows_name, 300, 400);
	
	/* Load image */
	IplImage *image = cvLoadImage(file_path,1);
	cvShowImage(windows_name, image);

	//Delay until user press the button
	cvWaitKey(0);

	/* Distory the windows and release the image */
	cvDestroyWindow(windows_name);
	cvReleaseImage(&image);

	return 0;
}
