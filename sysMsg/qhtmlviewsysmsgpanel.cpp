#include "qhtmlviewsysmsgpanel.h"

#include "utils/qapputils.h"


#include <QGridLayout>
#include <QDebug>
#include <QWebFrame>
#include <QPropertyAnimation>

QHtmlViewSysMsgPanel::QHtmlViewSysMsgPanel(QWidget *parent) : QWidget(parent)
{
    int wid,hei,taskh;
    QAppUtils::ref().getScreenSize(wid,hei);
    taskh = QAppUtils::ref().getTaskBarHeight();
    initUI();
    resize(400,hei - taskh);
    setWindowFlags(Qt::FramelessWindowHint);
    setVisible(false);
    setAttribute(Qt::WA_TranslucentBackground);
}

QHtmlViewSysMsgPanel::~QHtmlViewSysMsgPanel()
{

}

void QHtmlViewSysMsgPanel::initUI()
{
    QWidget *center = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(center);
    QVBoxLayout *mainLay = new QVBoxLayout(this);
    m_web = new QHFWebView(this);
    vlay->setMargin(0);
    vlay->addWidget(m_web);
    mainLay->setMargin(0);
    mainLay->addWidget(center);
    m_web->load(QUrl("html/sysmsg.html"));
    m_web->setTransparent(true);
    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));
}

void QHtmlViewSysMsgPanel::addMessage(QString title, QString msg)
{

    QString js = tr("addMessage('%1','%2')").arg(title).arg(msg);
    m_web->page()->mainFrame()->evaluateJavaScript(js);
}
void QHtmlViewSysMsgPanel::addObject()
{
    qDebug()<<"Add Object";
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Msg",this);
}

void QHtmlViewSysMsgPanel::anim_Show()
{
    int wid,hei;
    setVisible(true);
    QPropertyAnimation *anim = new QPropertyAnimation(this,"pos");

    QAppUtils::ref().getScreenSize(wid,hei);
    anim->setDuration(500);
    anim->setStartValue(QPoint(wid,0));
    anim->setEndValue(QPoint(wid-width(),0));
    anim->start();
}
void QHtmlViewSysMsgPanel::anim_Hide()
{
    int wid,hei;
    setVisible(true);
    QPropertyAnimation *anim = new QPropertyAnimation(this,"pos");

    QAppUtils::ref().getScreenSize(wid,hei);

    anim->setDuration(500);
    anim->setEndValue(QPoint(wid,0));
    anim->setStartValue(QPoint(wid-width(),0));
    anim->start();
    connect(anim,SIGNAL(finished()),this,SLOT(hide()));
}
