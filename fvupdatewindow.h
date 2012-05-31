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

private:
	Ui::FvUpdateWindow*	m_ui;

	// Helpers
	void installTranslator();
};

#endif // FVUPDATEWINDOW_H
