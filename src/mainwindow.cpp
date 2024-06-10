#include "mainwindow.h"
#include "./ui_mainwindow.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setUpUi();
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

    // 连接槽函数
    QObject::connect(pExitAction, &QAction::triggered, this, &QMainWindow::close);

    // 连接信号槽
    QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow() {
    delete centralWidget;
}

void MainWindow::setUpUi() {
    if (objectName().isEmpty()) {
        setObjectName("MainWindow");
    }
    resize(800, 600);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    setCentralWidget(centralWidget);

    setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
}

void MainWindow::on_actionExit_triggered() {

}
