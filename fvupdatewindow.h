#ifndef FVUPDATEWINDOW_H
#define FVUPDATEWINDOW_H

#include <QWidget>

namespace Ui {
class FvUpdateWindow;
}

class FvUpdateWindow : public QWidget
{
	Q_OBJECT
	
public:
	explicit FvUpdateWindow(QWidget *parent = 0);
	~FvUpdateWindow();

	// Update the current update proposal from FvUpdater
	bool UpdateWindowWithCurrentProposedUpdate();

private:
	Ui::FvUpdateWindow*	m_ui;

};

#endif // FVUPDATEWINDOW_H
