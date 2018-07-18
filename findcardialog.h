#ifndef FINDCARDIALOG_H
#define FINDCARDIALOG_H

#include <QDialog>

namespace Ui {
class FindCarDialog;
}

class FindCarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindCarDialog(QWidget *parent = 0);
    ~FindCarDialog();
    void paintEvent(QPaintEvent*);
    void showCar();

public slots:
    void getItem(int row, int col);
    void search();

private:
    Ui::FindCarDialog *ui;
};

#endif // FINDCARDIALOG_H
