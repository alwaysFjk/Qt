#include "settingdialog_add.h"
#include "ui_settingdialog_add.h"
#include <QTime>

SettingDialog_add::SettingDialog_add(int type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog_add)
    ,m_nType(type)
{
    ui->setupUi(this);
    if (type == 0)
    {
        this->setWindowTitle(QString::fromLocal8Bit("��Ӳ��������Ż�ʱ��"));
    }
    else if (type == 1)
    {
        this->setWindowTitle(QString::fromLocal8Bit("���ר�������Ż�ʱ��"));
    }

}

SettingDialog_add::~SettingDialog_add()
{
    delete ui;
}

void SettingDialog_add::getInfo(QTime &beginTime, QTime &endTime, double &money)
{
    beginTime = ui->beginTimeEdit->time();
    endTime = ui->endTimeEdit->time();
    money = ui->dialSpinBox->value();
}

void SettingDialog_add::on_pushButton_clicked()
{
    this->accept();
}
