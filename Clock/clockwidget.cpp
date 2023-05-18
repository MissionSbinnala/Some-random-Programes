#include "clockwidget.h"

clockwidget::clockwidget(QWidget *parent) : QWidget(parent)
{

}

clockwidget::~clockwidget()
{

}

void clockwidget::getData(int h, int m, int s) {
    time.setsecond(s);
    time.setminute(m);
    time.sethour(h);
}

void clockwidget::ChangeTime(int h, int m, int s) {
    time.setsecond(s);
    time.setminute(m);
    time.sethour(h);
}
