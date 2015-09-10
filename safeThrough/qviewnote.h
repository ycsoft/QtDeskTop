#ifndef QVIEWNOTE_H
#define QVIEWNOTE_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QEvent>
#include <QPaintEvent>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QContextMenuEvent>
#include <QLabel>

class QViewNote : public QWidget
{
    Q_OBJECT
public:
    explicit QViewNote(QWidget *parent = 0);
    ~QViewNote(){}
protected:
    void    setupUI();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public:
    void setText(QString txt);
    void setPixmap(const QPixmap &pixmap);
    void moveToRightTop();


private:
    QPoint                      m_currentPos;
    QPixmap                     m_pixmap;
    QLabel                      *m_label;
};

#endif // QVIEWNOTE_H
