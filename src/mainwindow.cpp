
#include <QTextEdit>
#include <QTreeView>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

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



    connect(pOpenAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
    // 连接槽函数
    connect(pExitAction, &QAction::triggered, this, &QMainWindow::close);

    // 连接信号槽
    QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow() {
    if (centralWidget)
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