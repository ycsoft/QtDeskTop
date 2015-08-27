#ifndef QSCREENSHORT_H
#define QSCREENSHORT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class QScreenShort : public QWidget
{
    Q_OBJECT
public:
    explicit QScreenShort(QWidget *parent = 0);
    ~QScreenShort(){}
    //设置要显示的窗口部件
    void setWidget(QWidget*);
    /**
     * @brief setWindowTitle
     * 设置窗体标题
     * @param title:窗体标题
     */
    void setWindowTitle(const QString &title);

protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent*);
    void paintEvent(QPaintEvent *);
private:
    void initUI();
    //标题
    QLabel          *m_lbtitle;
    QWidget         *m_center;
    QHBoxLayout     *m_hlay;

    bool            m_pressed;
    bool            m_entered;
signals:
    void            screenClicked(QString);
public slots:
};

#endif // QSCREENSHORT_H
