#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fvupdatewindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	updateWindow = new FvUpdateWindow();

	connect(ui->updateButton, SIGNAL(clicked()), updateWindow, SLOT(show()));
}

MainWindow::~MainWindow()
{
	delete ui;
	delete updateWindow;
}
