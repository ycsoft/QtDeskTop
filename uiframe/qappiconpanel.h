#ifndef QAPPICONPANEL_H
#define QAPPICONPANEL_H

#include <QWidget>

#define ROW_LIMIT   8
#define COL_LIMIT   10

class QAppIconPanel : public QWidget
{
    Q_OBJECT
public:
    explicit QAppIconPanel(QWidget *parent = 0);
    ~QAppIconPanel(){}

    /**
     * @brief addApp
     * 添加应用程序图标
     *
     * @param title
     * @param path
     */
    void     addApp(QPixmap &pix,QString title, QString path);

protected:
    void     paintEvent(QPaintEvent *);
signals:

public slots:

private:
    int     m_screenWidth;
    int     m_screenHight;

    int     m_currow;
    int     m_curcol;
};

#endif // QAPPICONPANEL_H
