#ifndef FINDSTAFFDIALOG_H
#define FINDSTAFFDIALOG_H

#include <QDialog>

namespace Ui {
class FindStaffDialog;
}

class FindStaffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindStaffDialog(QWidget *parent = 0);
    ~FindStaffDialog();
    void paintEvent(QPaintEvent*);
    void showStaff();

public slots:
    void getItem(int row, int col);
    void search();

private:
    Ui::FindStaffDialog *ui;
};

#endif // FINDSTAFFDIALOG_H
