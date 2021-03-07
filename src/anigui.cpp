#include "anigui.hpp"

AniGui::AniGui(ImgCut *anii, QObject *parent) : QObject(parent){
    ani = anii;
    canvas = new QLabel("Canvas");
    ani->setCanvas(canvas);
    fsel = new QDial();
    disphz = new QLCDNumber();
    frnum = new QSpinBox();
    zoomf = new QSpinBox();
    startbutt = new QPushButton("Start");
    stopbutt = new QPushButton("Stop");

    framedis = new QProgressBar();
    framedis->setMinimum(1);
    framedis->setMaximum(ani->estimateFrameNumber());
    framedis->setValue(1);
    framedis->setFormat(QString("frame %v"));
    ani->setBar(framedis);

    //Dial values
    fsel->setMinimum(minf);
    fsel->setMaximum(maxf);
    connect(fsel,&QDial::sliderMoved,this,&AniGui::updateLCDisplay);
    updateLCDisplay(fsel->value());
    //Dial height
    fsel->setFixedHeight(80);
    disphz->setFixedWidth(250);
    //Frame info
    frnum->setMinimum(1);
    frnum->setValue(ani->estimateFrameNumber());
    connect(frnum,QOverload<int>::of(&QSpinBox::valueChanged),ani,&ImgCut::setFrameNumber);
    connect(frnum,QOverload<int>::of(&QSpinBox::valueChanged),framedis,&QProgressBar::setMaximum);
    connect(frnum,QOverload<int>::of(&QSpinBox::valueChanged),this,&AniGui::uptprogbar);
    zoomf->setMinimum(ani->zoomLimit());
    zoomf->setMaximum(ani->zoomLimit());
    connect(zoomf,QOverload<int>::of(&QSpinBox::valueChanged),ani,&ImgCut::alterZoomFactor);

    freui = new QHBoxLayout();
    fraui = new QHBoxLayout();
    finfo = new QHBoxLayout();
    vlay = new QVBoxLayout();

    fraui->addWidget(new QLabel("1"));
    fraui->addWidget(framedis);
    fraui->addWidget(frnum);

    finfo->addWidget(new QLabel("Zoom factor"));
    finfo->addWidget(zoomf);
    finfo->addWidget(new QLabel("Size of each Frame is:"));

    freui->addWidget(fsel);
    freui->addWidget(disphz);
    freui->addWidget(new QLabel(" Hz"));
    //Start and stop buttons
    freui->addWidget(startbutt);
    freui->addWidget(stopbutt);

    vlay->addWidget(canvas);
    vlay->addLayout(fraui);
    vlay->addLayout(finfo);
    vlay->addLayout(freui);

    createUbuntuColours();

    timer = new QTimer();
    connect(timer,&QTimer::timeout,ani,&ImgCut::nextFrame);

    //Start & stop buttons
    connect(startbutt,&QPushButton::clicked,this,&AniGui::startani);
    connect(stopbutt,&QPushButton::clicked,timer,&QTimer::stop);
}

void AniGui::createUbuntuColours(){
    //Fits in the default Ubuntu UI
    myColor = new QColor(0xE9, 0x54, 0x20);
    ubuntu = new QPalette();

    ubuntu->setColor(QPalette::Highlight, *myColor);
    ubuntu->setColor(QPalette::Light, *myColor);
    ubuntu->setColor(QPalette::Dark, *myColor);
    ubuntu->setColor(QPalette::Window, *myColor);
    ubuntu->setColor(QPalette::WindowText, *myColor);
    fsel->setPalette(*ubuntu);
    frnum->setPalette(*ubuntu);
    zoomf->setPalette(*ubuntu); 
    disphz->setPalette(*ubuntu);
    framedis->setPalette(*ubuntu);    
}

QVBoxLayout* AniGui::getFullGui(){
    return vlay;
}

void AniGui::updateLCDisplay(int v){
    std::stringstream dis;
    dis << std::fixed;
    dis.precision(2);
    dis << (float)v/std::milli::den;
    disphz->display(dis.str().c_str());
}

void AniGui::uptprogbar(int v){
    framedis->setMaximum(v);
}

void AniGui::startani(){
    float f = fsel->value()/1000.0;
    period = std::chrono::milliseconds((int)(std::milli::den/f));

    cout << "Starting animation at " << period.count() << "ms" << endl;

    timer->start(period);
}