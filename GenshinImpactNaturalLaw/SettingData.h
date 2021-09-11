#pragma once

#include <QApplication>
#include <QDir>
#include <QSettings>
#include <vector>
using namespace std;

class SettingData
{
	QSettings *IniSettingFile = nullptr;

public:
	// [General]
	bool is_auto_run = false;
	bool is_start_pupowindows = true;
	bool is_start_module = true;
	bool is_exit_ismini = false;
	QString launcher_install_path = "E:/Genshin Impact/";
	QString game_dynamic_bg_name = "000.gif";
	QString game_install_path = "E:/Genshin Impact/Genshin Impact Game/";
	QString game_start_name = "YuanShen.exe";
	QString parm_borderless = " -popupwindow";
	bool is_first_exit = false;
	int mods_number = 0;
	vector<bool> is_start_mods_list;

public:
	SettingData();
	~SettingData();
	SettingData& operator=(const SettingData& setting);

	void sync();

	bool tryGetGamePath();
	bool trySetAutoRun();

	QString gamepath();
	QString Command_NoBorderStartGame();
	QString Command_StartGame();


};

