#ifndef URLOPERATION_H
#define URLOPERATION_H

#include <QString>
#include <QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class URLOperation
{
public:
    URLOperation(QString url);
    ~URLOperation();

    QString getContent();
    int getBookContent();//get one book's chapter and each chapter's url

public:
    QUrl url;
    QStringList *chapterList;//store chapter list
    QStringList *urlList;//store url list

};

#endif // URLOPERATION_H
