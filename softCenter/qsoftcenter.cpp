#include "qsoftcenter.h"

#include <QHBoxLayout>

QSoftCenter::QSoftCenter(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void QSoftCenter::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    m_web = new QHFWebView(this);
    m_web->load(QUrl("html/softCenter.html"));
    lay->addWidget(m_web);
    resize(600,400);
}
