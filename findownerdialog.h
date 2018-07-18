#ifndef FINDOWNERDIALOG_H
#define FINDOWNERDIALOG_H

#include <QDialog>

namespace Ui {
class FindOwnerDialog;
}

class FindOwnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindOwnerDialog(QWidget *parent = 0);
    ~FindOwnerDialog();
    void paintEvent(QPaintEvent*);
    void showOwner();

public slots:
    void getItem(int row, int col);
    void search();

private:
    Ui::FindOwnerDialog *ui;
};

#endif // FINDOWNERDIALOG_H
