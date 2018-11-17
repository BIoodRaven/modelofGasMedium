#ifndef PAINTLINE_H
#define PAINTLINE_H

#include<iostream>
#include<calculusbody.h>
#include<paintline.h>
#include<mainwidget.h>
#include <QWidget>
#include <QPainter>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPicture>
#include <QLabel>

#include<QIODevice>
#include<QDebug>
#include<QFile>

#include<QTimer>
class PaintLine : public QWidget
{
    Q_OBJECT
private:
    int counter;
    double Imax;
    double h;
public:
    PaintLine(QWidget *parent = 0);
    ~PaintLine();
public slots:
    void addCounter();
    void paintEvent(QPaintEvent*);
    void modEiler(bool);
signals:
    void dataChanged();
};

#endif // PAINTLINE_H
