#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
	class Dialog;
}

class Dialog : public QDialog
{
	Q_OBJECT

public:
    explicit Dialog(QWidget* parent = 0);
	~Dialog();
	void ChangeStacked(int a);

signals:
	void sendData(int, int, int, int, int, int, int, int, int);
	void sendData(int, int, int);

private slots:
	void on_buttonBox_accepted();
	void on_comboBox_currentIndexChanged(int index);

private:
	Ui::Dialog* ui;
};
#endif // DIALOG_H
