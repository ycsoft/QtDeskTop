#ifndef QDOCKER_H
#define QDOCKER_H

#include <QWidget>
#include <QWebView>
class QDocker : public QWidget
{
    Q_OBJECT
public:
    explicit QDocker(QWidget *parent = 0);
    ~QDocker(){}

    void addApp(QPixmap &pix,QString &title, QString &path);
    void addApp(QString &path, QString &title);
signals:

public slots:

protected:
    void    initUI();
    void    paintEvent(QPaintEvent *evt);

    void mousePressEvent(QMouseEvent *evt);

    void mouseReleaseEvent(QMouseEvent *evt);

    void mouseMoveEvent(QMouseEvent *evt);
private:
    QWebView    *m_web;
    bool        m_pressed;
    QPoint      m_movePoint;
    int         m_appCount;
};

#endif // QDOCKER_H
