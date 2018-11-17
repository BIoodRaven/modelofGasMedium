#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QApplication>
#include <QSpinBox>

class mainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mainWidget(QWidget *parent = nullptr);

signals:

public slots:
    void constants();
    void ImaxValue(int);
};

#endif // MAINWIDGET_H
