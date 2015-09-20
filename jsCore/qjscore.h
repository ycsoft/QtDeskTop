#ifndef QJSCORE_H
#define QJSCORE_H

#include <QObject>
#include <QWidget>
/**
 * @brief The QJSCore class
 *封装一些本地方法，供js调用
 *
 */
class QJSCore : public QObject
{
    Q_OBJECT
public:
    explicit QJSCore(QObject *parent = 0);

signals:

public slots:

    void     msgBox(const QString &title,const QString &txt);
    QString  readFromFile(const QString &fn);
    void     open(const QString &path);
    void     open(const QString &path,const QStringList &arglist);
    void     showWindow(QString);
};

#endif // QJSCORE_H
