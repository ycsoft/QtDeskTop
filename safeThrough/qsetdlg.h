#ifndef QSETDLG_H
#define QSETDLG_H

#include <QDialog>

namespace Ui {
class QSetDlg;
}

class QSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSetDlg(QWidget *parent = 0);
    ~QSetDlg();

public slots:
    void onApplyClick();
    void onCancelClick();
    void onUpdateClick();
    void	textEdited ( const QString & text );

private:
    Ui::QSetDlg *ui;
};

#endif // QSETDLG_H
