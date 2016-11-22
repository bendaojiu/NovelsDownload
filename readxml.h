#ifndef READXML_H
#define READXML_H
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

class ReadXML
{
public:
    ReadXML();
    ~ReadXML();

    int writeXML(QString name, QString url);//add COLLECTION item
    int writeXML();//default write config.xml, when this document isn't exist,write it!
    int readXML();

private:
    QString fileName;
    QFile file;
};

#endif // READXML_H
