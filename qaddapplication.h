#ifndef QADDAPPLICATION_H
#define QADDAPPLICATION_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>

#include "skin/iconbutton.h"
#include "skin/framelesswin.h"



class QAddApplication : public FramelessWin
{
    Q_OBJECT
public:
    explicit QAddApplication(QWidget *parent = 0);


    QString  m_app;
    QString  m_name;

    QPixmap &getPixmap()
    {
        return m_pixmap;
    }

signals:

public slots:
    void    slot_find();
    void    slot_ok();
private:
    void SetupUI();

    QLabel              *m_lb_pic;
    QLineEdit           *m_line_path;
    QLineEdit           *m_line_name;
    IconButton          *m_btn_ok;
    QPixmap             m_pixmap;


};

#endif // QADDAPPLICATION_H
