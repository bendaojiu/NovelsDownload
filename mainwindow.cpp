#include "mainwindow.h"
#include "urloperation.h"

extern QString mainUrl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget();
    leftWidget = new QTabWidget();
    allNovels = new QTreeWidget();
    bookShelf = new QListWidget();
    searchBtn = new QPushButton("搜索", this);
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("请输入书名或作者");

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
    this->setCentralWidget(widget);
    this->resize(600, 700);

    URLOperation url("http://www.shumilou.co/yichangshengwujianwenlu/6938210.html");
    int i = url.getChapterContent();
    qDebug()<<url.text;
    qDebug()<<i;
}

MainWindow::~MainWindow()
{

}
