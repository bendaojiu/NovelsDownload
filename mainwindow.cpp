#include "mainwindow.h"
#include "urloperation.h"
#include "readxml.h"

extern QString mainUrl;


QString xmlCategory[2] = {"ALL", "COLLECTION"};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget();
    leftWidget = new QTabWidget();
    allNovels = new QTreeWidget();
    bookShelf = new QTreeWidget();
    searchBtn = new QPushButton("搜索", this);
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("请输入书名或作者");

    getAllNovels();
    getBookShelf();
    QTreeWidgetItem *root = new QTreeWidgetItem(allNovels, QStringList(QString("书迷网")));
    QTreeWidgetItem *categoryTree;
    for (int i=0; i<categoryName.length(); ++i)
    {
        categoryTree = new QTreeWidgetItem(root, QStringList()<<categoryName.at(i));
        allNovels->insertTopLevelItem(i, categoryTree);
    }
    QTreeWidgetItem *shelfItem;
    for (int i=0; i<shelfName.length(); ++i)
    {
        shelfItem = new QTreeWidgetItem(QStringList()<<shelfName.at(i));
        bookShelf->addTopLevelItem(shelfItem);
    }

    rightTopLayout = new QHBoxLayout();
//    rightLayout = new QVBoxLayout();
    allLayout = new QHBoxLayout();
    rightTopLayout->addWidget(searchEdit);
    rightTopLayout->setStretch(0, 4);
    rightTopLayout->addWidget(searchBtn);
    rightTopLayout->setStretch(1, 1);


    leftWidget->addTab(allNovels, "全网小说");
    leftWidget->addTab(bookShelf, "收藏");
    allLayout->addWidget(leftWidget);
    allLayout->addLayout(rightTopLayout);
    widget->setLayout(allLayout);

    this->resize(600, 700);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

int MainWindow::getAllNovels()
{
    ReadXML *xml = new ReadXML();
    int i = xml->readXML(xmlCategory[0], categoryName, categoryUrl);
    if (i != 0)
        return i;
    delete xml;
    return 0;
}

int MainWindow::getBookShelf()
{
    ReadXML *xml = new ReadXML();
    int i = xml->readXML(xmlCategory[1], shelfName, shelfUrl);
    if (i != 0)
        return i;
    delete xml;
    return 0;
}

int MainWindow::writeShelf(QString name, QString url)
{
    ReadXML *xml = new ReadXML();
    int i = xml->writeXML(name, url);
    if (i != 0)
        return i;
    delete xml;
    return 0;
}
