#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *leftWidget; //左边的窗口，包括全网，和书架两个窗口
    QWidget *allNovels;//全部小说的窗口，用于实现分类，进行查看
    QWidget *bookShelf;//暑假窗口，用于加载已有的收藏

};

#endif // MAINWINDOW_H
