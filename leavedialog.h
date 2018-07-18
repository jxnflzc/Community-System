#ifndef LEAVEDIALOG_H
#define LEAVEDIALOG_H

#include <QDialog>

namespace Ui {
class LeaveDialog;
}

class LeaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LeaveDialog(QWidget *parent = 0);
    ~LeaveDialog();
    void paintEvent(QPaintEvent*);

private slots:
    void submit();

private:
    Ui::LeaveDialog *ui;
};

#endif // LEAVEDIALOG_H
