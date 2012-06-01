#ifndef FVIGNOREDVERSIONS_H
#define FVIGNOREDVERSIONS_H

#include <QObject>

class FVIgnoredVersions : public QObject
{
	Q_OBJECT

public:
	static bool VersionIsIgnored(QString version);
	
private:
	explicit FVIgnoredVersions(QObject *parent = 0);
	
};

#endif // FVIGNOREDVERSIONS_H
