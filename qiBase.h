#ifndef QIBASE_H
#define QIBASE_H

#include <QObject>
#include <QtConcurrent>
#include <functional>
#include <QThread>

enum EQUERY
{
    EQUERY_NONE         = 0,
    EQUERY_TESTING
};

class CPromise : public QObject
{
    Q_OBJECT

public:
    explicit CPromise(const QFuture<bool>& future);
            ~CPromise();

public:
    template <class Function, class... Args>
    void callback(Function &&f, Args&&... args)
    {
        m_callback = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
//        m_callback();
    }

public:
    void    call_callback   ();

signals:
    void    finished        ();

private:
    QFutureWatcher<bool>*   m_pWatcher;

    std::function<void()>   m_callback = nullptr;
};

//=======================================================================================

class CQICounterTask : public QObject
{

public:
    CQICounterTask() : QObject() {}
    ~CQICounterTask();

public:
    CPromise* addTask(EQUERY task, const QFuture<bool>& future);

private:
    QMap<CPromise*, EQUERY>  m_mapTasks;

};

//=======================================================================================

class CQIBase : public CQICounterTask
{
    Q_OBJECT

protected:
        CQIBase() : CQICounterTask() {}
        ~CQIBase() {}

protected:
    template <class Object, class Function, class... Args>
    CPromise* startTask(EQUERY task, Object* obj, Function &&f, Args&&... args);
};

template <class Object, class Function, class... Args>
CPromise* CQIBase::startTask(EQUERY task, Object* obj, Function &&f, Args&&... args)
{
    return addTask(task, QtConcurrent::run(obj, std::forward<Function>(f), std::forward<Args>(args)...));
}

#endif // QIBASE_H
