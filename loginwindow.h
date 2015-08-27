#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QString>
#include <QCryptographicHash>
#include <QByteArray>
#include <QHBoxLayout>
#include <QLineEdit>

#include "skin/shadowdlg.h"
#include "skin/iconbutton.h"
#include "loginwithsafe.h"

#define LOCAL(x)  QString::fromLocal8Bit(x)
class QFileTrans;
namespace Ui {
class Loginwindow;
}

class Loginwindow : public ShadowDlg
{
    Q_OBJECT

public:
    explicit Loginwindow(QWidget *parent = 0);
    ~Loginwindow();

public slots:

    //通过通行证进行登录
    void LoginWithInfo(QString jid,QString pwd);

    void slotloginclick();

private:
    Ui::Loginwindow *ui;

signals:

private:
   //Added BY X.D Yang
   QWidget             *initTopSkin();
   QHBoxLayout         *initMiddle();

   QLineEdit           *m_edit_user;
   QLineEdit           *m_edit_pwd;
   LoginWithSafe       *m_login_safe;
};

#endif // LOGINWINDOW_H
