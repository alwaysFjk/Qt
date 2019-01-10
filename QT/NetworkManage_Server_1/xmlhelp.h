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
    // �� beginTime �� endTime ���շ� money
    // beginTime �� endTime ��С��λΪСʱ�� ����06��00, ��������06��30
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

    int type;           // �û�����
    double money;       // �û���׼�շ�
    QList<TimeInfo> timeInfos;      // �ۿ�����
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
