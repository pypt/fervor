#ifndef FVUPDATER_H
#define FVUPDATER_H

#include <QObject>
#include <QMutex>
class FvUpdateWindow;


class FvUpdater : public QObject
{
	Q_OBJECT

public:

	// Singleton
	static FvUpdater* sharedUpdater();
	static void drop();
	
public slots:

	// Check for updates
	bool CheckForUpdates(bool notifyAboutUpToDateApplication = false);

private:

	// Hide main constructor
	FvUpdater();
	~FvUpdater();

	// Hide copy constructor
	FvUpdater(const FvUpdater&);

	// Hide assign op
	// we leave just the declarations, so the compiler will warn us
	// if we try to use those two functions by accident
	FvUpdater& operator=(const FvUpdater&);

	// Singleton instance
	static FvUpdater* m_Instance;

	// Updater window
	FvUpdateWindow* m_updaterWindow;

	void destroyUpdaterWindow();
	
};

#endif // FVUPDATER_H
