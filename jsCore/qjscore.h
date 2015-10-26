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


    ~QJSCore();

    static QJSCore *ref()
    {
        static QJSCore js;
        return &js;
    }

signals:

public slots:

    void     msgBox(const QString &title,const QString &txt);
    QString  readFromFile(const QString &fn);
    void     saveData(const QString &fn,const QString &data);
    void     open(const QString &path);
    void     exec(const QString &path);
    void     open(const QString &path,const QStringList &arglist);
    QString  showWindow(QString);
    void     close();
    int      connectDB(QString host, int port, QString dbname,QString usr,QString pwd);
    void     executeSQL(QString sql);
    void     download ( QString url );
    QString  nameFromURL( QString url);

    int         getRecordCount();
    int         getColumnCount();
    QString      fieldValue( int row, int col);
    void        setSoftInfo(QString info) { m_addsoft = info;}
    QString     getSoftInfo() { return m_addsoft;}

    void        executeSQL(QString sql,QString etti);
private:
    explicit QJSCore(QObject *parent = 0);
    HFPGSql         *m_pgsql;

    ///
    /// \brief 要添加的软件信息
    ///
    QString         m_addsoft;
};

#endif // QJSCORE_H
