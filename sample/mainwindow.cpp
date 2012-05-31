#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fvupdater.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->updateButton, SIGNAL(clicked()), FvUpdater::sharedUpdater(), SLOT(CheckForUpdates()));
}

MainWindow::~MainWindow()
{
	delete ui;
}
