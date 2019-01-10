#ifndef BILLDIALOG_H
#define BILLDIALOG_H

#include <QDialog>
#include <QDateTime>

class MoneyInfo;

namespace Ui {
class BillDialog;
}

class UserNetInfo   //用户上网流水信息
{
public:
    QString userID;         // 用户ID
    QDateTime beginTime;
    QDateTime endTime;
    int type;               // 用户类型
};

class MoneyInfo
{
public:
    QString userID;
    QDateTime beginTime;
    QDateTime endTime;
    double money;
};

class BillDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BillDialog(QList<UserNetInfo> userNetInfo,QWidget *parent = 0);
    ~BillDialog();

protected:
    void initTabWidget();
    void insertTableWidget(QList<MoneyInfo> moneyInfos);

private:
    Ui::BillDialog *ui;
    QList<MoneyInfo> m_moneyInfoList;
    QList<UserNetInfo> m_UserNetInfoList;
};

#endif // BILLDIALOG_H
