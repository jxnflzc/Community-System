#ifndef REPAIRSCHEDULEDIALOG_H
#define REPAIRSCHEDULEDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QAction>

namespace Ui {
class RepairScheduleDialog;
}

class RepairScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RepairScheduleDialog(QWidget *parent = 0);
    ~RepairScheduleDialog();
    void paintEvent(QPaintEvent*);
    void showAS();
    void showOw();

public slots:
    void getItem(int,int);

private:
    Ui::RepairScheduleDialog *ui;
};

#endif // REPAIRSCHEDULEDIALOG_H
