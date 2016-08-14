#include <highgui.h>
#include <cv.h>

int main()
{
	IplImage* frame;
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);

	cvNamedWindow("PI Camera", CV_WINDOW_AUTOSIZE);

	while(frame = cvQueryFrame(capture)) {
		cvShowImage("PI Camera", frame);	
		
		if(cvWaitKey(33) == 27) {
			break;
		}
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("PI Camera");

	return 0;
}
