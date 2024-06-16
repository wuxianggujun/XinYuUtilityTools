#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QVariant>
#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QDebug>
#include <QtCore>
#include <QtNetwork>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QSplitter>
#include <QListView>
#include <QTextEdit>
#include <QTreeView>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
private:
     void initialize();
private:
    QWidget *centralWidget;
    QMenuBar *mainMenuBar;
    QSplitter *mainSplitter;
    QVBoxLayout *mainVBoxLayout;
private slots:

    void on_actionOpen_triggered();

    void on_listView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
