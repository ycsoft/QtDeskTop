#ifndef QTIPS_H
#define QTIPS_H


#include "skin/iconbutton.h"
#include "skin/framelesswin.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

/**
 * @brief The QTips class
 *
 * 实现推送消息的显示
 *
 */

class QTipTxt;

class QTips : public FramelessWin
{
    Q_OBJECT
public:
    explicit QTips(QWidget *parent = 0);
    ~QTips();

    void  SetupUI();


    /**
     * @brief setTipTitle
     * @param title
     */
    void  setTipTitle( QString title)
    {
        _title = title;
        _lbtitle->setText(title);
    }
    /**
     * @brief getTipTitle
     * @return
     */
    QString getTipTitle()
    {
        return _title;
    }

    void removeTips(QWidget *);

    void paintEvent(QPaintEvent *evt);

    void addNotifyText(QString txt);

signals:

public slots:

    void click_close();

protected:
//    void mousePressEvent(QMouseEvent *evt);
//    void mouseMoveEvent(QMouseEvent *evt);
//    void mouseReleaseEvent(QMouseEvent *evt);

private:
    QString         _title; //提示的主体

    QTipTxt         *_preText;

    QLabel          *_lbtitle;
    QVBoxLayout     *_vlay;
    IconButton      *_preBtn;
    IconButton      *_nextBtn;

    bool            _pressed;
    QPoint          _movepoint;
    QWidget         *txtWidget;
};

#endif // QTIPS_H
