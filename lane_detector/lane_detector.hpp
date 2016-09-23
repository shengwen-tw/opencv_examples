#include <highgui.h>
#include <cv.h>

class LaneDetector {
	int threshold_h_min, threshold_h_max;
	int threshold_s_min, threshold_s_max;
	int threshold_v_min, threshold_v_max;

	public:
	LaneDetector() :
		threshold_h_min(0), threshold_h_max(256),
		threshold_s_min(0), threshold_s_max(256),
		threshold_v_min(0), threshold_v_max(256)
	{
		//Hardcode calibration
		threshold_h_min = 0, threshold_h_max = 75;
		threshold_s_min = 135, threshold_s_max = 175;
		threshold_v_min = 69, threshold_v_max = 226;
	}

	void tune_hsv_thresholding();
	void lane_detect(cv::Mat& image);

};
