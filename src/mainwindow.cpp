
#include "mainwindow.h"

QXLSX_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("XinYuConstructionTable.db");

    if (!db.open()) {
        qDebug() << "无法打开数据库";
        qDebug() << db.lastError().text();
        return;
    }
    qDebug() << "Database: connection ok";

    QSqlQuery query(db);

// 创建表
    if (query.exec(
            "CREATE TABLE IF NOT EXISTS ComplaintsSummary ("
            "Sequence INTEGER PRIMARY KEY AUTOINCREMENT,"
            "City VARCHAR(255),"
            "ComplaintLocation TEXT,"
            "Longitude DECIMAL(10, 6),"
            "Latitude DECIMAL(10, 6),"
            "ComplaintVolume INT,"
            "ComplaintSource VARCHAR(255),"
            "ComplaintUserNumber VARCHAR(255),"
            "SolutionMethod VARCHAR(255),"
            "Area VARCHAR(255),"
            "ResolvedStatus BOOLEAN,"
            "Remarks TEXT,"
            "ElevatorStop BOOLEAN)")) {

        qDebug() << "Table created successfully";

        // 准备插入数据的 SQL 语句
        query.prepare("INSERT INTO ComplaintsSummary"
                      " (Sequence, City, ComplaintLocation, Longitude, Latitude, ComplaintVolume, ComplaintSource, ComplaintUserNumber, SolutionMethod, Area, ResolvedStatus, Remarks, ElevatorStop) "
                      "VALUES(0, '', '', 0, 0, 0, '', '', '', '', 0, '', 0);");


        if (!query.exec()) {
            db.commit(); //提交事务
            qDebug() << "Insertion failed:" << query.lastError().text();
        } else {
            db.rollback(); //回滚事务
            qDebug() << "Insertion successful";
        }

    } else {
        qDebug() << "Table creation failed:" << query.lastError().text();
    }

    document = new Document(":file/XinYuConstructionTable.xlsx");
    if (document->load()) {
        qDebug() << "Excel file loaded successfully";

        if (document->selectSheet("汇总")) {
            auto cellReference = document->dimension();
            qDebug() << "Sheet dimension: " << cellReference.toString(); //打印表格大小

            auto* documentWrite = new Document("Test.xlsx");
            // 打印表格内容
            for (int i = 1; i <= cellReference.lastRow(); i++) {
                for (int j = 1; j <= cellReference.lastColumn(); j++) {
                    auto *cell = document->cellAt(i, j);
                    if (cell != nullptr) {
                        auto value = cell->value();
                        documentWrite->write(i, j, value);//写入单元格内容
                        qDebug() << "[debug] cell(" << i << "," << j << ") is " << value; //打印单元格内容
                    }
                }
            }
            if (documentWrite->saveAs("Test.xlsx")) // save the document as 'Test.xlsx'
            {
                qDebug() << "[debug] success to write xlsx file";
            } else {
                qDebug() << "[debug][error] failed to write xlsx file";
                exit(-1);
            }

            qDebug() << "[debug] current directory is " << QDir::currentPath();

        }
    }


    initialize();
}

MainWindow::~MainWindow() {
    delete centralWidget;
}


void MainWindow::on_actionOpen_triggered() {
    QString curPath = QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), curPath, tr("所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("文件操作"), tr("文件打开成功！"));
        }
    }

}

void MainWindow::on_listView_clicked(const QModelIndex &index) {
    QString text = index.data().toString();
    QMessageBox::information(this, tr("列表点击"), tr("你点击了：") + text);
}

void MainWindow::initialize() {
    resize(800, 600);
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));

    mainMenuBar = menuBar();
    // 创建菜单栏
    QMenu *pFileMenu = mainMenuBar->addMenu(tr("&File"));
    auto *pNewAction = new QAction("New", this);
    pFileMenu->addAction(pNewAction);
    auto *pOpenAction = new QAction("Open", this);
    pFileMenu->addAction(pOpenAction);
    auto *pSaveAction = new QAction("Save", this);
    pFileMenu->addAction(pSaveAction);
    auto *pSaveAsAction = new QAction("Save As", this);
    pFileMenu->addAction(pSaveAsAction);
    pFileMenu->addSeparator();
    auto *pExitAction = new QAction("Exit", this);
    pFileMenu->addAction(pExitAction);

    QMenu *pEditMenu = mainMenuBar->addMenu(tr("&Edit"));
    QMenu *pViewMenu = mainMenuBar->addMenu(tr("&View"));
    QMenu *pToolMenu = mainMenuBar->addMenu(tr("&Tool"));
    QMenu *pHelpMenu = mainMenuBar->addMenu(tr("&Help"));

    this->setMenuBar(mainMenuBar);

    mainVBoxLayout = new QVBoxLayout(centralWidget);

    mainSplitter = new QSplitter(this);
    mainVBoxLayout->addWidget(mainSplitter);

    auto *listview = new QListView();
    auto *treeview = new QTreeView();
    auto *textedit = new QTextEdit();
    mainSplitter->addWidget(listview);
    mainSplitter->addWidget(treeview);
    mainSplitter->addWidget(textedit);
    mainSplitter->show();

    centralWidget->setLayout(mainVBoxLayout);


    QStringList stringList;
    stringList << "Item1" << "Item2" << "Item3";

    auto *stringListModel = new QStringListModel();
    stringListModel->setStringList(stringList);
    listview->setModel(stringListModel);
    listview->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置列表不能编辑
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置列表不能被睡意拖动
    listview->setMovement(QListView::Static);
    //设置列表间隔
    listview->setSpacing(10);


    connect(listview, &QListView::clicked, this, &MainWindow::on_listView_clicked, Qt::DirectConnection);

    connect(pOpenAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
    // 连接槽函数
    connect(pExitAction, &QAction::triggered, this, &QMainWindow::close);
}
