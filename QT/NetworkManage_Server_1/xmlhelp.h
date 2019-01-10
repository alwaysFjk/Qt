#ifndef XMLHELP_H
#define XMLHELP_H

#include <QObject>
#include <QFile>
#include <QMap>
#include <QDomDocument>
#include <QXmlStreamReader>
#include <QTime>

class TimeInfo
{
    // 在 beginTime 到 endTime 内收费 money
    // beginTime 与 endTime 最小单位为小时， 例如06：00, 而不会是06：30
public:
    TimeInfo(){}
    TimeInfo(QTime begin,QTime end,double dMoney)
    {
        beginTime = begin;
        endTime = end;
        money = dMoney;
    }
    QTime beginTime;
    QTime endTime;
    double money;
};

class MoneyInfo
{
public:
    MoneyInfo(){}
    MoneyInfo(int nType,double dMoney)
    {
        type = nType;
        money = dMoney;
    }

    int type;           // 用户类型
    double money;       // 用户标准收费
    QList<TimeInfo> timeInfos;      // 折扣政策
};

class XMLHelp
{
public:
    XMLHelp();
    bool read(QList<MoneyInfo>& moneyInfoList);
    bool write(QList<MoneyInfo> moneyInfoList);

private:
    QDomDocument m_doc;

    QList<MoneyInfo> m_moneyInfoList;

};

#endif // XMLHELP_H
