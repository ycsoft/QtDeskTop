#ifndef QMESSAGEWIDGETS_H
#define QMESSAGEWIDGETS_H


#include <QWidget>
#include <QLabel>

#include "uiframe/qnoframewin.h"

class QMessageWidgets : public QNoFrameWin
{
    Q_OBJECT
public:
    explicit QMessageWidgets(QWidget *parent = 0);
    ~QMessageWidgets(){}

    /**
     * @brief initUI
     * 创建界面UI
     */
    void initUI();

    /**
     * @brief setMessage
     * 设置消息内容
     */
    void setMessage(const QString&);

private:
    /**
     * @brief mouseMoveEvent
     * 覆盖鼠标移动事件
     */
    void mouseMoveEvent(QMouseEvent *);
signals:

public slots:
private:
    QLabel          *m_lbmsg;

};

#endif // QMESSAGEWIDGETS_H
