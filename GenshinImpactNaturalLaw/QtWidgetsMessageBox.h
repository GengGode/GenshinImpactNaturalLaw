#pragma once
#include <QWidget>
#include "ui_QtWidgetsMessageBox.h"

class QtWidgetsMessageBox : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsMessageBox(QWidget *parent = Q_NULLPTR);
	~QtWidgetsMessageBox();

public:
	void setMessage(QString message);
private:
	Ui::QtWidgetsMessageBox ui;

private slots:
	void cancel_and_close();
	void ok_and_close();
signals:
	void signal_cancel();
	void signal_ok();
};
