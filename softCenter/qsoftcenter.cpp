#include "qsoftcenter.h"

#include <QHBoxLayout>

QSoftCenter::QSoftCenter(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void QSoftCenter::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    m_web = new QHFWebView(this);
    m_web->load(QUrl("html/softCenter.html"));
    lay->addWidget(m_web);
    resize(600,400);
}
