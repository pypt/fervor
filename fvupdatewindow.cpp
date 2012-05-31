#include "fvupdatewindow.h"
#include "ui_fvupdatewindow.h"
#include "fvupdateconfig.h"


FvUpdateWindow::FvUpdateWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FvUpdateWindow)
{
	ui->setupUi(this);
}

FvUpdateWindow::~FvUpdateWindow()
{
	delete ui;
}
