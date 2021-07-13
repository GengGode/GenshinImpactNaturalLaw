#include "ModulesManager.h"

ModulesManager::ModulesManager()
{
	refresh();
}

ModulesManager::~ModulesManager()
{
}

void ModulesManager::refresh()
{
	QDir dir;
	QString modulesPath = QApplication::applicationDirPath() + "/modules/";
	if (!dir.exists(modulesPath)) {
		dir.mkpath(modulesPath);
	}
	else
	{
		QDir modulesDir(modulesPath);
		QStringList ModulesDirList;

		modulesDir.setFilter(QDir::Dirs);

		foreach(QFileInfo fullDir, modulesDir.entryInfoList())
		{
			if (fullDir.fileName() == "." || fullDir.fileName() == "..") continue;

			ModulesDirList.append(fullDir.absoluteFilePath() + "/");

		}

		for (int i = 0; i < ModulesDirList.size(); i++)
		{
			QDir modulesExeDir(ModulesDirList[i]);
			QStringList nameFilters;
			nameFilters << "*.exe";
			QStringList moduleExe = modulesExeDir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
			ModuleFileList.append(ModulesDirList[i] + moduleExe[0]);
			ModuleExeList.append(moduleExe[0]);
		}
	}
}

QStringList ModulesManager::getModuleList()
{
	return ModuleFileList;
}

QStringList ModulesManager::getModuleNameList()
{
	return ModuleExeList;
}
