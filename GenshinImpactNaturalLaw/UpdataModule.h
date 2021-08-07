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


	// 设置要下载的url和文件名
	void setData(QUrl url);
	//开始下载
	void getFile();
	void startRequest(QUrl url);
	//发生的错误代码
	//int lastError();
	//返回是否有错误发生
	//bool errorValid();
	//返回是否下载中
	//bool isRunning();
	//返回是否下载完成
	//bool isFinished();
	//返回所下载文件的版本号
	QString getDownloadVersionCode();
	//返回所下载文件的名字（带扩展名）
	//QString getFileName();
	void cancel();
private:

	//=====状态变量=====
	bool bisFinished;   //下载是否完成
	bool bisRunning;    //下载是否进行中
	bool bisError;      //是否有错误发生
	int errorCode;      //错误代码
	int allBits = 0;    //文件大小
	bool httpRequestAborted;

	//=====对象声明=====
	VersionNumber version;

	QString FileBuff;
	QFile *downloadFile;                //保存目标文件指针
	QUrl downloadUrl;                   //下载地址Url
	QString savePath;                   //文件存放路径
	QString versionCode = "";           //所下载的文件版本号
	QString fileName = "";              //所下载文件名
	QNetworkReply *downloadReply;       //网络应答指针
	QNetworkAccessManager downloadmanager;     //网络连接主类指针
signals:

	//当错误发生时向外抛出错误信息
	void error(QNetworkReply::NetworkError);
	//抛出下载进度(更新进度条)
	void updateProgress(qint64 bytesSent, qint64 bytesTotal);
	//下载结果 0成功 其他失败
	void downloadResult(int retCode);

	void finish();

private slots:

	//准备下载，读取数据
	void downloadReadyRead();
	//下载完成
	void downloadFinished();
	//下载过程中发生错误
	void downloadError(QNetworkReply::NetworkError errorCode);
	//下载过程进度条
	void downloadProgress(qint64 bytesSent, qint64 bytesTotal);
};

