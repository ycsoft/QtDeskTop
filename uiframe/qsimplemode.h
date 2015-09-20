#ifndef QSIMPLEMODE_H
#define QSIMPLEMODE_H


#include "utils/qhfwebview.h"

#include <QWidget>
#include <QWebView>
#include <QWebSettings>
#include <QWebFrame>


class QSimpleMode : public QWidget
{
    Q_OBJECT
public:
    explicit QSimpleMode(QWidget *parent = 0);

private:
    void initUI();
signals:

protected:
    void contextMenuEvent(QContextMenuEvent *evt);
    void paintEvent(QPaintEvent *);
public slots:
    void addObject();


    QStringList invoke();
    QStringList getAllCanDoList();
    QString     get(QString sql);
    void        returnToAll();
private:
    QHFWebView *web;

};

#endif // QSIMPLEMODE_H
