#include "VersionNumber.h"

VersionNumber::VersionNumber()
{
}

VersionNumber::~VersionNumber()
{
}

VersionNumber::operator QString()
{
	return QString::number(Major_Version_Number) + "." +
		QString::number(Minor_Version_Number)+ "." + 
		QString::number(Revision_Number);
}

VersionNumber & VersionNumber::operator=(const QString & versionString)
{
	VersionString = versionString;
	tryToNumber(versionString);
	return *this;
}

bool VersionNumber::operator==(const VersionNumber & version)
{
	if (Revision_Number == version.Revision_Number &&
		Minor_Version_Number == version.Minor_Version_Number &&
		Major_Version_Number == version.Major_Version_Number)
	{
		return true;
	}
	return false;
}

bool VersionNumber::operator!=(const VersionNumber & version)
{
	if (Revision_Number == version.Revision_Number &&
		Minor_Version_Number == version.Minor_Version_Number &&
		Major_Version_Number == version.Major_Version_Number)
	{
		return false;
	}
	return true;
}

bool VersionNumber::operator>(const VersionNumber & version)
{
	if (Major_Version_Number > version.Major_Version_Number)
	{
		return true;
	}
	if (Minor_Version_Number > version.Minor_Version_Number)
	{
		return true;
	}
	if (Revision_Number > version.Revision_Number)
	{
		return true;
	}
	return false;
}

bool VersionNumber::operator<(const VersionNumber & version)
{
	if (Major_Version_Number < version.Major_Version_Number)
	{
		return true;
	}
	if (Minor_Version_Number < version.Minor_Version_Number)
	{
		return true;
	}
	if (Revision_Number < version.Revision_Number)
	{
		return true;
	}
	return false;
}

bool VersionNumber::operator>=(const VersionNumber & version)
{
	if (*this == version)
	{
		return true;
	}
	if (*this > version)
	{
		return true;
	}
	return false;
}

bool VersionNumber::operator<=(const VersionNumber & version)
{
	if (*this == version)
	{
		return true;
	}
	if (*this < version)
	{
		return true;
	}
	return false;
}

int VersionNumber::main()
{
	return Major_Version_Number;
}

int VersionNumber::branch()
{
	return Minor_Version_Number;
}

int VersionNumber::revision()
{
	return Revision_Number;
}

bool VersionNumber::tryToNumber(QString str)
{
	if (str == "")
	{
		return false;
	}
	QStringList VersionStringList = str.split(".");
	if (VersionStringList.size() != 3)
	{
		return false;
	}
	Major_Version_Number = VersionStringList[0].toInt();
	Minor_Version_Number = VersionStringList[1].toInt();
	Revision_Number = VersionStringList[2].toInt();
	return true;
}
