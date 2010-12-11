#include "/home/stef/CBprojects/CVHomeView/include/MyCVFilter.h"

// constructeur
MyCVFilter::MyCVFilter(IplImage* in)
{
	grayImage = cvCreateImage(cvSize(in->width,in->height), IPL_DEPTH_8U, 1);
	referenceImg = cvLoadImage("img.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	erodedImg = cvCreateImage(cvSize(in->width,in->height), IPL_DEPTH_8U, 1);
	differentiatedImg = cvCreateImage(cvSize(in->width,in->height), IPL_DEPTH_8U, 1);
}

void MyCVFilter::execute(IplImage* in, IplImage* out)
{
	CvScalar target_color[4] = { // dans l'ordre BGR
        {{   0,   0, 255,   0 }},  // rouge
        {{   0, 255,   0,   0 }},  // vert
        {{ 255,   0,   0,   0 }},  // bleu
        {{   255, 255, 255,   0 }}   // blanc
    };

	double value = 0.;
	std::stringstream valueStream;

	cvCvtColor(in,grayImage,CV_BGR2GRAY);
	referenceImg = cvLoadImage("img.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	cvAbsDiff(referenceImg,grayImage,differentiatedImg);
	cvThreshold(differentiatedImg,differentiatedImg,15,255,CV_THRESH_BINARY);
	cvErode(differentiatedImg,erodedImg, NULL, 2);

	for(int y = 0; y < in->height; ++y)
		for(int x = 0; x < in->width; ++x)
			value += ((unsigned char*)erodedImg->imageData)[x + y * erodedImg->widthStep];

	valueStream << value;

	if(value > 10000000)
	{
		CvFont font;
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,
					1.0,
					1.0,
					0,
					1,
					CV_AA);
		cvSaveImage("imgSaved.jpg",in);
		std::string buffer = valueStream.str();
		const char* valueSum = buffer.c_str();
		cvPutText(erodedImg,valueSum,cvPoint(10,50),&font,target_color[3]);
	}

	if(debug)
        cvCvtColor(erodedImg,out,CV_GRAY2BGR);

     cvReleaseImage(&referenceImg);
}

void MyCVFilter::setDebug(bool dbg)
{
    debug = dbg;
}


MyCVFilter::~MyCVFilter(){}
