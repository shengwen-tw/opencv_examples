#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	VideoCapture cap(0);

	if(!cap.isOpened()){  
		return -1;
	}

	Size video_size = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
			      (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	VideoWriter writer;
	writer.open("log.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, video_size);

	Mat frame;
	while(cap.read(frame)){
		writer.write(frame);
		imshow("show image", frame);
		cv::waitKey(33);
	}

	return 0;
}
