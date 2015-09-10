#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QVector>


class QMouseEvent;
class QEvent;
class QPaintEvent;
class QPixmap;
class QLabel;


class IconButton2 : public QPushButton
{
    Q_OBJECT
public:

    enum Status{
                BUTTON_FIRST,
                BUTTON_SCALED,
                BUTTON_ENTER,
                BUTTON_LEAVE,
                BUTTON_PRESSED,
                BUTTON_DISABLE
                };

    explicit IconButton2(QWidget *parent = 0,
                        QString iconnormal="",QString iconHigh="",QString icondown="");

    void SetButtonText(QString txt);

    void SetTextStyle(QString style);

    void SetButtonIcon(QString iconpath);

    void AddTxtLabel();

    void SetStatus(int status);

    void enterEvent(QEvent *evt);

    void leaveEvent(QEvent *evt);

    void mousePressEvent(QMouseEvent *evt);

    void mouseReleaseEvent(QMouseEvent *evt);

    void paintEvent(QPaintEvent *evt);

signals:

public slots:

private:
    QPixmap                     m_cur_icon;
    QVector<QPixmap>            m_icon_list;
    QString                     m_txt;
    QLabel                      *m_txt_lb;
    int                         m_status;

};

#endif // ICONBUTTON_H
