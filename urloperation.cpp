#include "urloperation.h"

#include <QEventLoop>
#include <QtCore>
#include <QTextCodec>
#include <strings.h>
#include <QNetworkConfigurationManager>



QString mainUrl = "http://www.shumilou.co/";

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

int URLOperation::getBookContent()
{
    QString htmlContent = this->getContent();
    if (htmlContent.isEmpty())
    {
        //error
        return -1;
    }
    QString tag = "<div class=\"tit\">";
    int index1 = htmlContent.indexOf(tag);
    int index2 = htmlContent.indexOf(tag, index1+10);
    int index3 = htmlContent.indexOf(tag, index2+10);
    QString str1 = htmlContent.mid(index1, (index2-index1));
    int recv = this->getNovelsAbstract(str1);
    if (recv != 0)
    {
        //error
    }
    QString str2 = htmlContent.mid(index2, (index3-index2));
    recv = this->getNovelsChapter(str2);
    if (recv != 0)
    {
        //error
    }
    QString str3 = htmlContent.mid(index3);
    recv = this->getNovelsHot(str3);
    if (recv != 0)
    {
        //error
    }

    return 0;
}

int URLOperation::getChapterContent()
{
    QString temStr1 = this->getContent();
    if (temStr1.isEmpty())
    {
        //error
        return -1;
    }
    int index1 = temStr1.indexOf("font color");
    if (index1 == -1)
    {
        return -2;
    }
    QString temStr2 = temStr1.mid(index1+10, temStr1.length()-index1-10);
    temStr1.clear();
    index1 = temStr2.indexOf("/div>");
    if (index1 == -1)
    {
        return -3;
    }
    temStr1 = temStr2.mid(index1+5, temStr2.length()-index1-5);
    temStr2.clear();
    int index2 = temStr1.indexOf("<b>");
    if (index2 == -1)
    {
        return -4;
    }
    text = temStr1.mid(0, index2-3);
    temStr1.clear();
    temStr2.clear();

    return 0;
}

int URLOperation::getClassifyNovels()
{
    QString htmlContent = this->getContent();
    if (htmlContent.isEmpty())
    {
        //error
        return -1;
    }
    int index1 = htmlContent.indexOf("class=\"tit\">");
    int recv = this->getNovelsHot(htmlContent.mid(index1+12, htmlContent.length()-index1-12));
    if (recv != 0)
    {
        //error
    }
}

int URLOperation::getHomeContent()
{
    QString temStr1 = this->getContent();
    if (temStr1.isEmpty())
    {
        //error
        return -1;
    }
    int index1 = temStr1.indexOf("class=\"tit\">");
    QString temStr2 = temStr1.mid(index1+12, temStr1.length()-index1-12);
    temStr1.clear();
    index1 = temStr2.indexOf("class=\"tit\">");
    temStr1 = temStr2.mid(0, index1);
    int recv = this->getNovelsHot(temStr1);
    if (recv != 0)
    {
        //error
        return -2;
    }
    hotNameList->append("none");
    hotUrlList->append("none");//set as division
    temStr1.clear();
    index1 = temStr2.indexOf("class=\"tit\">");
    temStr1 = temStr2.mid(index1+12, temStr2.length()-index1-12);
    temStr2.clear();
    index1 = temStr1.indexOf("class=\"tit\">");
    temStr2 = temStr1.mid(0, index1);
    recv = this->getNovelsHot(temStr2);
    if (recv != 0)
    {
        //error
        return -2;
    }
}

bool URLOperation::isOnline()
{
    QNetworkConfigurationManager mgr;
    return mgr.isOnline();
}

/********************************************
 * 根据传入的字符串，从中解析出小说简介来
 * 错误值：
        -1      代表没有找到小说名字的头位置
        -2      代表没有找到小说名字的尾位置
        -3      代表没有找到小说图标网址的头位置
        -4      代表没有找到小说图标网址的尾位置
********************************************/
int URLOperation::getNovelsAbstract(QString str)
{
    int index1 = str.indexOf("<b>");
    if (index1 == -1)
    {
        return -1;
    }
    int index2 = str.indexOf("</b>");
    if (index2 == -1)
    {
        return -2;
    }
    QString temStr = str.mid(index1, (index2-index1));
    info.name = temStr.mid(3, temStr.length()-3);
    index1 = str.indexOf("img src");
    if (index1 == -1)
    {
        return -3;
    }
    index2 = str.indexOf("jpg");
    if (index2 == -1)
    {
        return -4;
    }
    info.url = str.mid(index1+9, index2-6-index1);
    index1 = str.indexOf("<br");
    temStr = str.mid(index1+12, str.length()-index1-12);
    //index2 = temStr.indexOf("<br");
    //info.author = str.mid(index1+12, index2);
    index2 = temStr.indexOf("<br");
    info.author = temStr.mid(0, index2);
    temStr = temStr.mid(index2+12, temStr.length()-index2-12);
    index2 = temStr.indexOf("<br");
    info.state = temStr.mid(0, index2);
    temStr = temStr.mid(index2+12, temStr.length()-index2-12);
    index2 = temStr.indexOf("<br");
    info.classify = temStr.mid(14, index2-14);
    temStr = temStr.mid(index2+12, temStr.length()-index2-12);
    index2 = temStr.indexOf("<br");
    info.abstract = temStr.mid(0, index2);

    return 0;
}

int URLOperation::getNovelsChapter(QString str)
{
    int index1 = str.indexOf("a href=");
    if (index1 == 0)
        return -1;
    QString temStr = str.mid(index1, str.length()-index1);
    QString temStr2;
    int index2 = 0;
    while(1)
    {
        index2  = temStr.indexOf(">");
        urlList->append(temStr.mid(8, index2-9));
        temStr2 = temStr.mid(index2, temStr.length()-index2);
        temStr.clear();
        index2 = temStr2.indexOf("<");
        chapterList->append(temStr2.mid(1, index2-1));
        temStr = temStr2.mid(index2, temStr2.length()-index2);
        temStr2.clear();
        index1 = temStr.indexOf("a href=");
        if (index1 == -1)
            break;
        temStr = temStr.mid(index1, temStr.length()-index1);
    }

    return 0;
}

int URLOperation::getNovelsHot(QString str)
{
    int index1 = str.indexOf("a href=");
    if (index1 == 0)
        return -1;
    QString temStr1 = str.mid(index1, str.length()-index1);
    QString temStr2;
    int index2;
    while(1)
    {
        index2  = temStr1.indexOf(">");
        hotUrlList->append(temStr1.mid(8, index2-9));
        temStr2 = temStr1.mid(index2, temStr1.length()-index2);
        temStr1.clear();
        index2 = temStr2.indexOf("<");
        hotNameList->append(temStr2.mid(1, index2-1));
        temStr1 = temStr2.mid(index2, temStr2.length()-index2);
        temStr2.clear();
        index1 = temStr1.indexOf("a href=");
        if (index1 == -1)
            break;
        temStr1 = temStr1.mid(index1, temStr1.length()-index1);
    }

    return 0;
}


