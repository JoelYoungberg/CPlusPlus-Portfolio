#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"
#include <QSound>
#include <QMultimedia>
//#include <phonon>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setupgraph(QCustomPlot *customPlot);
    ~Widget();


    //Variables for dropdowns (public so they can access one another)
    QString dropDownText1;
    QString dropDownText2;
    QString songName;


private slots:


    void on_currencyDropDown1_activated(const QString &arg1);

    void on_currencyDropDown2_activated(const QString &arg2);

    void on_inputBox_textEdited(const QString &arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
