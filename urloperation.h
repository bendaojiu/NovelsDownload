#ifndef URLOPERATION_H
#define URLOPERATION_H

#include <QString>
#include <QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

// 用于存储小说的基本信息（名称，图标网址，作者，状态，类别, 简介）
struct NovelsInfo{
    QString name;
    QString url;
    QString author;
    QString state;
    QString classify;
    QString abstract;
};

class URLOperation
{
public:
    URLOperation(QString url);
    ~URLOperation();

    QString getContent();
    int getBookContent(QStringList &nameList, QStringList &urlList);//get one book's chapter and each chapter's url
    int getChapterContent(QString &text, QString &nextUrl);//get a chapter's content and next chapter'url
    int getClassifyNovels(QStringList &nameList, QStringList &urlList);
    int getHomeContent(QStringList &nameList, QStringList &urlList);
    int getAllNovelsFromString(QString str, QStringList &name, QStringList &url);
    bool isOnline();//is this online?


public:
    QUrl url;    
    NovelsInfo info;


private:
    int getNovelsAbstract(QString str);//用于获取一段字符串中关于作品简介的信息
    int getNovelsChapter(QString str, QStringList &nameList, QStringList &urlList);// 用于获取一段字符串中小说章节的信息
    int getNovelsHot(QString str);//用于获取一段字符串中热门小说的信息
};

#endif // URLOPERATION_H
