#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_dialButton_clicked();

    void on_dialDelButton_clicked();


    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_specialDelButton_clicked();

    void on_specialButton_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
