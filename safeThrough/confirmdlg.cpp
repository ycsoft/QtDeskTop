#include <QLabel>
#include <QVBoxLayout>

#include "confirmdlg.h"
#include "iconbutton2.h"

ConfirmDlg::ConfirmDlg(QWidget *parent,QString info) :
    FramelessWin2(parent)
{
    resize(400,350);
    m_info = info;

}

ConfirmDlg::~ConfirmDlg()
{

}

void ConfirmDlg::Init()
{

}
