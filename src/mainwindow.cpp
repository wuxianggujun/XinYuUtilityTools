
#include "mainwindow.h"

QXLSX_USE_NAMESPACE

int MainWindow::longitudeColumn = 0;
int MainWindow::latitudeColumn = 0;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    initialize();
}

MainWindow::~MainWindow() {
    delete centralWidget;
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

    auto *pExportKmlAction = new QAction("Export KML", this);
    pFileMenu->addAction(pExportKmlAction);

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

    auto *listView = new QListView();
    auto *tableView = new QTableView();
    mainSplitter->addWidget(listView);
    mainSplitter->addWidget(tableView);
    mainSplitter->show();

    listView->hide();

    centralWidget->setLayout(mainVBoxLayout);


    model = new QStandardItemModel();

    progressDialog = new QProgressDialog(this);
    progressDialog->setWindowTitle(tr("Loading..."));
    progressDialog->setLabelText(tr("Loading data from Excel file..."));
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setMinimumDuration(0);

    document = new Document(":file/XinYuConstructionTable.xlsx");
    if (document->load()) {
        qDebug() << "Excel file loaded successfully";

        // 选择工作表
        if (document->selectSheet("汇总")) {
            // 获取表格的行列数
            auto cellReference = document->dimension();
            model->setRowCount(cellReference.lastRow());
            model->setColumnCount(cellReference.lastColumn());

            progressDialog->setRange(0, cellReference.lastRow());

            // 打印表格内容
            for (int i = 1; i <= cellReference.lastRow(); i++) {
                for (int j = 1; j <= cellReference.lastColumn(); j++) {
                    auto *cell = document->cellAt(i, j);
                    if (cell != nullptr) {
                        if (cell->value().toString().contains("经度")) {
                            MainWindow::longitudeColumn = j;
                        } else if (cell->value().toString().contains("纬度")) {
                            MainWindow::latitudeColumn = j;
                        }

                        auto value = cell->value();
                        QStandardItem *item = nullptr;
                        double doubleValue{};
                        if (convertLatitudeLongitudeColumns(value, j, doubleValue)) {
                            item = new QStandardItem(QString::number(doubleValue, 'f', 6));
                        } else {
                            item = new QStandardItem(value.toString());
                        }
                        auto format = cell->format();
                        auto bgColor = cell->format().patternBackgroundColor();
                        if (bgColor.isValid()) {
                            item->setBackground(bgColor); // 设置单元格背景色
                        }
                        auto textColor = cell->format().patternForegroundColor();
                        if (textColor.isValid()) {
                            item->setForeground(textColor); // 设置单元格字体颜色
                        }

                        if (format.hasFontData()) {
                            item->setFont(format.font()); // 设置单元格字体
                        }

                        model->setItem(i - 1, j - 1, item);
                    }
                }
                progressDialog->setValue(i);
                QCoreApplication::processEvents();
                if (progressDialog->wasCanceled()) {
                    break;
                }
            }
        }
    }

    tableView->setModel(model);

    QStringList stringList;
    stringList << "Item1" << "Item2" << "Item3";

    auto *stringListModel = new QStringListModel();
    stringListModel->setStringList(stringList);
    listView->setModel(stringListModel);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置列表不能编辑
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置列表不能被睡意拖动
    listView->setMovement(QListView::Static);
    //设置列表间隔
    listView->setSpacing(10);


    connect(listView, &QListView::clicked, this, &MainWindow::handleListViewClick, Qt::DirectConnection);

    connect(pOpenAction, &QAction::triggered, this, &MainWindow::handleFileOpenAction);

    connect(pSaveAsAction, &QAction::triggered, this, &MainWindow::handleFileSaveAsAction);

    connect(pExportKmlAction, &QAction::triggered, this, &MainWindow::handlerXlsxToKmlAction);
    // 连接槽函数
    connect(pExitAction, &QAction::triggered, this, &QMainWindow::close);

}

void MainWindow::handleFileOpenAction() {
    QString curPath = QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), curPath, tr("所有文件 (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("文件操作"), tr("文件打开成功！"));
        }
    }
}

void MainWindow::handleListViewClick(const QModelIndex &index) {
    QString text = index.data().toString();
    QMessageBox::information(this, tr("列表点击"), tr("你点击了：") + text);
}

void MainWindow::setUpDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
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
}

void MainWindow::insertData(const QList<QXlsx::Cell *> &cells) {
    QSqlQuery query(db);
    // 准备插入数据的 SQL 语句
    query.prepare("INSERT INTO ComplaintsSummary"
                  " (City, ComplaintLocation, Longitude, Latitude, ComplaintVolume, ComplaintSource, ComplaintUserNumber, SolutionMethod, Area, ResolvedStatus, Remarks, ElevatorStop) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
    for (auto cell: cells) {
        query.addBindValue(cell ? cell->value().toString() : QVariant());
    }
    if (!query.exec()) {
        qDebug() << "Insertion failed:" << query.lastError().text();
    } else {
        qDebug() << "Insertion successful";
    }
}

void MainWindow::insertModelData() {


}

void MainWindow::handlerXlsxToKmlAction() {
    const char *kmlPath = "./XinYuConstructionTable.kml";

    tinyxml2::XMLDocument doc;

    // 添加XML声明
    auto *decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(decl);

    auto *kml = doc.NewElement("kml");
    kml->SetAttribute("xmlns", "http://www.opengis.net/kml/2.2");
    doc.InsertEndChild(kml);

    // 创建Document元素
    auto *documentElement = doc.NewElement("Document");
    kml->InsertEndChild(documentElement);

    for (int i = 0; i < model->rowCount(); i++) {
        auto nameItem = model->item(i, 2);

        auto longitudeItem = model->item(i, MainWindow::longitudeColumn - 1);
        auto latitudeItem = model->item(i, MainWindow::latitudeColumn - 1);

        // 检查是否有无效的项
        if (!nameItem || !longitudeItem || !latitudeItem) {
            qDebug() << "第" << i << "行有无效项";
            continue; // 跳过无效行
        }

        auto *placemark = doc.NewElement("Placemark");
        documentElement->InsertEndChild(placemark);

        auto *nameElement = doc.NewElement("name");
        nameElement->SetText(nameItem->text().toStdString().c_str());
        placemark->InsertEndChild(nameElement);

        /*     auto* descriptionElement = doc.NewElement("description");
             descriptionElement->SetText(description.toStdString().c_str());
             placemark->InsertEndChild(descriptionElement);*/

        auto *point = doc.NewElement("Point");
        placemark->InsertEndChild(point);

        auto *coordinates = doc.NewElement("coordinates");
        QString coordString = QString("%1,%2,0").arg(longitudeItem->text()).arg(latitudeItem->text());
        coordinates->SetText(coordString.toStdString().c_str());
        point->InsertEndChild(coordinates);
    }
    tinyxml2::XMLError result = doc.SaveFile(kmlPath);
    if (result != tinyxml2::XML_SUCCESS) {
        qDebug() << "Failed to save KML file: " << result;
        return;
    }
    qDebug() << "KML file saved successfully";
}


bool MainWindow::convertLatitudeLongitudeColumns(QVariant &value, int column, double &doubleValue) {
    bool isDoubleValue = false;
    if (column == MainWindow::longitudeColumn || column == MainWindow::latitudeColumn) {
        // 移除经纬度中的空格和度数符号
        QString strValue = value.toString().trimmed().remove(QChar(0x00B0));
        if (strValue.contains('.')) {
            doubleValue = strValue.toDouble(&isDoubleValue);
        }
        return isDoubleValue;
    }
    return isDoubleValue;
}

void MainWindow::handleFileSaveAsAction() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存文件"), QDir::currentPath(),
                                                    tr("XLSX Files (*.xlsx);;All Files (*)"));
    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".xlsx", Qt::CaseInsensitive)) {
            fileName += ".xlsx";
        }
        saveXlsx(fileName);
    }
}

void MainWindow::saveXlsx(const QString &fileName) {
    qDebug() << "Saving to file: " << fileName;
    auto documentWrite = new Document(fileName);
    for (int i = 0; i < model->rowCount(); i++) {
        for (int j = 0; j < model->columnCount(); j++) {
            auto item = model->item(i, j);
            if (item) {
                documentWrite->write(i+1, j+1, item->text());
                qDebug() << "Saving item: " << item->text();
            }
        }
    }
    if (documentWrite->save()) {
        qDebug() << "File saved successfully";
    } else {
        qDebug() << "Failed to save file: " << documentWrite;
    }

}
