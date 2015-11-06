#ifndef QHTMLVIEWSYSMSGPANEL_H
#define QHTMLVIEWSYSMSGPANEL_H

#include "utils/qhfwebview.h"

#include <QWidget>

class QHtmlViewSysMsgPanel : public QWidget
{
    Q_OBJECT
public:
    explicit QHtmlViewSysMsgPanel(QWidget *parent = 0);

    ~QHtmlViewSysMsgPanel();


signals:

public slots:
    void    addObject();
    void    addMessage( QString title,  QString msg);
    void     anim_Show();
    void     anim_Hide();

protected:
    void            initUI();
private:
    QHFWebView      *m_web;
};

#endif // QHTMLVIEWSYSMSGPANEL_H
