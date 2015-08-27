#ifndef QSCREENSELECTOR_H
#define QSCREENSELECTOR_H

#include <QWidget>


class QScreenSelector : public QWidget
{
    Q_OBJECT
public:
    explicit QScreenSelector(QWidget *parent = 0);
signals:

private:
    void initUI();

    void paintEvent(QPaintEvent *);
public slots:
    void slot_selectDesk(QString);

    void slot_showall(QString);
    void slot_showtodo(QString);
    void slot_showdone(QString);

};

#endif // QSCREENSELECTOR_H
