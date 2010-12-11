#include <stdio.h>
#include <assert.h>
#include <QApplication>

#include </usr/include/opencv/cv.h>
#include </usr/include/opencv/highgui.h>

#include "include/Window.moc"

int main(int argc, char **argv) {
	CvCapture* camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage* image=cvQueryFrame(camera);
    assert(image);

	QApplication app(argc,argv);

	Window window(camera,image);

    window.show();
	int retval = app.exec();

	cvReleaseCapture(&camera);

	return retval;
}
