#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include <QString>
#include <QTimer>
#include "class.h"
#include "clockwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    Dialog* d;
    int a;
    QString user;
    QString name;
    MechClock mech;
    ElecClock elec;
    MEClock me;
    Clock c1;
    QTimer* timer;

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void MakeConnection(Dialog* di);
    void ChangeTime(MechClock mech);
    void ChangeTime(ElecClock elec);
    void ChangeTime(MEClock me);

private slots:
    void on_pushButton_clicked();
    void getData(int c, int y, int m, int d, int h, int mi, int s, int e1, int e2);
    void TFAction();
    void on_pushButton_2_clicked();
    void Stop();
    void RenderTime();

};

#endif // MAINWINDOW_H
