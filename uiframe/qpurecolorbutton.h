#ifndef QPURECOLORBUTTON_H
#define QPURECOLORBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class QPureColorButton : public QWidget
{
    Q_OBJECT
public:
    explicit QPureColorButton(QWidget *parent = 0);
    ~QPureColorButton() {}

    void setColors(const QColor &pres,const QColor &release
                   , const QColor &enter,const QColor &leave);

    void setPressColor( const QColor &c)  { m_pressColor = c;}
    void setReleaseColor(const QColor &c) { m_releaseColor = c;}
    void setEnterColor ( const QColor &c) { m_enterColor = c;}
    void setLeaveColor(const QColor &c)   { m_leaveColor = c;}
    void setButtonText(const QString &txt)
    {
        if (m_lbtitle )
            m_lbtitle->setText(txt);
    }
    void setTextStyle(const QString &st)
    {
        if ( m_lbtitle )
            m_lbtitle->setStyleSheet(st);
    }

    void setIndex(const int &id)            { m_index = id;     }
    int  getIndex() const                   { return m_index;   }

    QString getButtonText()const {;}
signals:
    void clicked();
    void clicked(int);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);
public slots:

private:
    bool    m_pressed;
    bool    m_entered;
    int     m_index;


    QColor  m_currentColor;
    QColor  m_releaseColor;
    QColor  m_enterColor;
    QColor  m_leaveColor;
    QColor  m_pressColor;

    QLabel  *m_lbtitle;
};

#endif // QPURECOLORBUTTON_H
