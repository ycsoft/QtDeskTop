#ifndef QLOGINDESKTOP_H
#define QLOGINDESKTOP_H

#include <QWidget>
#include <QWebView>

class QLoginDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit QLoginDesktop(QWidget *parent = 0);

signals:

public slots:
    void    showMain();
    void    addObject();
    void    exitApp();
protected:
    void    initUI();
private:

    QWebView    *m_web;
};

#endif // QLOGINDESKTOP_H
