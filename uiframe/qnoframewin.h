#ifndef QNOFRAMEWIN_H
#define QNOFRAMEWIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>

class QNoFrameWin : public QWidget
{
    Q_OBJECT
public:
    explicit QNoFrameWin(QWidget *parent = 0);
    ~QNoFrameWin(){}

    QGridLayout*    getLayout() const
    {
        return m_gridLay;
    }
    QWidget*        getCenterPanel() const
    {
        return m_centerpanel;
    }
    /**
     * @brief setWindowTitle
     * 设置窗体的标题
     */
    void setWindowTitle(const QString &);
    /**
     * @brief setTitleStyle
     * 设置标题的样式
     */
    void setTitleStyle(const  QString &);
protected:
    //重载标准组件的鼠标事件
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    void initUI();


    QWidget         *m_centerpanel;
    QLabel          *m_lbtitle;
    QPoint          m_pressPoint;
    QGridLayout     *m_gridLay;
    QHBoxLayout     *m_hlay;
    bool            m_isPressed;
signals:

public slots:
};

#endif // QNOFRAMEWIN_H
