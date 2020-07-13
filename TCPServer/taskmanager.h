#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <QThread>
#include <QList>
#include "taskclass.h"
#include <QWaitCondition>
#include <QMutex>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class TaskManager : public QThread
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);
    void addTask(TaskClass* newtask);
//    TaskClass* popTask();
    void clearTask();
    void loginTaskPorcess(TaskClass* curTask);
    void modifyTaskPorcess(TaskClass* curTask);
    void increaseTaskPorcess(TaskClass* curTask);
    void deleteTaskPorcess(TaskClass* curTask);
    void queryTaskPorcess(TaskClass* curTask);
    void closeThread();
signals:
    void CommandExecultione(QObject* client,QByteArray result);
public slots:
protected:
    void run();
private:
    QList<TaskClass*> m_taskList;
    QWaitCondition m_wd;
    QSqlDatabase m_db;
    QMutex m_mutex;
    bool m_running{true};
};

#endif // TASKMANAGER_H
