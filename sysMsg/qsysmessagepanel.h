#ifndef QSYSMESSAGEPANEL_H
#define QSYSMESSAGEPANEL_H

#include <QWidget>
#include <QGridLayout>

#include "uiframe/qnoframewin.h"

class QSysMessagePanel : public QWidget
{
    Q_OBJECT
public:
    explicit QSysMessagePanel(QWidget *parent = 0);
    ~QSysMessagePanel(){}

    QGridLayout *getLayout()
    {
        return m_lay;
    }

    void    addMessage(const QString &from, const QString &msg);
protected:
    void    initUI();
signals:

public slots:

private:
    int     m_currow;
    QGridLayout     *m_lay;
};

#endif // QSYSMESSAGEPANEL_H
