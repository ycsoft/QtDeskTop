#ifndef QSINGLESCREEN_H
#define QSINGLESCREEN_H

#include <QWidget>

class QSingleScreen : public QWidget
{
    Q_OBJECT
public:
    explicit QSingleScreen(QWidget *parent = 0);

    ~QSingleScreen(){}

private:
    void initUI();

signals:

public slots:
private:
    QImage              m_img;
};

#endif // QSINGLESCREEN_H
