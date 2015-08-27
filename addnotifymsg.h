#ifndef ADDNOTIFYMSG_H
#define ADDNOTIFYMSG_H

#include <QDialog>

namespace Ui {
class AddNotifyMsg;
}

class AddNotifyMsg : public QDialog
{
    Q_OBJECT

public:
    explicit AddNotifyMsg(QWidget *parent = 0);
    ~AddNotifyMsg();

    QString       getTitle() const
    {
        return m_app;
    }
public slots:
    void click();

private:
    Ui::AddNotifyMsg *ui;

    QString          m_app;
};

#endif // ADDNOTIFYMSG_H
