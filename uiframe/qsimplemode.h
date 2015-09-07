#ifndef QSIMPLEMODE_H
#define QSIMPLEMODE_H

#include <QWidget>

class QSimpleMode : public QWidget
{
    Q_OBJECT
public:
    explicit QSimpleMode(QWidget *parent = 0);

private:
    void initUI();
signals:

public slots:
};

#endif // QSIMPLEMODE_H
