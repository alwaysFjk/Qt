#include "billdialog.h"
#include "ui_billdialog.h"
#include "xmlhelp.h"
#include <QTableWidget>

BillDialog::BillDialog(QList<UserNetInfo> userNetInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BillDialog)
    ,m_UserNetInfoList(userNetInfo)
{
    ui->setupUi(this);

    this->setWindowTitle(QString::fromLocal8Bit("账单"));

    XMLHelp config;
    config.read(m_moneyInfoList);

    initTabWidget();
}

BillDialog::~BillDialog()
{
    delete ui;
}

void BillDialog::initTabWidget()
{
    // 取 变量m_moneyInfoList,m_UserNetInfoList  算出每一笔流水的消费金额
    //...

    // 每个用户 使用一个QList<MoneyInfo>
    // 计算完 塞入insertTableWidget(); 中
}

void BillDialog::insertTableWidget(QList<MoneyInfo> moneyInfos)
{
    if (moneyInfos.count() > 0)
    {
        QTableWidget *tableWidget = new QTableWidget(this);
        tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("ID")));
        tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("上网时间")));
        tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("断网时间")));
        tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromLocal8Bit("费用（元）")));
        tableWidget->setColumnWidth(0, 200);
        tableWidget->setColumnWidth(1, 150);
        tableWidget->setColumnWidth(2, 150);
        tableWidget->setColumnWidth(3, 50);

        foreach(MoneyInfo moneyInfo, moneyInfos)
        {
            tableWidget->insertRow(0);
            tableWidget->setItem(0, 0, new QTableWidgetItem(moneyInfo.userID));
            tableWidget->setItem(0, 1, new QTableWidgetItem(moneyInfo.beginTime.toString("yyyy-MM-dd hh:mm:ss")));
            tableWidget->setItem(0, 2, new QTableWidgetItem(moneyInfo.endTime.toString(  "yyyy-MM-dd hh:mm:ss")));
            tableWidget->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(moneyInfo.money)));
        }
        // 再算一个总价
        ui->tabWidget->addTab( tableWidget, moneyInfos.at(0).userID);
    }
}
