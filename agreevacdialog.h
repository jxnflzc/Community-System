#ifndef AGREEVACDIALOG_H
#define AGREEVACDIALOG_H

#include <QDialog>

namespace Ui {
class AgreeVacDialog;
}

class AgreeVacDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AgreeVacDialog(QWidget *parent = 0);
    ~AgreeVacDialog();
    void paintEvent(QPaintEvent*);
    void showWants();

public slots:
    void getItem(int row, int col);

private:
    Ui::AgreeVacDialog *ui;
};

#endif // AGREEVACDIALOG_H
