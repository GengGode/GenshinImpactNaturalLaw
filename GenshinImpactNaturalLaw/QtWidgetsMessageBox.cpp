#include "QtWidgetsMessageBox.h"

QtWidgetsMessageBox::QtWidgetsMessageBox(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

	connect(ui.pushButton_OK, &QPushButton::clicked, this, &QtWidgetsMessageBox::ok_and_close);
	connect(ui.pushButton_Cancel, &QPushButton::clicked, this, &QtWidgetsMessageBox::cancel_and_close);
}

QtWidgetsMessageBox::~QtWidgetsMessageBox()
{
}

void QtWidgetsMessageBox::setMessage(QString message)
{
	ui.label_Message->setText(message);
}

void QtWidgetsMessageBox::cancel_and_close()
{
	signal_cancel();
	close();
}

void QtWidgetsMessageBox::ok_and_close()
{
	signal_ok();
	close();
}
