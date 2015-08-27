#ifndef QTIPTXT_H
#define QTIPTXT_H

#include <QLabel>
#include <QWidget>

class QTipTxt : public QWidget
{
    Q_OBJECT
public:
    explicit QTipTxt(QWidget *parent = 0);
    ~QTipTxt()
    {

    }

    void setupUi();

    void setText(QString txt);
    void setIcon(QString iconpath);



signals:

public slots:

protected:
    void paintEvent(QPaintEvent *evt);

    void enterEvent(QEvent *evt);
    void leaveEvent(QEvent *evt);
private:

    QLabel *_lb_ico;
    QLabel *_lb_txt;
    QString _txt;
    bool    _benter;
};

#endif // QTIPTXT_H
