#include "QtWidgetsSetting.h"
//#pragma execution_character_set("utf-8")
#include "version/Version.h"
#include "define/Api.h"
#include <cpr/cpr.h>
#ifdef _DEBUG
#pragma comment(lib, "3rdpart/cpr/lib/cprd.lib")
#pragma comment(lib, "3rdpart/cpr/lib/libcurld.lib")							
#pragma comment(lib, "3rdpart/cpr/lib/zlibd.lib")
#pragma comment(lib, "3rdpart/cpr/lib/nghttp2d.lib")
#else
#pragma comment(lib, "3rdpart/cpr/lib/cpr.lib")
#pragma comment(lib, "3rdpart/cpr/lib/libcurl.lib")							
#pragma comment(lib, "3rdpart/cpr/lib/zlib.lib")
#pragma comment(lib, "3rdpart/cpr/lib/nghttp2.lib")
#endif
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")

#include "QtWidgetsMessageBox.h"

QtWidgetsSetting::QtWidgetsSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);

	uiConnectButton();

	scrBar = ui.scrollArea_Main->verticalScrollBar();
	connect(scrBar, &QScrollBar::valueChanged, this, &QtWidgetsSetting::BarMove_ChangeButton);

	connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(CloseSelf()));
	connect(ui.pushButton_Cancel, SIGNAL(clicked()), this, SLOT(Cancel()));
	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(OK()));

	connect(ui.radioButton_Setting_0, SIGNAL(clicked()), this, SLOT(RadioButton_SettingExitOrMini()));
	connect(ui.radioButton_Setting_1, SIGNAL(clicked()), this, SLOT(RadioButton_SettingExitOrMini()));
	
	connect(ui.checkBox_Setting_0, SIGNAL(stateChanged(int)), this, SLOT(CheckBox_SettingAutoRun(int)));
	connect(ui.checkBox_Setting_1, SIGNAL(stateChanged(int)), this, SLOT(CheckBox_SettingPupoGame(int)));
	connect(ui.checkBox_Setting_2, SIGNAL(stateChanged(int)), this, SLOT(CheckBox_SettingRunModule(int)));
	
	connect(ui.pushButton_Check_1, SIGNAL(clicked()), this, SLOT(CheckOptions_CheckGameLauncher()));
	connect(ui.pushButton_Check_2, SIGNAL(clicked()), this, SLOT(CheckOptions_CheckGame()));
	connect(ui.pushButton_Check_3, SIGNAL(clicked()), this, SLOT(CheckOptions_CheckModule()));
	connect(ui.pushButton_Check_4, SIGNAL(clicked()), this, SLOT(CheckOptions_RefreshModule()));
	connect(ui.pushButton_Check_5, SIGNAL(clicked()), this, SLOT(CheckOptions_UpdataLauncher()));
	connect(ui.pushButton_Check_6, SIGNAL(clicked()), this, SLOT(CheckOptions_UpdataGameLauncher()));
	connect(ui.pushButton_Check_7, SIGNAL(clicked()), this, SLOT(CheckOptions_UpdataGame()));

	
	ui.label_Label_5->setText(KeyString1 + tl::launcher::version::build_version);
	
}

QtWidgetsSetting::~QtWidgetsSetting()
{
}

void QtWidgetsSetting::uiConnectButton()
{
	UIButtonList.clear();
	UIButtonList.push_back(ui.pushButton_UI_GeneralSetting);
	UIButtonList.push_back(ui.pushButton_UI_GameSetting);
	UIButtonList.push_back(ui.pushButton_UI_ModuleSetting);
	UIButtonList.push_back(ui.pushButton_UI_ModuleResource);
	UIButtonList.push_back(ui.pushButton_UI_VersionInformation);

	ScrollLabelList.clear();
	ScrollLabelList.push_back(ui.label_Title_0);
	ScrollLabelList.push_back(ui.label_Title_1);
	ScrollLabelList.push_back(ui.label_Title_2);
	/************************************************************************************************************************************/
	ScrollLabelList.push_back(ui.label_Title_2);
	/************************************************************************************************************************************/
	ScrollLabelList.push_back(ui.label_Title_3);

	for (int i = 0; i < UIButtonList.size(); i++)
	{
		connect(UIButtonList[i], SIGNAL(clicked()), this, SLOT(SwitchOptions()));
	}
}

void QtWidgetsSetting::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton &&
		ui.TitleLabelRect->frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())) {
		m_Press = event->globalPos();
		leftBtnClk = true;
	}
	event->ignore();
}

void QtWidgetsSetting::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		leftBtnClk = false;
	}
	event->ignore();
}
void QtWidgetsSetting::mouseMoveEvent(QMouseEvent *event)
{
	if (leftBtnClk) {
		m_Move = event->globalPos();
		this->move(this->pos() + m_Move - m_Press);
		m_Press = m_Move;
	}
	event->ignore();
}

void QtWidgetsSetting::SetSetting(SettingData *setting)
{
	this->setting = setting;

	emit UpdataShowOptions();
}

void QtWidgetsSetting::SetModules(ModulesManager *modules)
{
	this->modules = modules;

	emit UpdataModulesOptions();
}

void QtWidgetsSetting::UpdataShowOptions()
{
	ui.checkBox_Setting_0->setChecked(setting->is_auto_run);
	ui.checkBox_Setting_1->setChecked(setting->is_start_pupowindows);
	ui.checkBox_Setting_2->setChecked(setting->is_start_module);
	ui.radioButton_Setting_0->setChecked(setting->is_exit_ismini);
	ui.radioButton_Setting_1->setChecked(!setting->is_exit_ismini);
	ui.lineEdit_Path_1->setText(setting->launcher_install_path.replace(QRegExp("/"), "\\"));
	ui.lineEdit_Path_2->setText(setting->game_install_path.replace(QRegExp("/"), "\\"));
}

void QtWidgetsSetting::UpdataModulesOptions()
{
	QStringList ModsName = modules->getModuleNameList();

	if (ModulesSubVBoxLayout == nullptr)
	{
		 ModulesSubVBoxLayout = new QVBoxLayout;
		 ModulesSubVBoxLayout->setSpacing(12);
	}

	for (int i = 0; i < ModulesItemCheckBoxList.size(); i++)
	{
		delete ModulesItemCheckBoxList[i];
		ModulesItemCheckBoxList[i] = nullptr;
	}
	ModulesItemCheckBoxList.clear();

	setting->is_start_mods_list.resize(ModsName.size(), false);
	setting->mods_number = (int)setting->is_start_mods_list.size();

	for (int i = 0; i < ModsName.size(); i++)
	{
		QString ModName = ModsName[i].section(".", 0, -2);

		QCheckBox *newQCheckBox = new QCheckBox();

		newQCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
			"	font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
			"	color: rgb(57, 59, 64);\n"
			"	spacing: 10px;\n"
			"}\n"
			"QCheckBox::indicator {\n"
			"	width: 24px;\n"
			"	height: 24px;\n"
			"}\n"
			"QCheckBox::indicator:unchecked {\n"
			"    image: url(:/CheckBox/resource/QtWidgetsSetting/CheckBox/checkbox_unchecked.png);\n"
			"}\n"
			"\n"
			"QCheckBox::indicator:unchecked:hover {\n"
			"    image: url(:/CheckBox/resource/QtWidgetsSetting/CheckBox/checkbox_unchecked_hover.png);\n"
			"}\n"
			"\n"
			"QCheckBox::indicator:unchecked:pressed {\n"
			"    image: url(:/CheckBox/resource/QtWidgetsSetting/CheckBox/checkbox_unchecked_pressed.png);\n"
			"}\n"
			"\n"
			"QCheckBox::indicator:checked {\n"
			"    image: url(:/CheckBox/resource/QtWidgetsSetting/CheckBox/checkbox_checked.png);\n"
			"}\n"
			"\n"
			"QCheckBox::indicator:checked:hover {\n"
			"    image: url(:/CheckBox/resource/QtWidgetsSetting/CheckBox/checkbox_checked_hover.png);\n"
			"}\n"
			"\n"
			"QCheckBox::indicator:checked:pressed {\n"
			"    image: url(:/CheckBox/resource/QtWidgetsSettin"
			"g/CheckBox/checkbox_checked_pressed.png);\n"
			"}\n"
			""));
		newQCheckBox->setText(ModName);
		newQCheckBox->setChecked(setting->is_start_mods_list[i]);
		connect(newQCheckBox, &QCheckBox::stateChanged, this, &QtWidgetsSetting::CheckBox_SettingModulesOptions);

		ModulesSubVBoxLayout->addWidget(newQCheckBox);

		ModulesItemCheckBoxList.push_back(newQCheckBox);
	}

	ui.widget_ModulesRect->setLayout(ModulesSubVBoxLayout);
	ui.widget_ModulesRect->setFixedHeight(36 * (ModsName.size() + 1));
	ui.widget_ModulesRect->show();

	ui.scrollAreaWidgetContents_ModulesSub->setMinimumHeight(36 * (ModsName.size() + 1));
	ui.scrollAreaWidgetContents_ModulesSub->setMaximumHeight(36 * (ModsName.size() + 1));
	
	QScrollBar *scrBar = ui.scrollArea_ModulesSub->verticalScrollBar();
	scrBar->setStyleSheet("QScrollBar::handle:vertical {min-height: auto;}");

}

void QtWidgetsSetting::CloseSelf()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::Cancel()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::OK()
{
	if (!setting->trySetAutoRun())
	{
		setting->is_auto_run = !setting->is_auto_run;
	}
	setting->sync();

	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::SwitchOptions()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	for (int i = 0; i < UIButtonList.size(); i++)
	{
		if (btn == UIButtonList[i])
		{
			QPropertyAnimation *scrBarAni = new QPropertyAnimation(scrBar, "value");
			connect(scrBarAni, &QPropertyAnimation::finished, scrBarAni, &QPropertyAnimation::deleteLater);
			scrBarAni->setStartValue(scrBar->value());
			scrBarAni->setEndValue(ScrollLabelList[i]->y());
			scrBarAni->setDuration(150);
			scrBarAni->start();
		}
	}
}

void QtWidgetsSetting::BarMove_ChangeButton()
{
	for (int i = 0; i < ScrollLabelList.size(); i++)
	{
		if (scrBar->value() > ScrollLabelList[i]->y()-60)
		{
			UIButtonList[i]->setChecked(true);
		}
	}
}

void QtWidgetsSetting::UpdataLauncher_GetUrlVersion()
{
	QString filePath = QApplication::applicationDirPath() + "/download/";
	QString fileName = "version.tag";
	QString savePath = filePath + fileName;

	QString line = "0.0.0";
	QFile readVer(savePath);
	if (!readVer.open(QIODevice::ReadOnly | QIODevice::Text))
	{

	}
	else
	{
		line = readVer.readLine();
	}

	VersionNumber newVer(line);

	if (newVer > myVersion)
	{
		QString command = "\"" + QApplication::applicationDirPath() +"/update/UpdateProgram.exe" + "\"";
		TCHAR szCmdLine[1024] = {};

		command.toWCharArray(szCmdLine);
		STARTUPINFO si;
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi;

		bool res = CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

		if (res != true)
		{
			int k = GetLastError();
		}

		emit SendCloseAllSignalToMainWidgets();
		this->OK();
	}
	else
	{
		this->OK();
	}
}

void QtWidgetsSetting::ShowMessageBox()
{
	if (WidgetsMessageBox == nullptr)
	{
		WidgetsMessageBox = new QtWidgetsMessageBox();
		connect(WidgetsMessageBox, &QtWidgetsMessageBox::signal_cancel, this, &QtWidgetsSetting::ReceiveCloseSelfSignalFromWidgetsMessageBox);
		connect(WidgetsMessageBox,&QtWidgetsMessageBox::signal_ok, this, &QtWidgetsSetting::ReceiveCloseSelfSignalFromWidgetsMessageBox);

		WidgetsMessageBox->setWindowModality(Qt::ApplicationModal);
		WidgetsMessageBox->move(this->x() + 145, this->y() + 85);
		WidgetsMessageBox->show();
	}
	else
	{
		WidgetsMessageBox->move(this->x() + 145, this->y() + 85);
		WidgetsMessageBox->show();
	}
	if (MainMaskLabel == nullptr)
	{
		MainMaskLabel = new QLabel(this);
		MainMaskLabel->setText("");
		MainMaskLabel->setGeometry(QRect(0, 0, 820, 524));
		MainMaskLabel->setStyleSheet("background-color:rgba(0, 0, 0, 120);");
		MainMaskLabel->show();
	}
	else
	{
		MainMaskLabel->show();
	}
}

void QtWidgetsSetting::CheckBox_SettingAutoRun(int arg)
{
	if (arg == 2)
	{
		setting->is_auto_run = true;
	}
	else if (arg == 0)
	{
		setting->is_auto_run = false;
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckBox_SettingPupoGame(int arg)
{
	if (arg == 2)
	{
		setting->is_start_pupowindows = true;
	}
	else if (arg == 0)
	{
		setting->is_start_pupowindows = false;
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckBox_SettingRunModule(int arg)
{
	if (arg == 2)
	{
		setting->is_start_module = true;
	}
	else if (arg == 0)
	{
		setting->is_start_module = false;
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::RadioButton_SettingExitOrMini()
{
	QRadioButton *btn = qobject_cast<QRadioButton*>(sender());
	if (btn == ui.radioButton_Setting_0)
	{
		if (btn->isChecked() == true)
		{
			setting->is_exit_ismini = true;
		}
	}
	if (btn == ui.radioButton_Setting_1)
	{
		if (btn->isChecked() == true)
		{
			setting->is_exit_ismini = false;
		}
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckOptions_CheckGameLauncher()
{
	QString FileDialogPath = "./";
	if (setting->launcher_install_path != "")
	{
		FileDialogPath = setting->launcher_install_path;
	}
	QString GameLauncherPath = QFileDialog::getOpenFileName(this, tr("Str_SelectGILauncherPath")/*"选择原神所在目录"*/, FileDialogPath, tr("Str_ApplicationProgram") + " (*.exe);;"/* "应用程序 (*.exe);;"*/);

	//QString GameLauncherPath = QFileDialog::getExistingDirectory(this, tr("Str_SelectGILauncherPath")/*"选择原神启动器所在目录"*/, FileDialogPath, QFileDialog::ShowDirsOnly);
	
	if (!GameLauncherPath.isEmpty())
	{
		GameLauncherPath = GameLauncherPath.section("/", 0, -2);
		QFileInfo file(GameLauncherPath+"/launcher.exe");
		if (file.exists() == false)
		{
			emit ShowMessageBox();//未能找到游戏本体，请重新选择游戏本体路径
			return;
		}
		else
		{
			setting->launcher_install_path = GameLauncherPath;
			if (!setting->tryGetGamePath())
			{
				emit ShowMessageBox();//未能找到游戏本体，请手动选择游戏本体路径
				return;
			}
		}
	}
	else
	{
		return;
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckOptions_CheckGame()
{
	QString FileDialogPath = "./";
	if (setting->game_install_path != "")
	{
		FileDialogPath = setting->game_install_path;
	}
	QString GamePath = QFileDialog::getOpenFileName(this, tr("Str_SelectGIPath")/*"选择原神所在目录"*/, FileDialogPath,tr("Str_ApplicationProgram")+" (*.exe);;"/* "应用程序 (*.exe);;"*/);
	if (!GamePath.isEmpty()) 
	{
		setting->game_start_name = GamePath.section('/', -1);
		setting->game_install_path = GamePath.section('/', 0, -2);
	}
	else
	{
		return;
	}

	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckOptions_CheckModule()
{
	QString FileDialogPath = "./";
	if (setting->launcher_install_path != "")
	{
		FileDialogPath = setting->launcher_install_path;
	}
	QString GameLauncherPath = QFileDialog::getExistingDirectory(this, tr("Str_SelectGILauncherPath")/*"选择原神启动器所在目录"*/, FileDialogPath, QFileDialog::ShowDirsOnly);

	if (!GameLauncherPath.isEmpty())
	{
		QFileInfo file(GameLauncherPath + "/launcher.exe");
		if (file.exists() == false)
		{
			emit ShowMessageBox();//未能找到游戏本体，请重新选择游戏本体路径
			return;
		}
		else
		{
			setting->launcher_install_path = GameLauncherPath;
			if (!setting->tryGetGamePath())
			{
				emit ShowMessageBox();//未能找到游戏本体，请手动选择游戏本体路径
				return;
			}
		}
	}
	else
	{
		return;
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckOptions_RefreshModule()
{
	modules->refresh();

	emit UpdataModulesOptions();
}

void QtWidgetsSetting::CheckOptions_UpdataLauncher()
{
	cpr::Session session;
	session.SetVerifySsl(false);
	
	session.SetUrl(tl::launcher::api::version_url);
	auto r = session.Get();
	if (r.status_code ==200)
	{
		net_version = r.text;
	}
	if (VersionNumber(tl::launcher::version::version) < VersionNumber(net_version.c_str()))
	{
		// 检测到存在更新
		static QtWidgetsMessageBox* message_box = nullptr;

		if (MainMaskLabel == nullptr)
		{
			MainMaskLabel = new QLabel(this);
			MainMaskLabel->setText("");
			MainMaskLabel->setGeometry(QRect(0, 0, 820, 524));
			MainMaskLabel->setStyleSheet("background-color:rgba(0, 0, 0, 120);");
			MainMaskLabel->show();
		}
		else
		{
			MainMaskLabel->show();
		}
		if (message_box == nullptr)
		{
			message_box = new QtWidgetsMessageBox(this);
			message_box->setWindowModality(Qt::ApplicationModal);
			connect(message_box, &QtWidgetsMessageBox::signal_cancel, [=]() {
				//qDebug() << "kais gengxin";
				MainMaskLabel->hide();
			//MainMaskLabel->deleteLater();
				});
			connect(message_box, &QtWidgetsMessageBox::signal_ok, [=]() {
				//qDebug() << "kais gengxin";
				MainMaskLabel->hide();
				//MainMaskLabel->deleteLater();
				});
			message_box->setMessage(tr("Str_SelectIsUpdateNow"));

			message_box->move( 145, 85);
			message_box->show();
		}
		else
		{
			message_box->setWindowModality(Qt::ApplicationModal);
			message_box->move(this->x() + 145, this->y() + 85);
			message_box->show();
		}

	}
}

void QtWidgetsSetting::CheckOptions_UpdataGameLauncher()
{

}

void QtWidgetsSetting::CheckOptions_UpdataGame()
{

}

void QtWidgetsSetting::CheckBox_SettingModulesOptions(int arg)
{
	QCheckBox *cbtObj = qobject_cast<QCheckBox*>(sender());
	for (int i = 0; i < ModulesItemCheckBoxList.size(); i++)
	{
		if (cbtObj == ModulesItemCheckBoxList[i])
		{
			if (arg == 2)
			{
				setting->is_start_mods_list[i] = true;
			}
			else if (arg == 0)
			{
				setting->is_start_mods_list[i] = false;
			}
			emit UpdataShowOptions();
		}
	}
}

void QtWidgetsSetting::ReceiveCloseSelfSignalFromWidgetsMessageBox()
{
	MainMaskLabel->hide();
}

