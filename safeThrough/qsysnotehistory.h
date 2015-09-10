#ifndef QSYSNOTEHISTORY_H
#define QSYSNOTEHISTORY_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>

class QSysNoteHistory : public QWidget
{
    Q_OBJECT
public:
    explicit QSysNoteHistory(QWidget *parent = 0);

signals:

public slots:

private:
    void setupUI();

    QTextEdit       *m_edit;
};

#endif // QSYSNOTEHISTORY_H
