#include </usr/include/opencv/cv.h>
#include </usr/include/opencv/cxcore.h>
#include </usr/include/opencv/cvaux.h>
#include </usr/include/opencv/highgui.h>
#include <iostream>

using namespace std;


class MyCVFilter
{
	public:
	MyCVFilter(IplImage* in);
	void setDebug(bool dbg);
	void execute(IplImage* in, IplImage* out);
	~MyCVFilter();
	private:
	IplImage* grayImage;
	IplImage* referenceImg;
	IplImage* erodedImg;
	IplImage* differentiatedImg;
	bool debug;
};
