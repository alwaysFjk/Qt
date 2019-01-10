#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = 0);
    ~AddUserDialog();

    void getInfo(QString &userID, QString &password, QString &userName, QString &phone, int &type);
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddUserDialog *ui;
};

#endif // ADDUSERDIALOG_H
