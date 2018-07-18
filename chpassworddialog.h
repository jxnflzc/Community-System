#ifndef CHPASSWORDDIALOG_H
#define CHPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class ChPasswordDialog;
}

class ChPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChPasswordDialog(QWidget *parent = 0);
    ~ChPasswordDialog();
    void paintEvent(QPaintEvent*);

public slots:
    void submit();

private:
    Ui::ChPasswordDialog *ui;
};

#endif // CHPASSWORDDIALOG_H
