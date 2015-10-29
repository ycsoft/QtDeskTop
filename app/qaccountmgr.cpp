#include "qaccountmgr.h"

#include <QVBoxLayout>

QAccountMgr::QAccountMgr(QWidget *parent) : QDialog(parent)
{
    initUI();
    resize(800,600);
    setWindowTitle(QString::fromLocal8Bit("账务系统"));
}

void QAccountMgr::initUI()
{
    QWidget *center = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(center);
    QVBoxLayout *mainLay = new QVBoxLayout(this);

    vlay->setMargin(0);
    mainLay->setMargin(0);

    m_web = new QHFWebView(this);
    vlay->addWidget(m_web);
    mainLay->addWidget(center);

    m_web->load(QUrl("html/examine.html"));
}
