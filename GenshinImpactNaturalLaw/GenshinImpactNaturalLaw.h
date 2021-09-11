#pragma once
#include <windows.h>
#include <vector>
#include <QGraphicsDropShadowEffect>
#include <QDesktopServices>
#include <QTextCodec>
#include <QTranslator>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QAction>
#include <QMenu>
#include <QMovie>
#include <QProcess>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpactNaturalLaw.h"
#include "QtWidgetsSetting.h"
#include "SettingData.h"
#include "ModulesManager.h"

class GenshinImpactNaturalLaw : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpactNaturalLaw(QWidget *parent = Q_NULLPTR);
	~GenshinImpactNaturalLaw();

private:
    Ui::GenshinImpactNaturalLawClass ui;

private:
	SettingData setting;
	ModulesManager modules;
private:
	QPoint m_Press;
	QPoint m_Move;
	bool leftBtnClk = false;

	QtWidgetsSetting *WidgetsSetting = nullptr;
	QLabel *MainMaskLabel = nullptr;
	QMenu *TrayMenu;//���̲˵�
	QSystemTrayIcon *Tray;//����ͼ����ӳ�Ա
	QAction *ShowMainAction;//����ͼ���Ҽ����ʱ����ѡ��
	QAction *ExitAction;//����ͼ���Ҽ����ʱ����ѡ��
private:
	std::vector<QPushButton*> LinkeButtonList;
	std::vector<QUrl> LinkeButtonUrlList;

	std::vector<QPushButton*> LinkeButtonLabelList;
	std::vector<QUrl> LinkeButtonLabelUrlList;
private:
	void uiConnectButton();
	void uiConnectButtonLabel();
	void uiShowImage();
private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void NewWidgetsSetting();
	void CloseEvent();
	void StartGame();
	void OpenLinkeUrl();
	void OpenPageLinkeUrl();
	void OpenButtonLabelLinkeUrl();
	
	void TrayMenuClickEvent(QSystemTrayIcon::ActivationReason reason);
	// Receive Setting From WidgetsSetting
	void ReceiveSettingFromWidgetsSetting();
	void ReceiveCloseSelfSignalFromWidgetsSetting();

	void ShowTopMainWidget();
public slots:
	void ReceiveUniqueKeyMsg();
// signals:
};
