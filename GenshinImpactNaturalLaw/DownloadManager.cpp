#include "DownloadManager.h"

bool DownloadManager::download()
{
	//QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
	//accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
	//QUrl url("http://192.168.1.166:80/test.jpg");

	//QNetworkRequest request(url);
	//request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
	//reply = accessManager->get(request);

	//progressBar = new QProgressBar();
	//progressBar->setValue(0);
	//progressBar->show();

	//connect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
	//connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	//connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(loadError(QNetworkReply::NetworkError)));
	//connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(loadProgress(qint64, qint64)));

	return false;
}
