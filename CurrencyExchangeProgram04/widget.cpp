#include "widget.h"
#include "ui_widget.h"
#include "qcustomplot.h"
#include <QSound>
#include <QSoundEffect>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setupgraph(ui->customPlot);



    //First drop down menu & options:
    ui->currencyDropDown1->addItem("U.S. Dollar");
    ui->currencyDropDown1->addItem("Euro");
    ui->currencyDropDown1->addItem("Argentine Peso");
    ui->currencyDropDown1->addItem("Mexican Peso");
    ui->currencyDropDown1->addItem("Chinese Yuan");
    ui->currencyDropDown1->addItem("British Pound");
    ui->currencyDropDown1->addItem("Japanese Yen");
    ui->currencyDropDown1->addItem("Swedish Krona");
    ui->currencyDropDown1->addItem("Australian Dollar");
    ui->currencyDropDown1->addItem("Brazilian Real");

    //Second drop down menu & options:
    ui->currencyDropDown2->addItem("Euro");
    ui->currencyDropDown2->addItem("U.S. Dollar");
    ui->currencyDropDown2->addItem("Argentine Peso");
    ui->currencyDropDown2->addItem("Mexican Peso");
    ui->currencyDropDown2->addItem("Chinese Yuan");
    ui->currencyDropDown2->addItem("British Pound");
    ui->currencyDropDown2->addItem("Japanese Yen");
    ui->currencyDropDown2->addItem("Swedish Krona");
    ui->currencyDropDown2->addItem("Australian Dollar");
    ui->currencyDropDown2->addItem("Brazilian Real");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setupgraph(QCustomPlot *customPlot){
    //Graph Stuff
    // generate some data:
    QVector<double> x(5), y(5); // initialize with entries 0..100
    for (int i=0; i<5; ++i)
    {
      x[i] = i;
    }

        y[0] = 1;
        y[1] = 1;
        y[2] = 1;
        y[3] = 1;
        y[4] = 1;

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 4);
    customPlot->yAxis->setRange(0, 4);
    customPlot->replot();
}

void Widget::on_currencyDropDown1_activated(const QString &arg1)
{
    dropDownText1 = arg1;
    float rateForeignToUs = 1;//Rate of exchange from foreign to us
    float rateUsToForeign = 0.73;//Rate of exchange from us to foreign...(starts initially at Euro rate...)
    float usDollarValue = 0;
    float input = 0;
    float result = 0;

    if(arg1 == "U.S. Dollar"){
        rateForeignToUs = 1;
        //QSound::play("G://sounds//usa.wav");
        ui->lblCurrType->setText("U.S. Dollar");
    }
    if(arg1 == "Euro"){
        rateForeignToUs = 1.36;
        //QSound::play("G://sounds//germany.wav");
        ui->lblCurrType->setText("Euro");
    }
    if(arg1 == "Argentine Peso"){
        rateForeignToUs = 0.12;
        //QSound::play("G://sounds//argentina.wav");
        ui->lblCurrType->setText("Arentine Peso");
    }
    if(arg1 == "Mexican Peso"){
        rateForeignToUs = 0.078;
        //QSound::play("G://sounds//mexico.wav");
        ui->lblCurrType->setText("Mexican Peso");
    }
    if(arg1 == "Chinese Yuan"){
        rateForeignToUs = 0.16;
        //QSound::play("G://sounds//china.wav");
        ui->lblCurrType->setText("Chinese Yuan");
    }
    if(arg1 == "British Pound"){
        rateForeignToUs = 1.67;
        //QSound::play("G://sounds//britian.wav");
        ui->lblCurrType->setText("British Pound");
    }
    if(arg1 == "Japanese Yen"){
        rateForeignToUs = 0.0098;
        //QSound::play("G://sounds//japan.wav");
        ui->lblCurrType->setText("Japanese Yen");
    }
    if(arg1 == "Swedish Krona"){
        rateForeignToUs = 0.15;
        //QSound::play("G://sounds//sweden.wav");
        ui->lblCurrType->setText("Swedish Krona");
    }
    if(arg1 == "Australian Dollar"){
        rateForeignToUs = 0.93;
        //QSound::play("G://sounds//australia.wav");
        ui->lblCurrType->setText("Australian Dollar");
    }
    if(arg1 == "Brazilian Real"){
        rateForeignToUs = 0.45;
        //QSound::play("G://sounds//brazil.wav");
        ui->lblCurrType->setText("Brazilian Real");
    }

    //Calculate change based on currency type chosen...
    input = ui->inputBox->text().toInt();//Get amount from input box - convert text to number

    //Take input amount and convert the amount to U.S. Dollars...
    usDollarValue = input * rateForeignToUs;

    //Get text value from dropbox 2...
    if(dropDownText2 == "U.S. Dollar")
        rateUsToForeign = 1;
    if(dropDownText2 == "Euro")
        rateUsToForeign = 0.73;
    if(dropDownText2 == "Argentine Peso")
        rateUsToForeign = 8.07;
    if(dropDownText2 == "Mexican Peso")
        rateUsToForeign = 12.87;
    if(dropDownText2 == "Chinese Yuan")
        rateUsToForeign = 6.25;
    if(dropDownText2 == "British Pound")
        rateUsToForeign = 0.60;
    if(dropDownText2 == "Japanese Yen")
        rateUsToForeign = 101.73;
    if(dropDownText2 == "Swedish Krona")
        rateUsToForeign = 6.67;
    if(dropDownText2 == "Australian Dollar")
        rateUsToForeign = 1.07;
    if(dropDownText2 == "Brazilian Real")
        rateUsToForeign = 2.24;

    //Convert amount from us to new foreign rate...
    result = usDollarValue * rateUsToForeign;

    ui->outputBox->setText(QString::number(result));
    ui->lblResultAmt->setText(QString::number(result));
}

void Widget::on_currencyDropDown2_activated(const QString &arg2)
{
    dropDownText2 = arg2;
    float rateForeignToUs = 1;//Rate of exchange from foreign to us
    float rateUsToForeign = 0.73;//Rate of exchange from us to foreign...(starts initially at Euro Rate)
    float usDollarValue = 0;
    float input = 0;
    float result = 0;

    ui->lblResultType->setText(arg2);

    //First get currency type from drop box one
    //to know which conversion is desired...
    if(dropDownText1 == "U.S. Dollar")
        rateForeignToUs = 1;
    if(dropDownText1 == "Euro")
        rateForeignToUs = 1.36;
    if(dropDownText1 == "Argentine Peso")
        rateForeignToUs = 0.12;
    if(dropDownText1 == "Mexican Peso")
        rateForeignToUs = 0.078;
    if(dropDownText1 == "Chinese Yuan")
        rateForeignToUs = 0.16;
    if(dropDownText1 == "British Pound")
        rateForeignToUs = 1.67;
    if(dropDownText1 == "Japanese Yen")
        rateForeignToUs = 0.0098;
    if(dropDownText1 == "Swedish Krona")
        rateForeignToUs = 0.15;
    if(dropDownText1 == "Australian Dollar")
        rateForeignToUs = 0.93;
    if(dropDownText1 == "Brazilian Real")
        rateForeignToUs = 0.45;

    //Calculate change based on currency type chosen...
    //First get amount from input box - convert text to number
    input = ui->inputBox->text().toInt();

    //Then take input amount and convert the amount to U.S. Dollars...
    usDollarValue = input * rateForeignToUs;

     //If any song is in the middle of playing... stop it for the new song...


    //Get text value from dropbox 2 so we know what to convert it into...
    if(dropDownText2 == "U.S. Dollar"){
        rateUsToForeign = 1;
         QSoundEffect::play("G://sounds//usa.wav");
    }
    if(dropDownText2 == "Euro"){
        rateUsToForeign = 0.73;
        QSound::play("G://sounds//germany.wav");
    }
    if(dropDownText2 == "Argentine Peso"){
        rateUsToForeign = 8.07;
        QSound::play("G://sounds//argentina.wav");
    }
    if(dropDownText2 == "Mexican Peso"){
        rateUsToForeign = 12.87;
        QSound::play("G://sounds//mexico.wav");
    }
    if(dropDownText2 == "Chinese Yuan"){
        rateUsToForeign = 6.25;
        QSound::play("G://sounds//china.wav");
    }
    if(dropDownText2 == "British Pound"){
        rateUsToForeign = 0.60;
        QSound::play("G://sounds//britian.wav");
    }
    if(dropDownText2 == "Japanese Yen"){
        rateUsToForeign = 101.73;
        QSound::play("G://sounds//japan.wav");
    }
    if(dropDownText2 == "Swedish Krona"){
        rateUsToForeign = 6.67;
        QSound::play("G://sounds//sweden.wav");
    }
    if(dropDownText2 == "Australian Dollar"){
        rateUsToForeign = 1.07;
        QSound::play("G://sounds//australia.wav");
    }
    if(dropDownText2 == "Brazilian Real"){
        rateUsToForeign = 2.24;
        QSound::play("G://sounds//brazil.wav");
    }

    //Convert amount from us to new foreign rate...
    result = usDollarValue * rateUsToForeign;

    ui->outputBox->setText(QString::number(result));
    ui->lblResultAmt->setText(QString::number(result));
}



void Widget::on_inputBox_textEdited(const QString &arg1)
{
    ui->lblCurrAmount->setText(arg1);
}


