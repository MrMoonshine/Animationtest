#ifndef ANIGUI_HPP
#define ANIGUI_HPP
#include <QApplication>
#include <QGridLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <iostream>
#include <QPushButton>
#include <QSpinBox>
#include <QDial>
#include <QTimer>
#include <QSlider>
#include <QLCDNumber>
#include <QProgressBar>
#include <QPalette>
#include <climits>
#include <ratio>
#include <sstream>
#include <fstream>
#include <cmath>
#include <chrono>

#include "imgcut.hpp"

using namespace std;
using namespace std::chrono_literals;

static const float minf = 0.1 * std::milli::den;
static const float maxf = 15 * std::milli::den;

class AniGui : public QObject{
    //Q_OBJECT
    private:
        QColor *myColor;
        QPalette *ubuntu;

        QLCDNumber *disphz;
        QVBoxLayout *vlay;
        QHBoxLayout *fraui,*finfo , *freui;
        QDial *fsel;
        QSpinBox *frnum, *zoomf;
        QProgressBar *framedis;
        QPushButton *startbutt, *stopbutt;

        ImgCut *ani;

        QTimer *timer;
        std::chrono::milliseconds period;

        void updateLCDisplay(int v);
        void createUbuntuColours();
        void uptprogbar(int v);
        void startani();
    public:
        AniGui(ImgCut *anii, QObject *parent = nullptr);
        QVBoxLayout* getFullGui();
        QLabel *canvas;
        float frequency = 1.0;
};

#endif