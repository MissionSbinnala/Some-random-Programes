#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QPainter>
#include <QWidget>
#include <QtMath>
#include <QTime>

class Times {
private:
    int h, m, s;
public:
    Times(int ho, int mi, int se) {
        h = ho;
        m = mi;
        s = se;
    }
    Times() {}
    int hour() {
        return h;
    }
    int minute() {
        return m;
    }
    int second() {
        return s;
    }
    void sethour(int ho) {
        h = ho;
    }
    void setminute(int mi) {
        m = mi;
    }
    void setsecond(int se) {
        s = se;
    }
};

class clockwidget : public QWidget
{
    Q_OBJECT
public:
    explicit clockwidget(QWidget *parent = 0);
    ~clockwidget();
    void ChangeTime(int h, int m, int s);
    QRectF textRectF(double radius, int pointSize, double angle)
        {
            QRectF rectF;
            rectF.setX(radius * qCos(angle * M_PI / 180.0) - pointSize * 2);
            rectF.setY(radius * qSin(angle * M_PI / 180.0) - pointSize / 2.0);
            rectF.setWidth(pointSize * 4);
            rectF.setHeight(pointSize);
            return rectF;
        }
    void paintEvent(QPaintEvent* event)
        {
            Q_UNUSED(event);

            static const QPoint hourHand[3] = {
                QPoint(7, 8),
                QPoint(-7, 8),
                QPoint(0, -30)
            };
            static const QPoint minuteHand[3] = {
                QPoint(7, 8),
                QPoint(-7, 8),
                QPoint(0, -65)
            };

            static const QPoint secondHand[3] = {
                QPoint(7, 8),
                QPoint(-7, 8),
                QPoint(0, -80)
            };


            QColor hourColor(200, 100, 0, 200);
            QColor minuteColor(0, 127, 127, 150);
            QColor secondColor(0, 160, 230, 150);

            int side = qMin(width(), height());

            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            painter.translate(width() / 2, height() / 2);

            painter.scale(side / 200.0, side / 200.0);

            painter.setPen(Qt::NoPen);
            painter.setBrush(hourColor);

            painter.save();

            painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
            painter.drawConvexPolygon(hourHand, 3);
            painter.restore();

            painter.setPen(hourColor);


            for (int i = 0; i < 12; ++i) {
                painter.drawLine(88, 0, 96, 0);
                painter.rotate(30.0);
            }

            int radius = 100;
            QFont font = painter.font();
            font.setBold(true);
            painter.setFont(font);
            int pointSize = font.pointSize();


            int nHour = 0;
            for (int i = 0; i < 12; ++i) {
                nHour = i + 3;
                if (nHour > 12)
                    nHour -= 12;
                painter.drawText(textRectF(radius * 0.8, pointSize * 2, i * 30), Qt::AlignCenter, QString::number(nHour));
            }


            painter.setPen(Qt::NoPen);
            painter.setBrush(minuteColor);

            painter.save();

            painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
            painter.drawConvexPolygon(minuteHand, 3);
            painter.restore();

            painter.setPen(minuteColor);


            for (int j = 0; j < 60; ++j) {
                if ((j % 5) != 0)
                    painter.drawLine(92, 0, 96, 0);
                painter.rotate(6.0);
            }


            painter.setPen(Qt::NoPen);
            painter.setBrush(secondColor);

            painter.save();

            painter.rotate(6.0 * time.second());
            painter.drawConvexPolygon(secondHand, 3);
            painter.restore();
        }

    private slots:
        void getData(int h, int m, int s);

    private:
        Times time;

signals:

public slots:
};

#endif // CLOCKWIDGET_H
