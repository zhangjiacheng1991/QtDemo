#include "taskclass.h"


TaskClass::TaskClass(QObject *parent) : QObject(parent)
{

}

MSG_TYPE TaskClass::getMsgType()
{
    return m_type;
}

QString TaskClass::getUsername()
{
    return m_name;
}

QByteArray &TaskClass::getData()
{
    return m_data;
}

QObject* TaskClass::getObject()
{
    return m_obj;
}

void TaskClass::setMsgType(MSG_TYPE type)
{
    m_type = type;
}

void TaskClass::setUsername(QString name)
{
    m_name = name;
}

void TaskClass::SetJsonObjct(QJsonObject &obj)
{
    m_json = obj;
}

void TaskClass::SetObject(QObject *obj)
{
    m_obj = obj;
}

QJsonObject const &TaskClass::getJsonObject()
{
    return m_json;
}
