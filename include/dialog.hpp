//
// Created by wuxianggujun on 2024/6/9.
//

#ifndef XINYUUTILITYTOOLS_DIALOG_HPP
#define XINYUUTILITYTOOLS_DIALOG_HPP

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog {
Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog() override;

private:
    Ui::Dialog *ui;
};


#endif //XINYUUTILITYTOOLS_DIALOG_HPP
