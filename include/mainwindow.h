#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void setUpUi();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget *centralWidget;
    QMenuBar *mainMenuBar;
private slots:
    void on_actionExit_triggered();
};
#endif // MAINWINDOW_H
