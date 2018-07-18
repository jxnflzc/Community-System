#ifndef CANCELVACDIALOG_H
#define CANCELVACDIALOG_H

#include <QDialog>

namespace Ui {
class CancelVacDialog;
}

class CancelVacDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CancelVacDialog(QWidget *parent = 0);
    ~CancelVacDialog();

private:
    Ui::CancelVacDialog *ui;
};

#endif // CANCELVACDIALOG_H
