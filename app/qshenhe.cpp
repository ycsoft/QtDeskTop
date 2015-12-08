#include "qshenhe.h"
#include "utils/qapputils.h"
#include <QVBoxLayout>

QShenhe::QShenhe(QWidget *parent) : QDialog(parent)
{
    initUI();
    int wid,hei;
    QAppUtils::ref().getScreenSize(wid,hei);
    resize(wid,hei- 100);
}

QShenhe::~QShenhe()
{

}
void QShenhe::initUI()
{
    QWidget *center = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(center);
    QVBoxLayout *mainLay = new QVBoxLayout(this);

    vlay->setMargin(0);
    mainLay->setMargin(0);

    m_web = new QHFWebView(this);
    vlay->addWidget(m_web);
    mainLay->addWidget(center);

    m_web->load(QUrl("html/shenhe.html"));
}
