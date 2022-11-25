#include "queryImpl.h"

#include <QDebug>

/*--------- CQueryImpl ------------------------------------*/
CQueryImpl::CQueryImpl() : CQIBase()
{
}

CQueryImpl::~CQueryImpl()
{
}

void CQueryImpl::startTest(int val1, int val2)
{
    startTask(EQUERY_TESTING, this, &CQueryImpl::largeMethod, 200, 50, 100)
        ->callback(&CQueryImpl::callBackTest, this, val1, val2);
}

void CQueryImpl::callBackTest(int val1, int val2)
{
    qDebug() << "TEST CALLBACK\t" << val1 << "\t" << val2;
}

bool CQueryImpl::largeMethod(int val1, int val2, int val3)
{
    long long res = 0;
    for (int i = 0; i < val1; i++)
    {
        res += (i - val2) + val3;
    }

    return true;
}
