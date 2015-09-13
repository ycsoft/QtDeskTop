#ifndef QHFWEBVIEW_H
#define QHFWEBVIEW_H

#include <QWidget>
#include <QWebView>

class QHFWebView : public QWebView
{
    Q_OBJECT
public:
    explicit QHFWebView(QWidget *parent = 0);

    void     setTransparent( bool );

protected:
//    void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // QHFWEBVIEW_H
