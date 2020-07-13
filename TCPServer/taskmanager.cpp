#include "taskmanager.h"
#include "commandline.h"
#include <QString>

TaskManager::TaskManager(QObject *parent) : QThread(parent)
{
}

void TaskManager::addTask(TaskClass *newtask)
{
    m_taskList.push_back(newtask);
    m_wd.wakeAll();
}
//登录侦:"type":TYPE_LOGIN,"name":"","pwd":""
void TaskManager::loginTaskPorcess(TaskClass *curTask)
{
    CommandLine cl;
    QSqlQuery query;
    QString sqlstr = QString("SELECT password FROM employee where name = '%1'")
            .arg(curTask->getJsonObject().value("name").toString());
    query.exec(sqlstr);
    if(query.isActive() && query.isSelect())
    {
        query.next();
        QString pwd = query.value("password").toString();
        if(!pwd.isEmpty() && 0 == pwd.compare(curTask->getData()))
        {
            emit CommandExecultione(curTask->getObject(),cl.CreateResultMsg());
        }
        else
        {
            emit CommandExecultione(curTask->getObject(),cl.CreateResultMsg(300,"密码错误"));
        }
    }
    else
    {
        QString err = query.lastError().text();
        emit CommandExecultione(curTask->getObject(), cl.CreateResultMsg(1,err));
    }

}

//修改侦:"type":TYPE_MODIFY,"table":"","key":"","value":""
void TaskManager::modifyTaskPorcess(TaskClass *curTask)
{

}

//插入侦:"type":TYPE_INCREASE,"table":str,"value":str
void TaskManager::increaseTaskPorcess(TaskClass *curTask)
{
    CommandLine cl;
    QSqlQuery query;
    QString sqlstr = QString("insert into %1 values '%2' ")
            .arg(curTask->getJsonObject().value("table").toString())
            .arg(curTask->getJsonObject().value("value").toString());

    if(query.exec(sqlstr))
    {
        emit CommandExecultione(curTask->getObject(),cl.CreateResultMsg());
    }
    else
    {
        QString err = query.lastError().text();
        emit CommandExecultione(curTask->getObject(), cl.CreateResultMsg(1,err));
    }
}

//删除侦:"type":TYPE_DELETE,"table":"","key":"","value":""
void TaskManager::deleteTaskPorcess(TaskClass *curTask)
{
    CommandLine cl;
    QSqlQuery query;
    QString sqlstr = QString("delete from %1 where %2 = '%3' ")
            .arg(curTask->getJsonObject().value("table").toString())
            .arg(curTask->getJsonObject().value("key").toString())
            .arg(curTask->getJsonObject().value("value").toString());;

    if(query.exec(sqlstr))
    {
        emit CommandExecultione(curTask->getObject(),cl.CreateResultMsg());
    }
    else
    {
        QString err = query.lastError().text();
        emit CommandExecultione(curTask->getObject(), cl.CreateResultMsg(1,err));
    }
}

//查询侦:"type":TYPE_QUERY,"values":str,"table":str,"where":{"key":str,"w_value":str},"orderby""value"
void TaskManager::queryTaskPorcess(TaskClass *curTask)
{
    CommandLine cl;
    QSqlQuery query;
    QString sqlstr = QString("SELECT %1 FROM %2 where %3 = '%4' ")
            .arg(curTask->getJsonObject().value("values").toString())
            .arg(curTask->getJsonObject().value("table").toString())
            .arg(curTask->getJsonObject().value("where").toString())
            .arg(curTask->getJsonObject().value("key").toString())
            .arg(curTask->getJsonObject().value("value").toString());
    query.exec(sqlstr);
    if(query.isActive() && query.isSelect())
    {
        query.next();
//        query.
        QString pwd = query.value("password").toString();
        if(!pwd.isEmpty() && 0 == pwd.compare(curTask->getData()))
        {
            emit CommandExecultione(curTask->getObject(),cl.CreateResultMsg());
        }
        else
        {
            emit CommandExecultione(curTask->getObject(),cl.CreateResultMsg(300,"密码错误"));
        }
    }
    else
    {
        QString err = query.lastError().text();
        emit CommandExecultione(curTask->getObject(), cl.CreateResultMsg(1,err));
    }
}

void TaskManager::closeThread()
{
    if(isRunning())
    {
        m_running = false;
        m_wd.wakeAll();
    }
    msleep(100);
    if(isRunning())
    {
        terminate();
    }
}

void TaskManager::run()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("test.db");
    if(!m_db.open())
    {
        throw  QString("数据库打开失败");
    }
    while (m_running)
    {
        if(m_taskList.size() <= 0)
        {
            m_mutex.lock();
            m_wd.wait(&m_mutex);
            if(!m_running)
            {
                return;
            }
        }
        TaskClass* curTask = m_taskList.first();
        m_taskList.pop_front();
        switch (curTask->getMsgType())
        {
        case  MSG_TYPE::TYPE_LOGIN :
            //登录
            loginTaskPorcess(curTask);
            break;
        case  MSG_TYPE::TYPE_QUERY :
            //查询
            queryTaskPorcess(curTask);
            break;
        case  MSG_TYPE::TYPE_MODIFY :
            //修改
            modifyTaskPorcess(curTask);
            break;
        case  MSG_TYPE::TYPE_INCREASE :
            //增加
            increaseTaskPorcess(curTask);
            break;
        case  MSG_TYPE::TYPE_DELETE :
            //删除
            deleteTaskPorcess(curTask);
            break;
        default:
            qCritical() << tr("信息类型错误");
            break;
        }
        m_mutex.unlock();
    }

}
