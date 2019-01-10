#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "settingdialog_add.h"
#include <QTime>
#include "xmlhelp.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    // init tabwidget
    ui->tabWidget->setTabText( 0, QString::fromLocal8Bit("��������") );
    ui->tabWidget->setTabText( 1, QString::fromLocal8Bit("ר������") );

    // init tableWidget1
    ui->dialTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->dialTableWidget->setRowCount(0);
    ui->dialTableWidget->setColumnCount(3);
    ui->dialTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("����ʱ��")));
    ui->dialTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("����ʱ��")));
    ui->dialTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("�շѣ�ÿСʱ/Ԫ��")));
    ui->dialTableWidget->setColumnWidth(0, 150);
    ui->dialTableWidget->setColumnWidth(1, 150);
    ui->dialTableWidget->setColumnWidth(2, 100);

    ui->dialTableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //����ѡ��ģʽ��ѡ����
    ui->dialTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ�еķ�ʽ
    ui->dialTableWidget->verticalHeader()->setVisible(false);                   //�����б�ͷ
    ui->dialTableWidget->horizontalHeader()->setStretchLastSection(true);       //�ؼ�
    ui->dialTableWidget->horizontalHeader()->setHighlightSections(false);

    // init tableWidget1
    ui->specialTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->specialTableWidget->setRowCount(0);
    ui->specialTableWidget->setColumnCount(3);
    ui->specialTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("����ʱ��")));
    ui->specialTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("����ʱ��")));
    ui->specialTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("�շѣ�ÿСʱ/Ԫ��")));
    ui->specialTableWidget->setColumnWidth(0, 150);
    ui->specialTableWidget->setColumnWidth(1, 150);
    ui->specialTableWidget->setColumnWidth(2, 100);

    ui->specialTableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //����ѡ��ģʽ��ѡ����
    ui->specialTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ�еķ�ʽ
    ui->specialTableWidget->verticalHeader()->setVisible(false);                   //�����б�ͷ
    ui->specialTableWidget->horizontalHeader()->setStretchLastSection(true);       //�ؼ�
    ui->specialTableWidget->horizontalHeader()->setHighlightSections(false);
    // ��ȡ�ļ�����
    XMLHelp config;
    QList<MoneyInfo> moneyInfoList;
    config.read(moneyInfoList);
    if ( moneyInfoList.count() == 2)
    {
        foreach (MoneyInfo moneyInfo, moneyInfoList)
        {
            if (moneyInfo.type == 0)
            {
                ui->dialSpinBox->setValue(moneyInfo.money);
                foreach (TimeInfo timeInfo, moneyInfo.timeInfos)
                {
                    ui->dialTableWidget->insertRow(0);
                    QString beginTime = timeInfo.beginTime.toString("hh:mm");
                    QString endTime = timeInfo.endTime.toString("hh:mm");
                    ui->dialTableWidget->setItem(0, 0, new QTableWidgetItem(beginTime));
                    ui->dialTableWidget->setItem(0, 1, new QTableWidgetItem(endTime));
                    ui->dialTableWidget->setItem(0, 2, new QTableWidgetItem( QString("%1").arg(timeInfo.money)));
                }
            }
            if (moneyInfo.type == 1)
            {
                ui->specialSpinBox->setValue(moneyInfo.money);
                foreach (TimeInfo timeInfo, moneyInfo.timeInfos)
                {
                    ui->specialTableWidget->insertRow(0);
                    QString beginTime = timeInfo.beginTime.toString("hh:mm");
                    QString endTime = timeInfo.endTime.toString("hh:mm");
                    ui->specialTableWidget->setItem(0, 0, new QTableWidgetItem(beginTime));
                    ui->specialTableWidget->setItem(0, 1, new QTableWidgetItem(endTime));
                    ui->specialTableWidget->setItem(0, 2, new QTableWidgetItem( QString("%1").arg(timeInfo.money)));
                }
            }
        }
    }
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_dialButton_clicked()
{
    SettingDialog_add dialog(0,this);
    if ( dialog.exec() == QDialog::Accepted)
    {
        QTime beignTime,endTime;
        double money;
        dialog.getInfo(beignTime,endTime,money);
        ui->dialTableWidget->insertRow(0);
        ui->dialTableWidget->setItem(0, 0, new QTableWidgetItem(beignTime.toString("hh:mm")));
        ui->dialTableWidget->setItem(0, 1, new QTableWidgetItem(endTime.toString("hh:mm")));
        ui->dialTableWidget->setItem(0, 2, new QTableWidgetItem(QString("%1").arg(money)));
    }
}

void SettingDialog::on_dialDelButton_clicked()
{
    int row = ui->dialTableWidget->currentRow();
    ui->dialTableWidget->removeRow(row);
}

void SettingDialog::on_specialDelButton_clicked()
{
    int row = ui->specialTableWidget->currentRow();
    ui->specialTableWidget->removeRow(row);
}

void SettingDialog::on_specialButton_clicked()
{
    SettingDialog_add dialog(0,this);
    if ( dialog.exec() == QDialog::Accepted)
    {
        QTime beignTime,endTime;
        double money;
        dialog.getInfo(beignTime,endTime,money);
        ui->specialTableWidget->insertRow(0);
        ui->specialTableWidget->setItem(0, 0, new QTableWidgetItem(beignTime.toString("hh:mm")));
        ui->specialTableWidget->setItem(0, 1, new QTableWidgetItem(endTime.toString("hh:mm")));
        ui->specialTableWidget->setItem(0, 2, new QTableWidgetItem(QString("%1").arg(money)));
    }
}

void SettingDialog::on_cancelButton_clicked()
{
    this->reject();
}

void SettingDialog::on_okButton_clicked()
{
    // д�ļ�
    QList<MoneyInfo> moneyInfoList;
    {
        MoneyInfo moneyInfo(0,ui->dialSpinBox->value());
        for ( int i=0; i<ui->dialTableWidget->rowCount(); i++)
        {
            TimeInfo timeInfo( QTime::fromString( ui->dialTableWidget->item(i,0)->text(), "hh:mm"),
                               QTime::fromString( ui->dialTableWidget->item(i,1)->text(), "hh:mm"),
                               ui->dialTableWidget->item(i,2)->text().toDouble() );
            moneyInfo.timeInfos.append(timeInfo);
        }
        moneyInfoList.append(moneyInfo);
    }
    {
        MoneyInfo moneyInfo(1,ui->specialSpinBox->value());
        for ( int i=0; i<ui->specialTableWidget->rowCount(); i++)
        {
            TimeInfo timeInfo( QTime::fromString( ui->specialTableWidget->item(i,0)->text(), "hh:mm"),
                               QTime::fromString( ui->specialTableWidget->item(i,1)->text(), "hh:mm"),
                               ui->specialTableWidget->item(i,2)->text().toDouble() );
            moneyInfo.timeInfos.append(timeInfo);
        }
        moneyInfoList.append(moneyInfo);
    }


    XMLHelp config;
    config.write(moneyInfoList);
    this->accept();
}
