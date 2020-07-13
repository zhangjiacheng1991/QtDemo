#ifndef TASKCLASS_H
#define TASKCLASS_H

#include <QObject>
#include "commandline.h"

class TaskClass : public QObject
{
    Q_OBJECT
public:
    explicit TaskClass(QObject *parent = nullptr);
    MSG_TYPE getMsgType();
    QString getUsername();
    QByteArray& getData();
    QObject* getObject();
    void setMsgType(MSG_TYPE type);
    void setUsername(QString name);
    void SetJsonObjct(QJsonObject& obj);
    void SetObject(QObject* obj);
    QJsonObject const & getJsonObject();
signals:

public slots:
private:
    MSG_TYPE m_type{TYPE_NULL};
    QString m_name{};
    QByteArray m_data;
    QObject* m_obj;
    QJsonObject m_json;
};

#endif // TASKCLASS_H
