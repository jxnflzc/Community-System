#ifndef NEEDREPAIRDIALOG_H
#define NEEDREPAIRDIALOG_H

#include <QDialog>

namespace Ui {
class NeedRepairDialog;
}

class NeedRepairDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeedRepairDialog(QWidget *parent = 0);
    ~NeedRepairDialog();
    void paintEvent(QPaintEvent*);
    void showL();

public slots:
    void submit();


private:
    Ui::NeedRepairDialog *ui;
};

#endif // NEEDREPAIRDIALOG_H
