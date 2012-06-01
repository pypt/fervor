#include "fvupdateconfirmdialog.h"
#include "ui_fvupdateconfirmdialog.h"

FvUpdateConfirmDialog::FvUpdateConfirmDialog(QWidget *parent) :
	QDialog(parent),
	m_ui(new Ui::FvUpdateConfirmDialog)
{
	m_ui->setupUi(this);
}

FvUpdateConfirmDialog::~FvUpdateConfirmDialog()
{
	delete m_ui;
}
