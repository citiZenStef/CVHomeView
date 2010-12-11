#include "/home/stef/CBprojects/CVHomeView/include/Window.h"


Window::Window(CvCapture* cam, IplImage* CVImage) : QWidget()
{
	m_layout = new QHBoxLayout;
	m_layoutButtons = new QVBoxLayout;
	m_buttonQuit = new QPushButton("Quit",this);
	m_buttonSavePic = new QPushButton("Save picture",this);
	m_debug = new QCheckBox("Debug",this);
	debug = false;
	QtOut = new QOpenCVWidget(this);
	QtIn = new QOpenCVWidget(this);
	dude = new MyCVFilter(CVImage);

	in = cvCreateImage(cvSize(CVImage->width,CVImage->height),
						 CVImage->depth,
						 CVImage->nChannels);

	out = cvCreateImage(cvSize(CVImage->width,CVImage->height),
						 CVImage->depth,
						 CVImage->nChannels);

	camera = cam;

	m_layout->addWidget(QtIn);
	m_layout->addWidget(QtOut);
	m_layoutButtons->addWidget(m_buttonQuit);
	m_layoutButtons->addWidget(m_buttonSavePic);
	m_layoutButtons->addWidget(m_debug);
	m_layout->addLayout(m_layoutButtons);

	this->setLayout(m_layout);
	resize(500, 400);
	streamId = startTimer(100);  // 0.1-second timer
	refCaptId = startTimer(600000); // 1 hour timer

	QObject::connect(m_buttonQuit,SIGNAL(clicked()),this,SLOT(quitDial()));
	QObject::connect(this,SIGNAL(Iquit()),qApp,SLOT(quit()));
	QObject::connect(m_buttonSavePic,SIGNAL(clicked()),this,SLOT(savePicDial()));
	QObject::connect(m_debug,SIGNAL(stateChanged(int)),this,SLOT(debugChkB()));
}

void Window::quitDial()
{
	int reponse = QMessageBox::question(this, "HomeView", "Quit?", QMessageBox::Yes | QMessageBox::No);
	if(reponse == QMessageBox::Yes)
		emit Iquit();
}

void Window::savePicDial()
{
	cvSaveImage("img.jpg",cvQueryFrame(camera));
}

void Window::debugChkB()
{
	debug = !debug;
}

//called by the Qt timer events
void Window::timerEvent(QTimerEvent* e) {
	if(e->timerId()==streamId)
	{
		in=cvQueryFrame(camera);
		//execute vision algorithm
		dude->execute(in,out);
		dude->setDebug(debug);
		QtIn->putImage(in);
		QtOut->putImage(out);
	}
	//if the reference image is older than one hour, take a new
	if(e->timerId()==refCaptId)
	{
		cvSaveImage("img.jpg",cvQueryFrame(camera));
	}
}

Window::~Window()
{
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseCapture(&camera);
}
