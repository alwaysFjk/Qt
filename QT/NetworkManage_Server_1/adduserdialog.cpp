#include "adduserdialog.h"
#include "ui_adduserdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::getInfo(QString &userID, QString &password, QString &userName, QString &phone, int &type)
{
    userID = ui->lineEdit->text();
    password = ui->lineEdit_2->text();
    userName = ui->lineEdit_3->text();
    phone = ui->lineEdit_4->text();
    type = ui->comboBox->currentIndex();
}

void AddUserDialog::on_pushButton_clicked()
{
    this->accept();
}
