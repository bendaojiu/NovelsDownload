#include "urloperation.h"

#include <QEventLoop>
#include <QtCore>
#include <QTextCodec>


URLOperation::URLOperation(QString url)
{
    chapterList = new QStringList;
    urlList = new QStringList;
    this->url.setUrl(url);
}

URLOperation::~URLOperation()
{

}

QString URLOperation::getContent()
{
    QNetworkAccessManager manager;
    QEventLoop loop;
//    QTextCodec *codec;
    QNetworkReply *reply;

    reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    return reply->readAll();

}

int URLOperation::getBook()
{

}


