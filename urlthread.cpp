#include "urlthread.h"
#include "urloperation.h"

extern QString mainUrl;

URLThread::URLThread(QObject *parent)
          : QThread(parent)
{

}

URLThread::~URLThread()
{

}

int URLThread::setMode(int mode, QString url)
{
    this->mode = mode;
    this->url = url;
}

int URLThread::setUrl(QString url)
{
    if (!this->url.isEmpty())
        this->url.clear();
    this->url = url;
}

void URLThread::run()
{
    if (url.isNull())
    {
        recv = -2;
        return;
    }
    URLOperation *urlOper = new URLOperation(url);
    if (!urlOper->isOnline())
    {
        recv = -1;
        return;
    }
    switch(mode)
    {
       case 1:
            if (0 != urlOper->getHomeContent(nameList, urlList))
                recv = -3;
            break;
       case 2:
            if (0 != urlOper->getClassifyNovels(nameList, urlList))
                recv = -3;
            break;
       case 3:
            if (0 != urlOper->getBookContent(nameList, urlList))
                recv = -3;
            break;
       case 4:
            if (0 != urlOper->getChapterContent(text, nexturl))
                recv = -3;
            break;
       default:
            recv = -4;
            break;
    }
    return;
}
