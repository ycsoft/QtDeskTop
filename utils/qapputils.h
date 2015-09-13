#ifndef QAPPUTILS_H
#define QAPPUTILS_H

#include <QObject>
#include <QSize>
#include <QHash>
#include <QPixmap>

#include "utils/defines.h"

class IconButton;

class QAppUtils : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief getScreenSize
     * 获取屏幕尺寸
     * @param i:屏幕编号
     * @return
     */
    QSize    getScreenSize(int i = -1);
    /**
     * @brief getScreenSize
     * 获取屏幕尺寸
     * @param wid:返回的屏幕宽度
     * @param hei:返回的屏幕高度
     */
    void     getScreenSize( int &wid, int &hei);

    /**
     * @brief getScreenWid
     * 获取屏幕宽度
     * @param i:屏幕编号
     * @return
     */
    int      getScreenWid(int i = -1);
    /**
     * @brief getScreenHei
     * 获取屏幕高度
     * @param i:屏幕编号
     * @return
     */
    int      getScreenHei(int i = - 1);

    static QAppUtils & ref()
    {
        static QAppUtils app;
        return app;
    }

    void  getAppList( QHash<QString,QString> &mapapp);
    /**
     * @brief getCloseIconBtn
     * 获得关闭按钮
     */
    IconButton*  getCloseIconBtn(QWidget *parent);

    QPixmap      &getAppIcon(const QString &path);

signals:

public slots:
private:
    explicit QAppUtils(QObject *parent = 0);

    QHash<QString, QString>         m_applist;
};

#endif // QAPPUTILS_H
