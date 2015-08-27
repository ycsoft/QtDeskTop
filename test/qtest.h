#ifndef QTEST_H
#define QTEST_H

#include <QObject>

#include <QWidget>

#include "sysMsg/qsysmessagepanel.h"
#include "uiframe/qnoframewin.h"

#include <QVector>

class QTest : public QObject
{
    Q_OBJECT
public:
    explicit QTest(QObject *parent = 0);

    ~QTest();

    void     run(QWidget *wid);

signals:

public slots:

private:
    QVector<QWidget*> _tofree;
};

#endif // QTEST_H
