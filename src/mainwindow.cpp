
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

    initialize();

    // 连接信号槽
    QMetaObject::connectSlotsByName(this);
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
    if (objectName().isEmpty()) {
        setObjectName("MainWindow");
    }
    resize(800, 600);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
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
    mainVBoxLayout->setObjectName("mainVBoxLayout");

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


    connect(listview,&QListView::clicked,this,&MainWindow::on_listView_clicked,Qt::DirectConnection);

    connect(pOpenAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
    // 连接槽函数
    connect(pExitAction, &QAction::triggered, this, &QMainWindow::close);
}
