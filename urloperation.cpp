#include "urloperation.h"

#include <QEventLoop>
#include <QtCore>
#include <QTextCodec>
#include <strings.h>

#include <iostream>
#include "ParserDom.h"

using namespace std;
using namespace htmlcxx;

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
    //解析一段Html代码
    string content = this->getContent().toStdString();


    HTML::ParserDom parser;

    tree<HTML::Node> dom = parser.parseTree(content);

    cout<<dom<<endl;
    tree<HTML::Node>::iterator it = dom.begin();

//    for (; it != dom.end(); ++it)
//    {
//        //某个节点解析前都要执行parseAttributes函数
//        it->parseAttributes();
//        if (it->tagName() == "a")
//        {
//            //解析出网址
//            cout<<it->attribute("href").second;

//            //下面解析出tag的内容,
//            tree<HTML::Node>::iterator sib3 = dom.begin(it);
//            tree<HTML::Node>::iterator end3 = dom.end(it);
//            for (; sib3!=end3; ++sib3)
//            {
//                if (!sib3->isComment())
//                    break;//已经找到即章节名称
//                    //cout<<sib3->text()<<endl;
//            }
////            it->parseAttributes();
//            cout<<endl;
////            qDebug()<<QString::fromStdString(it->Attribute("href").second);
//        }
    for (; it != dom.end(); ++it)
    {
        it->parseAttributes();
        if (it->tagName() == "div")
        {
//            it->parseAttributes();
            cout<<it->text();
        }
    }
}


