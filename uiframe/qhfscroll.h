#ifndef QHFSCROLL_H
#define QHFSCROLL_H

#include <QWidget>
#include <QScrollArea>

class QHFScroll : public QScrollArea
{
    Q_OBJECT
public:
    explicit QHFScroll(QWidget *parent = 0);

signals:

protected:
    void paintEvent(QPaintEvent *evt);
public slots:
};

#endif // QHFSCROLL_H
