#ifndef QTRANSPARENTWIN_H
#define QTRANSPARENTWIN_H

#include <QWidget>

class QTransparentWin : public QWidget
{
    Q_OBJECT
public:
    explicit QTransparentWin(QWidget *parent = 0);
    ~QTransparentWin() {}

signals:

public slots:
};

#endif // QTRANSPARENTWIN_H
