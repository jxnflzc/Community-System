#ifndef ADDCARDIALOG_H
#define ADDCARDIALOG_H

#include <QDialog>

namespace Ui {
class AddCarDialog;
}

class AddCarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCarDialog(QWidget *parent = 0);
    ~AddCarDialog();
    void paintEvent(QPaintEvent*);

public slots:
    void reset();
    void submit();

private:
    Ui::AddCarDialog *ui;    
    void closeEvent( QCloseEvent * event);
};

#endif // ADDCARDIALOG_H
