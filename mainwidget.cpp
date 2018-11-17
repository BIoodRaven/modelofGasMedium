#include "mainwidget.h"
#include "paintline.h"
mainWidget::mainWidget(QWidget *parent) : QWidget(parent)
{

    QCheckBox* XeCl_X = new QCheckBox("&XeCl(X)");
    QCheckBox* XeCl_BC = new QCheckBox("&XeCl(B,C)");
    QCheckBox* Xe2Cl = new QCheckBox("&Xe2Cl*");
    QCheckBox* m = new QCheckBox("&Cl");
    QCheckBox* M = new QCheckBox("&Cl2");
    XeCl_X->setChecked(false);
    XeCl_BC->setChecked(false);
    Xe2Cl->setChecked(false);
    m->setChecked(false);
    M->setChecked(false);


    PaintLine* line = new PaintLine(this);
    QPushButton* doGraph = new QPushButton("&Plot");
    connect(doGraph,SIGNAL(clicked()),line,SLOT(addCounter()));
    connect(doGraph,SIGNAL(clicked(bool)),line,SLOT(modEiler(bool)));
    connect(line,SIGNAL(dataChanged()),line,SLOT(repaint()));

    QPushButton* exitApp = new QPushButton("&Quit");
    connect(exitApp,SIGNAL(clicked()),qApp,SLOT(quit()));


    QPushButton* ChangeRates = new QPushButton("&Change Constants");
    connect(ChangeRates,SIGNAL(clicked()),this,SLOT(constants()));

    QVBoxLayout* vertLayout = new QVBoxLayout;
    vertLayout->addWidget(XeCl_X);
    vertLayout->addWidget(XeCl_BC);
    vertLayout->addWidget(Xe2Cl);
    vertLayout->addWidget(m);
    vertLayout->addWidget(M);
    vertLayout->addWidget(doGraph);
    vertLayout->addWidget(ChangeRates);
    vertLayout->addWidget(exitApp);

    QHBoxLayout* HLayout = new QHBoxLayout;
    HLayout->addLayout(vertLayout,1);
    HLayout->addSpacing(40);
    HLayout->addWidget(line,6);

    setLayout(HLayout);
    resize(1150,850);
}

void mainWidget:: constants()
{
    QWidget* wImax = new QWidget();
    QPushButton* Imax = new QPushButton("Ok");
    QLabel* lblImax = new QLabel("&Imax, 10^25 = ");
    QSpinBox* spbImax = new QSpinBox;
    lblImax->setBuddy(spbImax);

    QHBoxLayout* hblayout = new QHBoxLayout;
    hblayout->addWidget(lblImax);
    hblayout->addWidget(spbImax);
    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addLayout(hblayout);
    vlayout->addWidget(Imax);
    connect(Imax,SIGNAL(clicked(bool)),wImax,SLOT(hide()));
    connect(spbImax,SIGNAL(valueChanged(int)),this,SLOT(ImaxValue(int)));

    wImax->setLayout(vlayout);
    wImax->resize(500,500);
    wImax->show();

}

void mainWidget::ImaxValue(int n)
{
    QFile file("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/constants.txt");
    qDebug()<<n;
    QTextStream stream(&file);
    if(file.open(QIODevice::Append))
    {
        stream<<n;
        file.close ();
    }
    //str = stream.readLine();
    //stream>>a1>>a2>>a3>>a4>>a5>>a6>>a7>>a8>>a9>>a10>>a11>>a12>>a13;
    //dataX[n]=a1;dataY[m]=a5;n++;m++;



}
