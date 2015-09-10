#ifndef CONFIRMDLG_H
#define CONFIRMDLG_H

#include "framelesswin2.h"

class ConfirmDlg : public FramelessWin2
{
    Q_OBJECT
public:
    explicit ConfirmDlg(QWidget *parent = 0,QString info = "");
    ~ConfirmDlg();

    void    Init();

signals:

public slots:

private:
    QString         m_info;

};

#endif // CONFIRMDLG_H
