#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QVariant>
#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableView>
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
#include <QProgressdialog>

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

// TinyXML2
#include <tinyxml2.h>


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    void initialize();

    void setUpDatabase();

    void insertData(const QList<QXlsx::Cell *> &cells);

    void insertModelData();

    void loadExcelFile(const QString &filePath, const QStandardItemModel *model);

    bool convertLatitudeLongitudeColumns(QVariant& value,int column,int &latitudeColumn, int &longitudeColumn,double &doubleValue);
private:
    QWidget *centralWidget{};
    QMenuBar *mainMenuBar{};
    QSplitter *mainSplitter{};
    QVBoxLayout *mainVBoxLayout{};
    QProgressDialog *progressDialog{};

private:
    QXlsx::Document *document{};
    QSqlDatabase db{};
    QStandardItemModel *model{};

private slots:

    void handlerXlsxToKmlAction();

    void handleFileOpenAction();

    void handleListViewClick(const QModelIndex &index);
};

#endif // MAINWINDOW_H
