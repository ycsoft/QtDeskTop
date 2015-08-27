#ifndef TASKBAR_H
#define TASKBAR_H

#include <QWidget>

class TaskBar : public QWidget
{
    Q_OBJECT
public:
    explicit TaskBar(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *evt);
signals:

public slots:

};

#endif // TASKBAR_H
