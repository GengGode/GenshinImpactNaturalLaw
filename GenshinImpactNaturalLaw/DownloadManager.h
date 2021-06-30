#pragma once
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QObject>

class DownloadManager:QObject
{
public:
	//DownloadManager();


	bool download();
};

