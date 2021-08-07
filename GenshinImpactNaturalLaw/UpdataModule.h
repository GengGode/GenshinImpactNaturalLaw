#pragma once
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QObject>

#include "VersionNumber.h"

class UpdataModule :public QObject
{
	Q_OBJECT

public:
	UpdataModule();
	~UpdataModule();


	// ����Ҫ���ص�url���ļ���
	void setData(QUrl url);
	//��ʼ����
	void getFile();
	void startRequest(QUrl url);
	//�����Ĵ������
	//int lastError();
	//�����Ƿ��д�����
	//bool errorValid();
	//�����Ƿ�������
	//bool isRunning();
	//�����Ƿ��������
	//bool isFinished();
	//�����������ļ��İ汾��
	QString getDownloadVersionCode();
	//�����������ļ������֣�����չ����
	//QString getFileName();
	void cancel();
private:

	//=====״̬����=====
	bool bisFinished;   //�����Ƿ����
	bool bisRunning;    //�����Ƿ������
	bool bisError;      //�Ƿ��д�����
	int errorCode;      //�������
	int allBits = 0;    //�ļ���С
	bool httpRequestAborted;

	//=====��������=====
	VersionNumber version;

	QString FileBuff;
	QFile *downloadFile;                //����Ŀ���ļ�ָ��
	QUrl downloadUrl;                   //���ص�ַUrl
	QString savePath;                   //�ļ����·��
	QString versionCode = "";           //�����ص��ļ��汾��
	QString fileName = "";              //�������ļ���
	QNetworkReply *downloadReply;       //����Ӧ��ָ��
	QNetworkAccessManager downloadmanager;     //������������ָ��
signals:

	//��������ʱ�����׳�������Ϣ
	void error(QNetworkReply::NetworkError);
	//�׳����ؽ���(���½�����)
	void updateProgress(qint64 bytesSent, qint64 bytesTotal);
	//���ؽ�� 0�ɹ� ����ʧ��
	void downloadResult(int retCode);

	void finish();

private slots:

	//׼�����أ���ȡ����
	void downloadReadyRead();
	//�������
	void downloadFinished();
	//���ع����з�������
	void downloadError(QNetworkReply::NetworkError errorCode);
	//���ع��̽�����
	void downloadProgress(qint64 bytesSent, qint64 bytesTotal);
};

