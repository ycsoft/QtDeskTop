#include "qpoptips.h"
#include <QVBoxLayout>

QPopTips::QPopTips(QWidget *parent) : QDialog(parent)
{
    initUI();
}

QPopTips::~QPopTips()
{

}
void QPopTips::setTips(const QString &usr, const QString &etti, const QString &data)
{

}

void QPopTips::initUI()
{
    QVBoxLayout *vlay = new QVBoxLayout(this);

    m_web = new QHFWebView(this);
    vlay->setContentsMargins(0,0,0,0);
    vlay->addWidget(m_web);
}
