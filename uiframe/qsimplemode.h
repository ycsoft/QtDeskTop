#ifndef QSIMPLEMODE_H
#define QSIMPLEMODE_H

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

public slots:
    void addObject();

    QString invoke();

private:
    QWebView *web;
};

#endif // QSIMPLEMODE_H
