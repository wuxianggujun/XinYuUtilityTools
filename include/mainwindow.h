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

#include <QtSql>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

//xlsx
#include <xlsxdocument.h>
#include <xlsxcellrange.h>
#include <xlsxworkbook.h>
#include <xlsxformat.h>
#include <xlsxchart.h>
#include <xlsxrichstring.h>
#include <xlsxconditionalformatting.h>
#include <xlsxchartsheet.h>


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

private:
    QXlsx::Document *document;
private slots:

    void on_actionOpen_triggered();

    void on_listView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
