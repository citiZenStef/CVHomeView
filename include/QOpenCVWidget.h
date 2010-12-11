
#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include </usr/include/opencv/cv.h>
#include </usr/include/opencv/highgui.h>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>

class QOpenCVWidget : public QWidget {
    private:
        QLabel *imagelabel;
        QVBoxLayout *layout;

        QImage image;

    public:
        QOpenCVWidget(QWidget *parent = 0);
        ~QOpenCVWidget(void);
        void putImage(IplImage *);
};

#endif
