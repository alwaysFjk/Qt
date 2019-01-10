#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDateTime>
#include <QString>
#include "adduserdialog.h"
#include "settingdialog.h"
#include "billdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init tableWidget1
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("ID")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("上网时间")));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("断网时间")));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromLocal8Bit("用户类型")));
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 50);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->verticalHeader()->setVisible(false);                   //隐藏列表头
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);       //关键
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);

    // init tableWidget2s
    ui->tableWidget_2->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("ID")));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("姓名")));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("电话号码")));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromLocal8Bit("用户类型")));
    ui->tableWidget_2->setColumnWidth(0, 200);
    ui->tableWidget_2->setColumnWidth(1, 200);
    ui->tableWidget_2->setColumnWidth(2, 150);
    ui->tableWidget_2->setColumnWidth(3, 50);

    ui->tableWidget_2->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows );  //整行选中的方式
    ui->tableWidget_2->verticalHeader()->setVisible(false);                   //隐藏列表头
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);       //关键
    ui->tableWidget_2->horizontalHeader()->setHighlightSections(false);

    // init tabwidget
    ui->tabWidget->setTabText( 0, QString::fromLocal8Bit("网络流水") );
    ui->tabWidget->setTabText( 1, QString::fromLocal8Bit("人员信息") );

    // init
    QDateTime dtBegin = QDateTime::currentDateTime();
    dtBegin.setTime(QTime(0, 0, 0));
    QDateTime dtEnd = dtBegin;
    dtEnd.setTime(QTime(23, 59, 59));
    ui->beginTimeEdit->setDateTime(dtBegin);
    ui->endTimeEdit->setDateTime(dtEnd);
    ui->beginTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->endTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    // 初始化的时候 查询人员信息
    on_searchUserButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exportButton_clicked()
{
    QList<UserNetInfo> userNetInfos;
    for (int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        UserNetInfo userNetInfo;
        userNetInfo.userID = ui->tableWidget->item(i,0)->text();
        userNetInfo.beginTime = QDateTime::fromString( ui->tableWidget->item(i,1)->text(), "yyyy-MM-dd hh:mm:ss");
        userNetInfo.endTime = QDateTime::fromString( ui->tableWidget->item(i,2)->text(), "yyyy-MM-dd hh:mm:ss");
        userNetInfo.type = ui->tableWidget->item(i,3)->text().toInt();

        userNetInfos.append(userNetInfo);
    }

    // 根据 tab1 的表格 生辰账单
    BillDialog dialog(userNetInfos , this);
    dialog.exec();
}

void MainWindow::on_searchLoginButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setHostName("118.25.74.128");            //118.25.74.128 为私有腾讯云上的服务器
    db.setDatabaseName("networkmanage");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("failed"),
        "failed", QMessageBox::Cancel);
        db.close();
        return;
    }
    QSqlQuery query(db);
    QString userID = ui->lineEdit->text();
    QString str = QString("select *from timeinfo where name = '%1' and beginTime < '%2' and endTime > '%3' ")
            .arg(userID)
            .arg(ui->beginTimeEdit->dateTime().toTime_t())
            .arg(ui->endTimeEdit->dateTime().toTime_t());
    if ( userID == "")
    {
        str = QString("select *from timeinfo where beginTime > '%1' and endTime < '%2' ")
            .arg(ui->beginTimeEdit->dateTime().toTime_t())
            .arg(ui->endTimeEdit->dateTime().toTime_t());;
    }
    query.exec(str);
    while (query.next())
    {
        ui->tableWidget->insertRow(0);
        QDateTime beginDateTime = QDateTime::fromTime_t( query.value(1).toInt());
        QDateTime endDateTime =   QDateTime::fromTime_t( query.value(2).toInt());
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(beginDateTime.toString("yyyy-MM-dd hh:mm:ss")));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(endDateTime.toString(  "yyyy-MM-dd hh:mm:ss")));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));

    }
    db.close();
}

void MainWindow::on_searchUserButton_clicked()
{
    ui->tableWidget_2->setRowCount(0);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setHostName("118.25.74.128");        //118.25.74.128 为私有腾讯云上的服务器
    db.setDatabaseName("networkmanage");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("failed"),
        "failed", QMessageBox::Cancel);
        db.close();
        return;
    }
    QSqlQuery query(db);
    QString userID = ui->lineEdit->text();
    QString str = QString("select *from userinfo where name = '%1'").arg(userID);
    if ( userID == "")
    {
        str = "select *from userinfo";
    }
    query.exec(str);
    while (query.next())
    {
        ui->tableWidget_2->insertRow(0);
        ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_2->setItem(0, 2, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem(query.value(4).toString()));
    }
    db.close();
}

void MainWindow::on_exportSettingButton_clicked()
{
    SettingDialog dialog(this);
    dialog.exec();
}


void MainWindow::on_addUserButton_clicked()
{
    AddUserDialog dialog(this);
    if ( dialog.exec() == QDialog::Accepted)
    {
        // 添加人员
        QString userID;
        QString password;
        QString userName;
        QString phone;
        int type;
        dialog.getInfo(userID, password, userName, phone, type);

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setPort(3306);
        db.setHostName("118.25.74.128");        //118.25.74.128 为私有腾讯云上的服务器
        db.setDatabaseName("networkmanage");
        db.setUserName("root");
        db.setPassword("123456");
        if (!db.open())
        {
            QMessageBox::critical(0, QObject::tr("failed"),
            "failed", QMessageBox::Cancel);
            db.close();
            return;
        }
        QSqlQuery query(db);
        QString str = QString("INSERT INTO `networkmanage`.`userinfo`(`userID`, `password`, `userName`, `phone`, `type`) "
                              "VALUES ('%1', '%2', '%3', '%4', '%5');")
                .arg(userID)
                .arg(password)
                .arg(userName)
                .arg(phone)
                .arg(type);
        query.exec(str);
        db.close();

        on_searchUserButton_clicked();
    }
}

void MainWindow::on_delUserButton_clicked()
{
    int row = ui->tableWidget_2->currentRow();
    QString userID = ui->tableWidget_2->item(row,0)->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setHostName("118.25.74.128");        //118.25.74.128 为私有腾讯云上的服务器
    db.setDatabaseName("networkmanage");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("failed"),
        "failed", QMessageBox::Cancel);
        db.close();
        return;
    }
    QSqlQuery query(db);
    QString str = QString(" DELETE FROM `userinfo` WHERE userID='%1';")
            .arg(userID);
    query.exec(str);
    db.close();

    on_searchUserButton_clicked();
}
