#include "qtest.h"
#include "utils/qapputils.h"

QTest::QTest(QObject *parent) : QObject(parent)
{

}

void QTest::run(QWidget *wid)
{
    int width,hei;
    QAppUtils::ref().getScreenSize(width,hei);

    //wid->resize(width/3,hei);
    wid->show();
    _tofree.push_back(wid);
}

QTest::~QTest()
{
    QVector<QWidget*>::iterator it = _tofree.begin();

    while ( it != _tofree.end())
    {
        delete *it;
        ++it;
    }
    _tofree.clear();
}
