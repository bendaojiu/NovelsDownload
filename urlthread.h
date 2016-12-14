#ifndef URLTHREAD_H
#define URLTHREAD_H

#include <QThread>


class URLThread : public QThread
{
    Q_OBJECT
public:
    explicit URLThread(QObject *parent = 0);
    ~URLThread();
    int setMode(int mode=0, QString url=NULL);//设置工作模式，1表示获取主页列表元素，
                                       //2表示获取分类列表元素,
                                       //3表示获取单个小说的章节列表元素,
                                       //4表示获取章节正文以及下一页网址
    int setUrl(QString url);
    virtual void run() Q_DECL_OVERRIDE;

public:
    QString url;
    QStringList nameList;
    QStringList urlList;
    QString text;
    QString nexturl;
    int recv = 0;//用于存储状态值，-1代表网络为链接
                 //-2代表url为空
                 //-3代表获取失败
                 //-4代表mode设置不对，没有找到

private:
    int mode;

signals:
    void resultReady();
    
};

#endif // URLTHREAD_H
