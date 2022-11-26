#include "qiBase.h"

#include <QDebug>

/*------- CPromise ----------------------------------------*/
CPromise::CPromise(const QFuture<bool>& future) :
    QObject()
{
    m_pWatcher = new QFutureWatcher<bool>;

    connect(m_pWatcher, &QFutureWatcher<bool>::finished, this, [=] {
        callPromises();
        emit finished();
    });

    m_pWatcher->setFuture(future);
}

/*------- ~CPromise ---------------------------------------*/
CPromise::~CPromise()
{
    delete m_pWatcher; m_pWatcher = nullptr;
}

/*------------ callPromises -------------------------------*/
void CPromise::callPromises()
{
    while (m_qPromises.size())
    {
        auto fn = m_qPromises.dequeue();

        if (fn) fn();
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
