#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTimerEvent>
#include <QMenu>
#include <QAction>
#include <QMap>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QMouseEvent>
#include <QMap>
#include <QList>

#include "skin/framelesswin.h"

class AppConfig
{
public:
    QString title;
    QString path;
};

class Panel : public FramelessWin
{
    Q_OBJECT
public:
    enum {RowCount = 10,ColCount=10};
    enum { Horiznal,Vertical};

    explicit Panel(QWidget* parent,int type = Vertical);
    ~Panel();

    void setRowColLimit( int rl,int cl)
    {
        row_limit = rl;
        col_limit = cl;
    }
    //设置图标边距
    void setMargins(int left,int top, int right,int bottom);
    /**
     * @brief addApp
     * 添加应用程序
     * @param title
     * @param path
     */
    void addApp(QString title,QString path);
    void addApp(QString title,QPixmap &pix);

    /**
     * @brief addWidget
     * 添加控件
     *
     * @param wid
     */
    void addWidget(QWidget *wid);


    void setMenu(QMenu *menu);


    void SetupUI();

    void createMenu();


    void contextMenuEvent(QContextMenuEvent *evt);
    void keyPressEvent(QKeyEvent *evt);

    void paintEvent(QPaintEvent *evt);

signals:

public slots:
    void action_add_app();
    void action_prop();
    void showDesk();
private:
    QMenu       *m_menu;
    QGridLayout *m_grid_lay;
    QMap<QString, QString>  m_app_map;
    QList<AppConfig>        m_app_list;

    QPoint      m_move_point;
    bool        m_press;

    int         m_row;
    int         m_col;
    int         row_limit;
    int         col_limit;
    int         lay_type;

};

#endif // PANEL_H
