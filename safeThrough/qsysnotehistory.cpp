#include "qsysnotehistory.h"

#include <QHBoxLayout>
#include <QFile>

QSysNoteHistory::QSysNoteHistory(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    setWindowTitle(QString::fromLocal8Bit("系统通知"));
}

void QSysNoteHistory::setupUI()
{
    QHBoxLayout *hlay = new QHBoxLayout(this);
    m_edit = new QTextEdit(this);
    m_edit->setEnabled(true);
    hlay->setMargin(0);
    hlay->setSpacing(0);
    hlay->addWidget(m_edit);
    resize(400,500);
    QFile *f = new QFile("note.dat",this);
    if (!f->exists())
        return;
    if (!f->open(QIODevice::ReadOnly))
        return;
    QString txt;
    txt = QString::fromLocal8Bit(f->readAll());
    QFont font = m_edit->font();
    font.setBold(true);
    font.setKerning(true);
    font.setWeight( font.weight() + 2);
    m_edit->setFont(font);
    m_edit->setTextColor(Qt::red);
    m_edit->setText(txt);
    f->close();
}
