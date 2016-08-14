#include <iostream>
#include <highgui.h>
#include <cv.h>
#include <raspicam/raspicam_cv.h>

using namespace std;

int main()
{
	raspicam::RaspiCam_Cv camera;

	if(!camera.open()) {
		cout << "failed to open pi camera!" << endl;
		return 0;
	}

	cv::Mat frame;

	while(1) {
		camera.grab();
		camera.retrieve(frame);

		cv::imshow("pi camera", frame);			

		/* Leave if press any key */	
		if(cvWaitKey(1) != -1) {
			break;
		}
	}

	camera.release();

	return 0;
}
