//
// Created by wuxianggujun on 2024/6/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Dialog.h" resolved

#include "dialog.hpp"
#include "./ui_Dialog.h"


Dialog::Dialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}
