#include "qhtmltips.h"
#include <QVBoxLayout>

QHtmlTips::QHtmlTips(QWidget *parent) : QWidget(parent)
{
    initUI();
    resize(400,300);
}

void QHtmlTips::initUI()
{
    QVBoxLayout *vlay = new QVBoxLayout(this);
    m_web = new QHFWebView(this);
    m_web->load(QUrl("html/canvas.html"));
    vlay->addWidget(m_web);
}
