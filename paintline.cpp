#include "paintline.h"

PaintLine::PaintLine(QWidget *parent)
    : QWidget(parent)
{
    counter=0;
    qDebug()<<counter;
    Imax = 5350;
    h = 0.001;

}

PaintLine::~PaintLine()
{

}

void PaintLine::addCounter()
{
    counter++;
}



void PaintLine::paintEvent(QPaintEvent*)//height 800 width 1000
{
    int n=250 / h ,m=250 / h;

    //QImage imageGraph(width(), height(), QImage::Format_RGB32);
    QPainter* plotLine = new QPainter(this);

    //QPainter* plotLine = new QPainter(&imageGraph);

    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(5000);


    qreal a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0,a8=0,a9=0,
            a10=0,a11=0,a12=0,a13=0,next1=0,next2=0;
    QFile file("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/MEEM.txt");
    n=0;m=0;
    if (file.open(QIODevice::ReadOnly))
    {
    QTextStream stream(&file);

    plotLine->setRenderHint(QPainter::Antialiasing,true);
    plotLine->setPen(QPen(Qt::red, 4, Qt::SolidLine));

    while (!stream.atEnd())
    {
    //str = stream.readLine();
    stream>>a1>>a2>>a3>>a4>>a5>>a6>>a7>>a8>>a9>>a10>>a11>>a12>>a13;
    stream>>next1>>a2>>a3>>a4>>next2>>a6>>a7>>a8>>a9>>a10>>a11>>a12>>a13;
    plotLine->drawLine(QPointF(a1*3.5,804-(a5/1E+12)),QPointF(next1*3.5,804-(next2/1E+12)));

    }

    if (stream.status() != QTextStream::Ok)
    {qDebug() << "Ошибка чтения файла";}
    file.close ();
    }
    //qDebug()<<dataX[2499]<<dataY[2499];

    //imageGraph.save("graph.png");

}



//---------------------------------------------MOD EILER------------------------------------------
void PaintLine ::modEiler(bool forma)
{
    double K/*,coef_I = 1*/; K = 250 / h;h = h*1E-9;
    int form=3;
    //if(counter>=2) form =2;
    //forma=true;
    std::ofstream data("MEEM.txt");
    /*Imax = 0,*/
    double  N = 5E+19, M0 = 3.3E+16;//N=5,5E+19 всегда,но 6.11.2018 RIP  N - [Xe] M - [Cl2]
    double a = 0, b = 0, c = 0, d = 0, f = 0, g = 0, T = 0, KI = 0;//инициализация переменный для плотности накачки T=t*1E+9
    //int   w = 0, v = 0;
    //read rates from file

    QFile file("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/constants.txt");

    QTextStream stream(&file);
    if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
    {
        stream<<Imax*9<<'\n';
        file.close ();
    }
/*
    if (file.open(QIODevice::ReadOnly))
    {
    QTextStream stream(&file);
    QString str;
    while (!stream.atEnd())
    {
    stream>>Imax;
    //str = stream.readLine();
    //stream>>a1>>a2>>a3>>a4>>a5>>a6>>a7>>a8>>a9>>a10>>a11>>a12>>a13;
    //dataX[n]=a1;dataY[m]=a5;n++;m++;
    }

    if (stream.status() != QTextStream::Ok)
    qDebug() << "Ошибка чтения файла";
    file.close ();
    }
*/
    //----------------
    switch (form)
    {
    case 1: {a = 9.145; b = 31.86; c = 10.16; d = 11.62; f = 62.21; g = 23.09; T = 0; KI = 0; /*Imax = coef_I*8.4E+23;*/ break; }//двугорб с макс 9.2E+24
    case 2: {a = 101.2; b = 27.812; c = 75.97; d = 12.94; f = 55.51; g = 22.68; T = 0; KI = 0;/* Imax = 9.4E+22;*/ break; }//odin gorb s maximumom 1.1E+25 коэф b и f смещены на 20
    //===== 13.11.18 case 3: b = 3.832
    //=======    I = Imax*(a*exp(-pow((T - b), 2) / pow(d, 2)) + c*exp(-pow((T - f), 2) / pow(g, 2))) MEEM I CHANGED TOO!!!!
    case 3: {a = 7.49-0.2; b = 6.832-3.8; c = 0.9309+1.5; d = 2.811+7.5; f = 12.027+9;//changed b=3.832+3, f=9.027+3
                g = 1.859+7; T = 0; KI = 0;/* Experiment 02.11.2018 */ break; }//c=h
    default: {std::cout << "Error"; }
    }
    //------------------------Imax------------------------
    Imax=Imax*1E+23;
    //Блок характеристик накачки
    //qDebug()<< Imax<<form;
    double t = 0;	/*время*/

    double n1 = 0, n2 = 0, n3 = 0, m = 0, M = M0, I = 0, XeI=0,XeClI=0, Xe2I=0,ClI=0,e=0, XeS=0,Xe2S=0,XeS2=0;//n1 - n1; n2 - n1*; n3 - n2*; m - [Cl]; M - [Cl2]; I - I      Начальные значения
    I = Imax*(a*exp(-pow((T - b), 2) / pow(d, 2)) + c*exp(-pow((T - f), 2) / pow(g, 2)));//0 значение

    double k_1 = 5.6E-12, k1 = 1.7E-33, b1 = 1.4E-16, b_1 = 4.2E-16, k1M =4.3E-10, k1m =8E-10, t1sp =25E-9, k1N = 5E-12;//b_1=4.2E-16
    double k3 = 1.3E-30;
    double k2M = 4E-10, k2m = 7.8E-11, b2 = 8.7E-18, t2sp = 244E-9;/* k2m=4E-10*/
    double bp = 1.8E-19;
    double nBX = 0.38/*, c0 = 3E+10*/;
    //Блок констант уравнений

    double kNn3 =6E-15, kXeXeI = 2E-31, bXe2I= 1.12E-17, bClI = 1.2E-17, keM=2E-10, /*kXeXeClI=1E-12,*/
            kXe2IClI=1.39E-6, kXeIClI=1.39E-6, kBCe=3.2E-8, kXCe=2E-8, kXe2Ie=2.3E-6;
    //kXe2IClI=0/*1.39E-6*/, kXeIClI=0/*1.39E-6*/, kBCe=3.2E-8, kXCe=2E-8, kXe2Ie=2.3E-6;
    //kXe2IClI=4.1E-7
    double kXeSXe = 5E-32, keXe2S = 1 / (9.75E+8*pow(300, 0.705)*exp(-(3.4 / 300))), kXe2Se = 1E-9,
            tXe2S = 1 / (6E+7), bXe2S = 7.1E-18,kXeS2M=2E-9,kXeS2XeS=5.5E-11,kXeSM=7E-10;
    //double kXeSXe = 5E-32, keXe2S = 1 / (9.75E+8*pow(300, 0.705)*exp(-(3.4 / 300))), kXe2Se = 1E-9,
            //tXe2S = 1 / (6E+7), bXe2S = 7.1E-18,kXeS2M=2E-9,kXeS2XeS=5.5E-11,kXeSM=7E-10;
    //Block of new constants for ions; keXe2S chemu ravna??


    double temp[14], coef[14][2], Tc = 0;

    //Блок переменных метода
    if (!data) {
        std::cout << "Error. Can not open file!";
    }


    temp[0] = m;
    temp[1] = n1;
    temp[2] = n2;
    temp[3] = n3;
    temp[4] = XeI;
    temp[5] = XeClI;
    temp[6] = Xe2I;
    temp[7] = ClI;
    temp[8] = e;
    temp[9] = XeS;
    temp[10] = Xe2S;
    temp[11] = XeS2;

    //special exercise
    //double ssgain=0;
    //special exercise

    double Xe2Cl_max=0,Irealmax=0, time=0;
    for (int i = 0; i < K; i++)
    {

        data.width(12); data.precision(4);
        data << t*1E+9; //data << m / 1000E+12;
        data.width(12); data.precision(4);
        data << I*0.183E-27; //data << m / 1000E+12;
        data.width(12); data.precision(4);
        data << n1; //data << n1 / 20E+12;
        data.width(12); data.precision(4);
        data << n2; //data << n2 / 1E+12;
        data.width(12); data.precision(4);
        data << n3;//data << n3 / 80E+12 << endl;
        data.width(12); data.precision(4);
        data << XeI; //data << m / 1000E+12;
        data.width(12); data.precision(4);
        data << XeClI; //data << n1 / 20E+12;
        data.width(12); data.precision(4);
        data << Xe2I; //data << n2 / 1E+12;
        data.width(12); data.precision(4);
        data << ClI;
        data.width(12); data.precision(4);
        data << e;
        data.width(12); data.precision(4);
        data << XeS;
        data.width(12); data.precision(4);
        data << Xe2S;
        data.width(12); data.precision(4);
        data << XeS2 << std::endl;
            /*
            data.width(12); data.precision(4);
            data << m; //data << m / 1000E+12;
            data.width(12); data.precision(4);
            data << n1; //data << n1 / 20E+12;
            data.width(12); data.precision(4);
            data << n2; //data << n2 / 1E+12;
            data.width(12); data.precision(4);
            data << n3 << endl;;//data << n3 / 80E+12 << endl;
            */
        t += h;

        Tc = t; T = Tc*1E+9;
        temp[12] = Imax*(a*exp(-pow((T - b), 2) / pow(d, 2)) + c*exp(-pow((T - f), 2) / pow(g, 2)));
        temp[13] = M0*exp(bp*Imax*1E-9*(0.5*a*d*1.77*(erf((b - T) / d) - erf(b / d)) + 0.5*c*g*1.77*(erf((f - T) / g) - erf(f / g))));

        KI = bp*M + b1*n1 + b2*n3 - b_1*nBX;
        for (int y = 0; y < 2; y++)
        {
            Tc = t + (y*h);
            T = Tc*1E+9;
            I = Imax*(a*exp(-pow((T - b), 2) / pow(d, 2)) + c*exp(-pow((T - f), 2) / pow(g, 2)));
            M = M0*exp(bp*Imax*1E-9*(0.5*a*d*1.77*(erf((b - T) / d) - erf(b / d)) + 0.5*c*g*1.77*(erf((f - T) / g) - erf(f / g))));
            //I = I*exp(-(KI*deltaZ));

        //Cl
        coef[0][y] = h*(k_1*N*n1 + (-k2m*m + k2M*M/* + b2*I*/ + (1 / t2sp)+kNn3*N)*n3 + (2 * bp*I*M) -
         k1*pow(N, 2)*m + bClI*I*ClI + keM*e*M+ kBCe*n2*e+ kXCe*e*n3+kXeS2M*XeS2*M+kXeSM*XeS*M);
        //constants - kXeSM, kXeS2M, bClI, kBCe, kXCe, bp, k2M, k2m, keM, k1, k_1(kinetika)

        //XeCl(X)
        coef[1][y] = h*(((-k_1*N - b1*I)*n1) + ((b_1*I*nBX + k1M*M + k1m*m + (1 / t1sp) + k1N*N)*n2) +
                        (k1*pow(N, 2)*m));
        //constants - k1, k_1, b1, b_1, k1M, k1m, k1N

        //XeCl(B,C)
        coef[2][y] = h*(b1*I*n1 + (-k3*pow(N, 2) - (b_1*I*nBX + k1M*M + k1m*m + (1 / t1sp) + k1N*N))*n2 +
                        kXe2IClI*Xe2I*ClI + kXeIClI*XeI*ClI - kBCe*n2*e+kXeS2M*XeS2*M+kXeSM*XeS*M);
        //constants - kXeS2M, kXeSM, b1, b_1, k3, k1M, k1m, k1N, kXe2IClI, kXeIClI, kBCe

        //Xe2Cl*
        coef[3][y] = h*(k3*pow(N, 2)*n2 - (k2m*m + k2M*M + b2*I + (1 / t2sp) + kNn3*N)*n3 - kXCe*e*n3);
        //constants - k3, k2m, k2M, b2, kNn3, kXCe

        //Xe+
        coef[4][y] = h*(b2*I*n3 + bXe2I*I*Xe2I - kXeXeI*XeI*pow(N, 2) - kXeIClI*XeI*ClI);//Xe+
        //constants - b2, bXe2I, kXeXeI, kXeIClI

        //XeCl-
        coef[5][y] =0;// h*(b2*I*n3 - kXeXeClI*XeClI*N);//XeCl-  - kXeXeClI*XeClI*N
        //constants - b2, kXeXeClI

        //Xe2+
        coef[6][y] = h*(kXeXeI*XeI*pow(N, 2)- bXe2I*I*Xe2I-kXe2IClI*Xe2I*ClI- kXe2Ie*Xe2I*e+
                        keXe2S*e*Xe2S + bXe2S*Xe2S*I);
        //constants - kXeXeI, bXe2I, kXe2IClI, kXe2IClI, kXe2Ie, keXe2S, bXe2S

        //Cl-
        coef[7][y] = h*(/*kXeXeClI*XeClI*N*/ - bClI*I*ClI + keM*e*M - kXe2IClI*Xe2I*ClI + b2*I*n3
                        - kXeIClI*XeI*ClI);
        //constants - kXeXeClI, bClI, keM, kXe2IClI, kXeIClI

        //e
        coef[8][y] = h*(-keM*e*M+ bClI*I*ClI- kXe2Ie*Xe2I*e + keXe2S*e*Xe2S + bXe2S*Xe2S*I);
        //constants - keM, bClI, kXe2Ie, keXe2S, bXe2S

        //Xe*
        coef[9][y] = h*( - kXeSXe*XeS*pow(N,2)+kXeS2XeS*XeS2*N-kXeSM*XeS*M);
        //constants - kXeSXe, kXeS2XeS, kXeSM

        //Xe2* - Xe2S
        coef[10][y] = h*(kXeSXe*XeS*pow(N, 2)- keXe2S*e*Xe2S - (1/tXe2S)*Xe2S - bXe2S*Xe2S*I-
                         kXe2Se*Xe2S*e);
        //constants - kXeSXe, keXe2S, bXe2S

        //Xe** - XeS2
        coef[11][y] =h*(kXe2Ie*Xe2I*e-kXeS2XeS*XeS2*N-kXeS2M*XeS2*M);
        //constants - kXe2Ie, kXeS2XeS, kXeS2M
        }
        for (int q = 0; q < 12; q++)
        {
            temp[q] = temp[q] + (coef[q][0] + coef[q][1]) / 2;
        }

        m = temp[0];
        n1 = temp[1];
        n2 = temp[2];
        n3 = temp[3];
        XeI = temp[4];
        XeClI = temp[5];
        Xe2I = temp[6];
        ClI = temp[7];
        e = temp[8];
        XeS = temp[9];
        Xe2S=temp[10];
        XeS2=temp[11];
        I = temp[12];
        M = temp[13];

        //if(i==20000) ssgain=(n3*0.63)/2.38E+14;
        if(temp[3]>=Xe2Cl_max) {Xe2Cl_max=temp[3];time=T;};
        if(temp[12]>=Irealmax) {Irealmax=temp[12];};
    }

    data.close();

    qDebug()<<time<<Irealmax<<Xe2Cl_max;
    if(forma = true) emit dataChanged();

    QFile file1("E:/projects/build-paintFirstTry-Desktop_Qt_5_10_0_MinGW_32bit-Debug/Xe2Cl.txt");
    QTextStream stream1(&file1);
    if(file1.open(QIODevice::WriteOnly |QIODevice::Text| QIODevice::Append))
    {
        stream1.setFieldWidth(15);
        stream1<<Xe2Cl_max<<Irealmax<<'\n';
        //stream1.setFieldWidth(12);

        file1.close ();
    }
    Imax=Imax*1.3E-23;h = h*1E+9;
}
