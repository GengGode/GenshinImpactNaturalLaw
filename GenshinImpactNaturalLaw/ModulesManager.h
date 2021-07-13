#pragma once
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QString>

class ModulesManager
{
	QStringList ModuleFileList;
	QStringList ModuleExeList;
public:
	ModulesManager();
	~ModulesManager();
	void refresh();

	QStringList getModuleList();
	QStringList getModuleNameList();

};

