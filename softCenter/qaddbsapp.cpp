#include "qaddbsapp.h"

#include "jsCore/qjscore.h"
#include "maindialog.h"
#include "uiframe/qappiconpanel.h"

#include <QVBoxLayout>
#include <QWebFrame>
#include <QDebug>

QAddBSApp::QAddBSApp(QWidget *parent) : QWidget(parent)
{
    initUI();
    resize(500,430);
    setWindowFlags(Qt::FramelessWindowHint);
    setVisible(false);
}


void QAddBSApp::initUI()
{
    QWidget *center = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(center);
    QVBoxLayout *mainLay = new QVBoxLayout(this);

    vlay->setMargin(0);
    mainLay->setMargin(0);

    m_web = new QHFWebView(center);
    vlay->addWidget(m_web);

    mainLay->addWidget(center);
    m_web->load(QUrl("html/addapp.html"));

    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));
}

void QAddBSApp::addObject()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("BS",this);
}

void QAddBSApp::okClick()
{
    QJSCore *jscore = QJSCore::ref();
    QString bsname = jscore->readValue("bs-name");
    QString url = jscore->readValue("bs-url");

    QAppIconPanel *panel = MainDialog::ref().getAppIconPanel();
    panel->addApp(QPixmap("html/images/ie.png"),bsname,url);
    MainDialog::ref().saveApp(bsname,url);
    hide();
}
