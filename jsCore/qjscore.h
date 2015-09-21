#ifndef QJSCORE_H
#define QJSCORE_H

#include "data/hfpgsql.h"

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

    ~QJSCore();

signals:

public slots:

    void     msgBox(const QString &title,const QString &txt);
    QString  readFromFile(const QString &fn);
    void     open(const QString &path);
    void     open(const QString &path,const QStringList &arglist);
    void     showWindow(QString);

    int      connectDB(QString host, QString dbname,QString usr,QString pwd);
    void     executeSQL(QString sql);

    int         getRecordCount();
    int         getColumnCount();
    QString      fieldValue( int row, int col);
private:
    HFPGSql         *m_pgsql;
};

#endif // QJSCORE_H
