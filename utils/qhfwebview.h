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
    void     load(const QUrl& url);

protected:
//    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *evt);
signals:

public slots:
    void    registerObject();
    void    download(const QNetworkRequest &req);
    void    downloadFinish();
};

#endif // QHFWEBVIEW_H
