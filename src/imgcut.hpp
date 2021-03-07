#ifndef IMGCUT_HPP
#define IMGCUT_HPP
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QImage>
#include <QProgressBar>

#include <iostream>
#include <climits>
#include <ratio>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

static const unsigned int maxWidth = 512;

class ImgCut : public QObject{
    Q_OBJECT
    private:
        QImage* img;
        QSize *framesize, *originalsize;
        QPoint* startp;
        QLabel* canvas;
        QProgressBar *pbar; 
        unsigned int frameid = 0, frameNumber = 1;
        unsigned int zoomf = 1;
    public:
        ImgCut(QImage *imgi, QObject *parent = nullptr);
        unsigned int estimateFrameNumber();
        void setCanvas(QLabel *lab);
        void nextFrame();
        void setFrameNumber(unsigned int frn);
        unsigned int getFrameNumber();
        void alterZoomFactor(unsigned int zoomfactor);
        unsigned int zoomLimit();
        void setBar(QProgressBar *bari);
};

#endif