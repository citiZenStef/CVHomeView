#ifndef DEF_WINDOW
#define DEF_WINDOW

#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QSlider>
#include <QCheckBox>
#include <QProgressBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "Window.h"
#include "MyCVFilter.h"


#include </usr/include/opencv/cv.h>
#include </usr/include/opencv/cxcore.h>
#include </usr/include/opencv/cvaux.h>
#include </usr/include/opencv/highgui.h>

using namespace std;

class Window : public QWidget
{
	Q_OBJECT

	public:
	Window(CvCapture *cam, IplImage* CVImage);
	~Window();

	public slots:
	void quitDial();
	void savePicDial();
	void debugChkB();

	signals:
	void Iquit();

	private:
	QHBoxLayout* m_layout;
	QVBoxLayout* m_layoutButtons;
	QPushButton* m_buttonSavePic;
	QPushButton* m_buttonQuit;
	QCheckBox* m_debug;
	QOpenCVWidget* QtIn;
	QOpenCVWidget* QtOut;
    CvCapture *camera;
	IplImage* in;
	IplImage* out;
	MyCVFilter* dude;
	bool debug;
	int streamId;
	int refCaptId;

	protected:
    void timerEvent(QTimerEvent*);
};

#endif
