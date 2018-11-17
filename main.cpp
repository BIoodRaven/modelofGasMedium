#include "paintline.h"
#include "mainwidget.h"
#include "calculusbody.h"
#include <QApplication>
#include<QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintLine createMEEM;
    QFile file2("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/MEEM.txt");
    file2.remove();
    createMEEM.modEiler(false);
    //QWidget asd;
    //PaintLine* line = new PaintLine(&asd);

    QFile file("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/constants.txt");
    file.remove();
    QFile file1("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/Xe2Cl.txt");
    file1.remove();
    mainWidget w;
    //QLabel* lbl = new QLabel(&asd);


    //QPixmap pic("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/graph.png");
    //lbl->setPixmap(pic);






//HLayout->setContentsMargins


    w.show();


    return a.exec();
}
