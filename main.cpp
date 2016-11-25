#include "urloperation.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QCoreApplication a(argc, argv);
    URLOperation tmpUrl("http://www.shumilou.co/");
    qDebug()<<tmpUrl.getContent();
//    dom.writeXML();
//    dom.readXML();
//    qDebug() << "**************";
//    qDebug() << "AFTER WRITE";
//    int i = dom.writeXML("heh", "http://163.com");
//    qDebug()<<i;
//    dom.readXML();



    return a.exec();
}
