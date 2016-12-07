#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QListWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int getAllNovels();
    int getBookShelf();
    int writeShelf(QString name, QString url);

public:
    QWidget *widget;//main widget
    QTabWidget *leftWidget; //左边的窗口，包括全网，和书架两个窗口
    QTreeWidget *allNovels;//全部小说的窗口，用于实现分类，进行查看
    QTreeWidget *bookShelf;//暑假窗口，用于加载已有的收藏
    QPushButton *searchBtn;//search button
    QLineEdit *searchEdit;//edit what to search
    QHBoxLayout *rightTopLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *allLayout;


public:
    QStringList categoryName;
    QStringList categoryUrl;
    QStringList shelfName;
    QStringList shelfUrl;


};

#endif // MAINWINDOW_H
