#ifndef ADDOWNERDIALOG_H
#define ADDOWNERDIALOG_H

#include <QDialog>

namespace Ui {
class AddOwnerDialog;
}

class AddOwnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOwnerDialog(QWidget *parent = 0);
    ~AddOwnerDialog();
    void paintEvent(QPaintEvent*);
    void show();

public slots:
    void submit();
    void reset();
    void owDelete();

private:
    Ui::AddOwnerDialog *ui;
    void closeEvent( QCloseEvent * event);
};

#endif // ADDOWNERDIALOG_H
