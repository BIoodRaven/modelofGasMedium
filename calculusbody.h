#ifndef CALCULUSBODY_H
#define CALCULUSBODY_H
#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include<fstream>
#include<cmath>
#include<locale.h>
#include<string.h>
#include <sstream>
#include <QWidget>
#include <QDebug>
#include<paintline.h>
class calculusBody :  public QWidget
{
    Q_OBJECT


public:
    calculusBody(QWidget *parent=0);

signals:
    void anuka();
public slots:


};

#endif // CALCULUSBODY_H
