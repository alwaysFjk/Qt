#ifndef SETTINGDIALOG_ADD_H
#define SETTINGDIALOG_ADD_H

#include <QDialog>

namespace Ui {
class SettingDialog_add;
}

class SettingDialog_add : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog_add(int type,QWidget *parent = 0);
    ~SettingDialog_add();

    void getInfo(QTime &beginTime, QTime &endTime, double &money);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingDialog_add *ui;

    int m_nType;
};

#endif // SETTINGDIALOG_ADD_H
