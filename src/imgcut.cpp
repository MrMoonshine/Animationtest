#include "imgcut.hpp"
ImgCut::ImgCut(QImage *imgi, QObject *parent) : QObject(parent){
    img = imgi;
    originalsize = new QSize(
        img->width(),
        img->height()
    );

    frameNumber = estimateFrameNumber();
    zoomf = zoomLimit();
    //cout << img->width() << "x" << img->height() << endl;
}

void ImgCut::setCanvas(QLabel *lab){
    canvas = lab;
}

void ImgCut::nextFrame(){
    //cout << "Next Frame"<<endl;
    framesize = new QSize(img->width(),img->height()/frameNumber);
    startp = new QPoint(0,framesize->height()*(frameid % frameNumber));
    pbar->setValue((frameid % frameNumber)+1);

    QImage sframe = img->copy(
        QRect(
            *startp,
            *framesize
        )
    );

    canvas->setPixmap(
        QPixmap::fromImage(
            sframe.scaled(
                img->width()*zoomf,
                img->height()*zoomf,
                Qt::KeepAspectRatio
            )
        )
    );
    frameid++;
}

unsigned int ImgCut::estimateFrameNumber(){
    return img->height()/img->width();
}

void ImgCut::setFrameNumber(unsigned int frn){
    cout << "setting framenumber to: " << frn << endl;
    frameNumber = frn;
    pbar->setMaximum(frameNumber);
}

unsigned int ImgCut::getFrameNumber(){
    return frameNumber;
}

void ImgCut::alterZoomFactor(unsigned int zoomfactor){
    cout << "setting zoomfacto to: " << zoomfactor << endl;
    zoomf = zoomfactor;
}

unsigned int ImgCut::zoomLimit(){
    unsigned int ret = maxWidth / img->width();
    
    return ret ? ret : 1;
}

void ImgCut::setBar(QProgressBar *bari){
    pbar = bari;
}