#ifndef URLOPERATION_H
#define URLOPERATION_H

#include <QString>
#include <QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

// 用于存储小说的基本信息（处理状态，名称，图标网址，作者，状态，简介）
struct NovelsInfo{
    bool isDo = false;
    QString name;
    QString url;
    QString author;
    QString state;
    QString  abstract;
};

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

    //本分类热门小说信息（名词，网址）
    QStringList *hotNameList;
    QStringList *hotUrlList;
};

#endif // URLOPERATION_H
