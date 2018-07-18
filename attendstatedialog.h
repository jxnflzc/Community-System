#ifndef ATTENDSTATEDIALOG_H
#define ATTENDSTATEDIALOG_H

#include <QDialog>

namespace Ui {
class AttendStateDialog;
}

class AttendStateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AttendStateDialog(QWidget *parent = 0);
    ~AttendStateDialog();
    void show();
    void paintEvent(QPaintEvent*);

public slots:
    void getItem(int row, int col);
    void search();

private:
    Ui::AttendStateDialog *ui;
};

#endif // ATTENDSTATEDIALOG_H
