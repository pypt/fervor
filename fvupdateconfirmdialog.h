#ifndef FVUPDATECONFIRMDIALOG_H
#define FVUPDATECONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class FvUpdateConfirmDialog;
}

class FvUpdateConfirmDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit FvUpdateConfirmDialog(QWidget *parent = 0);
	~FvUpdateConfirmDialog();
	
private:
	Ui::FvUpdateConfirmDialog* m_ui;
};

#endif // FVUPDATECONFIRMDIALOG_H
