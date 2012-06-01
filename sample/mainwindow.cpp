#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fvupdater.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Set feed URL before doing anything else
	FvUpdater::sharedUpdater()->SetFeedURL("https://raw.github.com/pypt/fervor/master/sample/Appcast.xml");

	// Connect the "check for updates" button with the autoupdater
	connect(ui->updateButton, SIGNAL(clicked()), FvUpdater::sharedUpdater(), SLOT(CheckForUpdates()));
}

MainWindow::~MainWindow()
{
	delete ui;
}
