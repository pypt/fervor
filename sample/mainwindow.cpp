#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fvupdater.h"
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Connect the "check for updates manually" button with the autoupdater
	connect(ui->updateButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(CheckForUpdatesNotSilent()));

	ui->label->setText( tr("Version %1").arg(QApplication::applicationVersion()) );
}

MainWindow::~MainWindow()
{
	delete ui;
}