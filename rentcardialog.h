#ifndef RENTCARDIALOG_H
#define RENTCARDIALOG_H

#include <QDialog>

namespace Ui {
class RentCarDialog;
}

class RentCarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RentCarDialog(QWidget *parent = 0);
    ~RentCarDialog();
    void paintEvent(QPaintEvent*);
    void showApp();

public slots:
    void getItem(int row, int col);
    void search();

private:
    Ui::RentCarDialog *ui;
};

#endif // RENTCARDIALOG_H
