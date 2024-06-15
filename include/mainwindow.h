#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QStandardItemModel>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QDebug>
#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QSplitter>
#include <QListView>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget *centralWidget;
    QMenuBar *mainMenuBar;
    QSplitter *mainSplitter;
    QVBoxLayout *mainVBoxLayout;
private slots:
    void on_actionOpen_triggered();
};
#endif // MAINWINDOW_H
