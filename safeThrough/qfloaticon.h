#ifndef QFLOATICON_H
#define QFLOATICON_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QEvent>
#include <QPaintEvent>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QContextMenuEvent>


class QFloatIcon : public QWidget
{
    Q_OBJECT
public:
    explicit QFloatIcon(QWidget *parent = 0);
    ~QFloatIcon(){}
protected:
    void    setupUI();
public slots:
    //获取动态口令
    void        onGetDynamicCode();
    //查看通知
    void        onViewSysNote();
    //自动更新
    void        onUpdate();
    //软件升级
    void        onSoftUpdate();
    //下载完毕
    void finished(const char *from,const char *filename);
    //退出程序
    void        onExit();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);


public:
    void setPixmap(const QPixmap &pixmap);
    void setContextMenu(QMenu*);
    void moveToRightTop();
signals:
    void DoubleClickSignal();

private:
    QMenu                       *_ctxMenu;
    QList<QAction*>             actions;
    QPoint                      m_currentPos;
    QPixmap                     m_pixmap;


};

#endif // QFLOATICON_H
