#pragma once
#include <QStringList>
#include <QString>
class VersionNumber
{
	QString VersionString;
	int Major_Version_Number = 0;
	int Minor_Version_Number = 0;
	int Revision_Number = 0;

public:
	VersionNumber();
	~VersionNumber();
	operator QString();
	VersionNumber& operator=(const QString & versionString);
	bool operator==(const VersionNumber & version);
	bool operator!=(const VersionNumber & version);
	bool operator>(const VersionNumber & version);
	bool operator<(const VersionNumber & version);
	bool operator>=(const VersionNumber & version);
	bool operator<=(const VersionNumber & version);

	int main();
	int branch();
	int revision();

private:
	bool tryToNumber(QString str);
};

