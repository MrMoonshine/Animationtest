#include <QApplication>
#include <QGridLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <QPushButton>
#include <QCoreApplication>

#include "imgcut.hpp"
#include "anigui.hpp"

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Incomplete command! Use it like this:" << endl;
        cout << "animationtester <image>" << endl;
        cout << "<image>\t\tpath to your image [PNG]" << endl;
        return EXIT_FAILURE;
    }

    QApplication a(argc, argv);

    QWidget *mainw = new QWidget();

    ImgCut img(new QImage(argv[1]));
    AniGui myui(&img);
    img.nextFrame();

    QVBoxLayout *vlay = myui.getFullGui();
    mainw->setLayout(vlay);
    mainw->show();
    return a.exec();
}
