#include "qdownloadprogress.h"
#include "datatypes.h"


#include <QVBoxLayout>
#include <QMessageBox>
#include <QProcess>
#include <QApplication>


QDownloadProgress::QDownloadProgress(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
}


void QDownloadProgress::progress(uint done, uint total)
{

    m_progress->setMaximum(total);
    m_progress->setValue(done);

    float     elapse = (float)m_time->elapsed()/1000.0f;
    float     vol = (float)done/elapse/1024.0f;
    char      buf[128] = {0};

    sprintf(buf,"下载速度:%.1f KB/秒",vol);
    m_label->setText(QString::fromLocal8Bit(buf));
    if ( done >= total)
    {
        //更新完毕，关闭当前应用，执行安装
        QProcess *proc = new QProcess(this);
        proc->start(Installer_Name);
        proc->waitForStarted(2000);
        this->close();
        QApplication::exit(0);
    }
}

void QDownloadProgress::setupUI()
{
    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->setSpacing(10);
    vlay->setMargin(10);
    m_progress = new QProgressBar(this);
    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignHCenter);
    m_time = new QTime();

    vlay->addWidget(m_label);
    vlay->addWidget(m_progress);

    resize(400,70);
    setWindowTitle(QString::fromLocal8Bit("更新进度"));
    m_time->start();
}
