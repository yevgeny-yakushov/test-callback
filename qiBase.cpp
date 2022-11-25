#include "qiBase.h"

#include <QDebug>

/*------- CPromise ----------------------------------------*/
CPromise::CPromise(const QFuture<bool>& future) :
    QObject()
{
    m_pWatcher = new QFutureWatcher<bool>;

    connect(m_pWatcher, &QFutureWatcher<bool>::finished, this, [=] {
        emit finished();
        call_callback();
    });

    m_pWatcher->setFuture(future);
}

/*------- ~CPromise ---------------------------------------*/
CPromise::~CPromise()
{
    delete m_pWatcher; m_pWatcher = nullptr;
}

/*------------ call_callback ------------------------------*/
void CPromise::call_callback()
{
    if (m_callback)
    {
        qDebug() << "CALL FROM CPP";
        m_callback();
    }
}

/*------------- ~CQICounterTask ---------------------------*/
CQICounterTask::~CQICounterTask()
{
    for (CPromise* promise : m_mapTasks.keys())
        delete promise;
}

/*----------------------- addTask -------------------------*/
CPromise* CQICounterTask::addTask(EQUERY task, const QFuture<bool>& future)
{
    CPromise* promise = new CPromise(future);

    m_mapTasks.insert(promise, task);

    connect(promise, &CPromise::finished, this, [=] {
        m_mapTasks.remove(promise);
        delete promise;
    });

    return promise;
}
