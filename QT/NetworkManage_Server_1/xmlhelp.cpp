#include "xmlhelp.h"
#include <QFile>
#include <QApplication>
#include <QList>
#include <QTextStream>

XMLHelp::XMLHelp()
{

}

bool XMLHelp::read(QList<MoneyInfo>& moneyInfoList)
{
    m_moneyInfoList.clear();
    //实例QFile
    QString projectPath = qApp->applicationDirPath();
    QString fileName = projectPath + "/" + "config.xml";
    QFile file(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    m_doc.setContent(&file);
    QDomElement root = m_doc.documentElement();
    if(root.tagName()!= "configinfo")
    {
        return false;
    }
    QDomNode typesNode = root.firstChild();
    while ( !typesNode.isNull() )
    {
        QDomElement types = typesNode.toElement();
        if( !types.isNull())
        {
            if( types.nodeName() == "types" )
            {
                MoneyInfo moneyInfo;
                if(types.hasAttributes())
                {
                    QDomNamedNodeMap tmpMap = types.attributes();
                    for(int i = 0; i < (int)tmpMap.size();i++)
                    {
                        QString nodeName = tmpMap.item(i).nodeName();
                        QString nodeValue = tmpMap.item(i).nodeValue();
                        if("type" == nodeName)
                        {
                            moneyInfo.type = nodeValue.toInt();
                        }
                        else if("money" == nodeName)
                        {
                            moneyInfo.money = nodeValue.toDouble();
                        }
                    }
                }
                QDomNodeList typesList = types.childNodes();
                for(int a=0; a<typesList.count(); a++) //遍历该列表
                {
                    QDomNode node = typesList.at(a);
                    if(node.isElement())
                    {
                        if( node.nodeName() == "M" )
                        {
                            TimeInfo timeInfo;
                            if(node.hasAttributes())
                            {
                                QDomNamedNodeMap tmpMap = node.attributes();
                                for(int i = 0; i < (int)tmpMap.size();i++)
                                {
                                    QString nodeName = tmpMap.item(i).nodeName();
                                    QString nodeValue = tmpMap.item(i).nodeValue();
                                    if("beginTime" == nodeName)
                                    {
                                        timeInfo.beginTime = QTime::fromString(nodeValue,"hh");
                                    }
                                    else if("endTime" == nodeName)
                                    {
                                        timeInfo.endTime = QTime::fromString(nodeValue,"hh");
                                    }
                                    else if("money" == nodeName)
                                    {
                                        timeInfo.money = nodeValue.toDouble();
                                    }
                                }
                            }
                            moneyInfo.timeInfos.append(timeInfo);
                        }
                    }
                }
                m_moneyInfoList.append(moneyInfo);
            }
        }
        typesNode = typesNode.nextSibling();
    }
    file.close();
    moneyInfoList = m_moneyInfoList;
    return true;
}

bool XMLHelp::write(QList<MoneyInfo> moneyInfoList)
{
    QString projectPath = qApp->applicationDirPath();
    QString fileName = projectPath + "/" + "config.xml";
    QFile file(fileName);
    if(!file.open( QFile::WriteOnly | QFile::Truncate))
    {
        return false;
    }
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement("configinfo");
    doc.appendChild(root);
    foreach(MoneyInfo moneyInfo , moneyInfoList)
    {
        QDomElement typesRoot = doc.createElement("types");
        typesRoot.setAttribute("type",  QString("%1").arg(moneyInfo.type));
        typesRoot.setAttribute("money", QString("%1").arg(moneyInfo.money) );
        QList<TimeInfo> timeInfos = moneyInfo.timeInfos;
        foreach (TimeInfo timeInfo, timeInfos)
        {
            QDomElement M = doc.createElement("M");
            M.setAttribute("beginTime", timeInfo.beginTime.toString("hh"));
            M.setAttribute("endTime",   timeInfo.endTime.toString("hh"));
            M.setAttribute("money",     QString("%1").arg(timeInfo.money) );
            typesRoot.appendChild(M);
        }
        root.appendChild(typesRoot);
    }

    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
    return true;
}
