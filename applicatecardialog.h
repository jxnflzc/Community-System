#ifndef APPLICATECARDIALOG_H
#define APPLICATECARDIALOG_H

#include <QDialog>

namespace Ui {
class ApplicateCarDialog;
}

class ApplicateCarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicateCarDialog(QWidget *parent = 0);
    ~ApplicateCarDialog();
    void paintEvent(QPaintEvent*);
    void showCar();

public slots:
    void applicate();
    void getPrice(QString text);

private:
    Ui::ApplicateCarDialog *ui;
};

#endif // APPLICATECARDIALOG_H
