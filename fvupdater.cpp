#include "fvupdater.h"
#include "fvupdatewindow.h"

#ifdef FV_DEBUG
// Unit tests
#include "fvversioncomparatortest.h"
#endif


FvUpdater* FvUpdater::m_Instance = 0;


FvUpdater* FvUpdater::sharedUpdater()
{
	static QMutex mutex;
	if (! m_Instance) {
		mutex.lock();

		if (! m_Instance) {
			m_Instance = new FvUpdater;
		}

		mutex.unlock();
	}

	return m_Instance;
}

void FvUpdater::drop()
{
	static QMutex mutex;
	mutex.lock();
	delete m_Instance;
	m_Instance = 0;
	mutex.unlock();
}

FvUpdater::FvUpdater() : QObject(0)
{
	m_updaterWindow = 0;

#ifdef FV_DEBUG
	// Unit tests
	FvVersionComparatorTest* test = new FvVersionComparatorTest();
	test->runAll();
	delete test;
#endif

}

FvUpdater::~FvUpdater()
{
	destroyUpdaterWindow();
}

void FvUpdater::destroyUpdaterWindow()
{
	if (m_updaterWindow) {
		m_updaterWindow->hide();
		delete m_updaterWindow;
		m_updaterWindow = 0;
	}
}


bool FvUpdater::CheckForUpdates(bool notifyAboutUpToDateApplication)
{
	destroyUpdaterWindow();

	m_updaterWindow = new FvUpdateWindow();
	m_updaterWindow->show();

	return true;
}
