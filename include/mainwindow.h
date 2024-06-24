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

    bool convertLatitudeLongitudeColumns(QVariant& value,int column,double &doubleValue);

    void saveXlsx(const QString &fileName);
private slots:

    void handleFileSaveAsAction();
    // 导出文件为KML
    void handlerXlsxToKmlAction();

    // 打开文件
    void handleFileOpenAction();

    void handleListViewClick(const QModelIndex &index);

private:
    QWidget *centralWidget{};
    QMenuBar *mainMenuBar{};
    QSplitter *mainSplitter{};
    QVBoxLayout *mainVBoxLayout{};
    QProgressDialog *progressDialog{};
    QXlsx::Document *document{};
    QSqlDatabase db{};
    QStandardItemModel *model{};

    // 找到经纬度所在的列
    static int longitudeColumn;
    static int latitudeColumn;

};

#endif // MAINWINDOW_H
