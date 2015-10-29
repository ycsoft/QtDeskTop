#include "qtipswidget.h"
#include "maindialog.h"

#include <QVBoxLayout>
#include <QWebFrame>

QTipsWidget::QTipsWidget(QWidget *parent) : QDialog(parent)
{
    initUI();
    resize(600,400);
    setWindowFlags( Qt::FramelessWindowHint);

}

void QTipsWidget::initUI()
{
    QWidget *center = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(center);
    m_web = new QHFWebView(center);
    vlay ->setMargin(0);
    vlay->addWidget(m_web);
    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->setMargin(0);
    mainLay->addWidget(center);
    m_web->load(QUrl("html/tips.html"));
}
void QTipsWidget::execJS(const QString &js)
{
    m_web->page()->mainFrame()->evaluateJavaScript(js);
}
