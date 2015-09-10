#ifndef QDOWNLOADPROGRESS_H
#define QDOWNLOADPROGRESS_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QTime>


class QDownloadProgress : public QWidget
{
    Q_OBJECT
public:
    explicit QDownloadProgress(QWidget *parent = 0);
    ~QDownloadProgress() {}


signals:

public slots:
    void            progress(uint done,uint total);
private:
    void            setupUI();

    QProgressBar    *m_progress;
    QLabel          *m_label;
    QTime           *m_time;

};

#endif // QDOWNLOADPROGRESS_H
