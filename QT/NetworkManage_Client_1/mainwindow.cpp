#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_updateTime()));
    timer->start(1000);
    slot_updateTime();

    ui->widget_2->setVisible(false);
    // 设置tab键焦点
    ui->lineEdit->setFocus();
    setTabOrder(ui->lineEdit, ui->lineEdit_2);
    setTabOrder(ui->lineEdit_2, ui->loginButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_updateTime()
{
    ui->dateTimeEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
}

void MainWindow::on_loginButton_clicked()
{
    QString userID = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    int type = ui->comboBox->currentIndex();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setHostName("localhost");
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
    QString str = QString("select *from userinfo where userID = '%1' and password = '%2' and type = '%3'")
            .arg(userID)
            .arg(password)
            .arg(type);
    query.exec(str);
    if (query.seek(0) )
    {
        // 登陆成功
        ui->widget_1->setVisible(false);
        ui->widget_2->setVisible(true);
        m_loginDateTime = QDateTime::currentDateTime();
    }
    else
    {
        QMessageBox::critical(0, QObject::tr("failed"),
        "login failed", QMessageBox::Cancel);
        db.close();
        return;
    }
    db.close();
    return ;
}


void MainWindow::on_logoutButton_clicked()
{
    ui->widget_2->setVisible(false);
    ui->widget_1->setVisible(true);
    QString userID = ui->lineEdit->text();
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
    QString str = QString("INSERT INTO `networkmanage`.`timeinfo`(`userID`, `beginTime`, `endTime`, `type`) VALUES ('%1','%2','%3','%4');")
            .arg(userID)
            .arg( m_loginDateTime.toTime_t() )
            .arg( QDateTime::currentDateTime().toTime_t()  )
            .arg( ui->comboBox->currentIndex());
    query.exec(str);
    db.close();
}
