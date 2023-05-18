#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);

}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::on_buttonBox_accepted()
{
	int c, y, m, d, h, mi, s, e1, e2;
	y = m = d = h = mi = s = e1 = e2 = 3;
	c = 0;
	c = ui->comboBox->currentIndex();
	y = ui->spinYear->value();
	m = ui->spinMonth->value();
	d = ui->spinDay->value();
	h = ui->spinHour->value();
	mi = ui->spinMinute->value();
	s = ui->spinSecond->value();
	if (c == 0) {
		e2 = ui->spinMechSpring->value();
	}
	else if (c == 1) {
		e1 = ui->spinElecBattery->value();
	}
	else if (c == 2) {
		e1 = ui->spinMEBattery->value();
		e2 = ui->spinMESpring->value();
	}
	emit sendData(c, y, m, d, h, mi, s, e1, e2);
	emit sendData(h, mi, s);
}

void Dialog::on_comboBox_currentIndexChanged(int index)
{
	ui->stackedWidget->setCurrentIndex(index);
}

