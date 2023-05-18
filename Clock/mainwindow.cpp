#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    d->show();
}

void MainWindow::getData(int c, int y, int m, int d, int h, int mi, int s, int e1, int e2)
{
    a = c;
    ui->stackedWidget->setCurrentIndex(a);
    if (a == 0) {
        mech = MechClock("a", 10, Time(h, mi, s), Date(y, m, d), e2);
        m = mech.RMon();
        d = mech.RD();
        ui->labelMechDate->setText(QString::number(y) + "-" + QString::number(m) + "-" + QString::number(d));
        if (mech.RSP() == -1) {
            ui->labelMechSpring->setText("Spring: " + QString::number(100));
        }
        else {
            ui->labelMechSpring->setText("Spring: " + QString::number(e2));
        }
    }
    else if (a == 1) {
        elec = ElecClock("a", 10, Time(h, mi, s), Date(y, m, d), e1);
        m = elec.RMon();
        d = elec.RD();
        ui->lcdNumber->display(h);
        ui->lcdNumber_2->display(mi);
        ui->lcdNumber_3->display(s);
        ui->labelDate->setText(QString::number(y) + "-" + QString::number(m) + "-" + QString::number(d));
        if (elec.RBA() == -1) {
            ui->labelElecBattery->setText("Battery: 100%");
        }
        else {
            ui->labelElecBattery->setText("Battery: " + QString::number(elec.RBA()) + "%");
        }

    }
    else if (a == 2) {
        MEClock me1("a", 10, Time(h, mi, s), Date(y, m, d), e2, e1);
        me.Move(me1);
        ui->lcdNumber_4->display(h);
        ui->lcdNumber_5->display(mi);
        ui->lcdNumber_6->display(s);
        m = me.RMon();
        d = me.RD();
        ui->labelMEDate->setText(QString::number(y) + "-" + QString::number(m) + "-" + QString::number(d));
        if (me.RSP() == -1) {
            ui->labelMESpring->setText("Spring: " + QString::number(100));
        }
        else {
            ui->labelMESpring->setText("Spring: " + QString::number(me.RSP()));
        }
        if (me.RBA() == -1) {
            ui->labelMEBattery->setText("Battery: 100%");
        }
        else {
            ui->labelMEBattery->setText("Battery: " + QString::number(me.RBA()) + "%");
        }
    }
}

void MainWindow::MakeConnection(Dialog* di)
{
    d = di;
    connect(di, SIGNAL(sendData(int, int, int, int, int, int, int, int, int)), this, SLOT(getData(int, int, int, int, int, int, int, int, int)));
    connect(di, SIGNAL(sendData(int, int, int)), ui->widget, SLOT(getData(int, int, int)));
    connect(di, SIGNAL(sendData(int, int, int)), ui->widget_2, SLOT(getData(int, int, int)));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(Stop()));
}

void MainWindow::on_pushButton_2_clicked()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::TFAction);
    timer->setInterval(1000);
    timer->start();
}

void MainWindow::Stop() {
    timer->stop();
    delete timer;
    timer = new QTimer(this);
}

void MainWindow::TFAction() {
    if (a == 0) {
        if (mech.RSP() == -1) {
            mech.SecondI(1);
            ChangeTime(mech);
        }
        else if (mech.RSP() == 0) {
            Stop();
            ChangeTime(mech);
        }
        else {
            mech.SecondI(1);
            mech.SpringD();
            ChangeTime(mech);
        }
    }
    else if (a == 1) {
        if (elec.RBA() == -1) {
            elec.SecondI(1);
            ChangeTime(elec);
        }
        else if (elec.RBA() == 0) {
            Stop();
            ChangeTime(elec);
        }
        else {
            elec.SecondI(1);
            elec.BatteryD();
            ChangeTime(elec);
        }
    }
    else if (a == 2) {
        if (me.RSP() == -1) {
            if (me.RBA() == -1) {
                me.SecondI(1);
                ChangeTime(me);
            }
            else if (me.RBA() == 0) {
                Stop();
            }
            else {
                me.SecondI(1);
                ChangeTime(me);
                me.BatteryD();
            }
        }
        else if (me.RSP() == 0) {
            Stop();
            ChangeTime(me);
        }
        else {
            me.SpringD();
            if (me.RBA() == -1) {
                me.SecondI(1);
                ChangeTime(me);
            }
            else if (me.RBA() == 0) {
                Stop();
            }
            else {
                me.SecondI(1);
                me.BatteryD();
                ChangeTime(me);
            }
        }
    }
}

void MainWindow::ChangeTime(MechClock mech) {
    RenderTime();
}

void MainWindow::ChangeTime(ElecClock elec) {
    RenderTime();
}

void MainWindow::ChangeTime(MEClock me) {
    RenderTime();
}

void MainWindow::RenderTime() {
    if (a == 0) {
        ui->lcdNumber->display(mech.RH());
        ui->lcdNumber_2->display(mech.RM());
        ui->lcdNumber_3->display(mech.RS());
        ui->labelMechDate->setText(QString::number(mech.RY()) + "-" + QString::number(mech.RMon()) + "-" + QString::number(mech.RD()));
        ui->widget->ChangeTime(mech.RH(), mech.RM(), mech.RS());
        if (mech.RSP() == -1) {
            ui->labelMechSpring->setText("Spring: " + QString::number(100));
        }
        else {
            ui->labelMechSpring->setText("Spring: " + QString::number(mech.RSP()));
        }
        ui->widget->update();
        //ui->labelPrice->setText("$" + QString::number(c1.RP()));
        //ui->labelBrand->setText(QString::fromStdString(c1.RB()));
    }
    else if (a == 1) {
        ui->lcdNumber->display(elec.RH());
        ui->lcdNumber_2->display(elec.RM());
        ui->lcdNumber_3->display(elec.RS());
        ui->labelDate->setText(QString::number(elec.RY()) + "-" + QString::number(elec.RMon()) + "-" + QString::number(elec.RD()));
        if (elec.RBA() == -1) {
            ui->labelElecBattery->setText("Battery: 100%");
        }
        else {
            ui->labelElecBattery->setText("Battery: " + QString::number(elec.RBA()) + "%");
        }
        //ui->labelPrice->setText("$" + QString::number(c1.RP()));
        //ui->labelBrand->setText(QString::fromStdString(c1.RB()));
    }
    else if (a == 2) {
        ui->lcdNumber_4->display(me.RH());
        ui->lcdNumber_5->display(me.RM());
        ui->lcdNumber_6->display(me.RS());
        ui->labelMEDate->setText(QString::number(me.RY()) + "-" + QString::number(me.RMon()) + "-" + QString::number(me.RD()));
        if (me.RSP() == -1) {
            ui->labelMESpring->setText("Spring: " + QString::number(100));
        }
        else {
            ui->labelMESpring->setText("Spring: " + QString::number(me.RSP()));
        }
        if (me.RBA() == -1) {
            ui->labelMEBattery->setText("Battery: 100%");
        }
        else {
            ui->labelMEBattery->setText("Battery: " + QString::number(me.RBA()) + "%");
        }
        ui->widget_2->ChangeTime(me.RH(), me.RM(), me.RS());
        ui->widget_2->update();
        //ui->labelPrice->setText("$" + QString::number(c1.RP()));
        //ui->labelBrand->setText(QString::fromStdString(c1.RB()));
    }
}
