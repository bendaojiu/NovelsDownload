#include "readxml.h"
#include <QDebug>

ReadXML::ReadXML()
{
    fileName = "./config.xml";
    file(fileName);
    if (!file.exists())//if config.xml isn't exist
    {
        //create config.xml
        file.open(QIODevice::WriteOnly);
        file.close();
        //write default configure
        int i = writeXML();
        qDebug()<<i;
    }

}

ReadXML::~ReadXML()
{

}

/********************************************
 * 写入xml文件，传入名称，网址
错误值：
        -1      代表以只读模式打开错误
        -2      代表文件读取错误
        -3      代表文件解析有错误，可能文件格式有问题
        -4      相关节点没有找到，要检查文件
        -5      代表以覆盖写入模式打开文件错误
********************************************/
int ReadXML::writeXML(QString name, QString url)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    QDomDocument doc;
    QDomAttr attr;
    QString error = "";
    int row = 0, column = 0;
    if (!doc.setContent(&file, false, &error, &row, &column))
    {
        qDebug() << "parse file failed:" << row << "---" <<column << ":" << error;
        file.close();
        return -2;
    }
    file.close();//readed
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    if (node.isNull())
    {
        qDebug() << "node is empty!!!";
        return -3;
    }
    QDomElement element = node.toElement(); //try to convert the node to an elemnet
    if (!element.isNull())
    {
        while ("COLLECTION" != element.text())//find the COLLECTION OBJECT
        {
            node = node.nextSibling();// goto next
            element = node.toElement();//reload new element
            if (element.isNull())
            {
                qDebug()<<"not found !!!";
                return -4;
            }
        }

        element = element.nextSiblingElement();


        //            QDomNode nodeson = element.firstChild();
        //            while (!nodeson.isNull())// find the end
        //            {
        //                nodeson = nodeson.nextSibling();
        //            }
        //            element = nodeson.toElement();
        QDomElement userElement = doc.createElement("USERINFO");;
        attr = doc.createAttribute("NAME");
        attr.setValue(name);
        userElement.setAttributeNode(attr);
        attr = doc.createAttribute("URL");
        attr.setValue(url);
        userElement.setAttributeNode(attr);
        element.appendChild(userElement);
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
            return -5;
        QTextStream out(&file);
        doc.save(out, 4);   //each line space of file is 4
        file.close();
        return 0;
    }

}

int ReadXML::writeXML()
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return -2;
    QTextStream out(&file);
    QDomDocument doc;
    QDomText text;
    QDomElement element;
    QDomAttr attr;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml", "version = \'1.0\' encoding = \'UTF-8\'");
    doc.appendChild( instruction );

    QDomElement root = doc.createElement("ALL");
    doc.appendChild(root);
    element = doc.createElement("OBJECT");
    text = doc.createTextNode("USER");
    element.appendChild(text);
    root.appendChild(element);

    element = doc.createElement("ACTION");
    text = doc.createTextNode("LOGIN");
    element.appendChild(text);
    root.appendChild(element);

    element = doc.createElement("DATA");
    root.appendChild(element);

    QDomElement userElement = doc.createElement("USERINFO");
    attr = doc.createAttribute("NAME");
    attr.setValue("root");
    userElement.setAttributeNode(attr);
    attr = doc.createAttribute("PASSWORD");
    attr.setValue("123456");
    userElement.setAttributeNode(attr);
    element.appendChild(userElement);

    doc.save(out, 4);   //each line space of file is 4
    file.close();
    return 0;
}

int ReadXML::readXML()
{
    QDomDocument doc;
    QFile file(fileName);
    QString error = "";
    int row = 0, column = 0;
    if (!file.open(QIODevice::ReadOnly))
        return -2;
    if (!doc.setContent(&file, false, &error, &row, &column))
    {
        qDebug() << "parse file failed:" << row << "---" <<column << ":" << error;
        file.close();
        return -1;
    }

    file.close();
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while(!node.isNull())
    {
        QDomElement element = node.toElement(); //try to convert the node to an elemnet
        if (!element.isNull())
        {
            //用于区分，是ALL的时候，表示小说的分类
            //是COLLECTION的时候，表示收藏的小说
            if ("ALL" == element.text())
                qDebug()<<"this is all";
            else if ("COLLECTION" == element.text())
                qDebug()<<"this is the collection books";
            //qDebug() << element.tagName() << ":" << element.text();
            QDomNode nodeson = element.firstChild();
            while (!nodeson.isNull())
            {
                QDomElement elementson = nodeson.toElement();
                if (!elementson.isNull())
                {
                    if (elementson.hasAttribute("NAME"))
                    {
                        qDebug() << "---" << elementson.attributeNode("NAME").value();
                    }
                    if (elementson.hasAttribute("URL"))
                    {
                        qDebug() << "---" << elementson.attributeNode("URL").value();
                    }
                }
                nodeson = nodeson.nextSibling();
            }
        }
        node = node.nextSibling();
    }
    return 0;
}
