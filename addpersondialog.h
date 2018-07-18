#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = 0);
    ~AddPersonDialog();
    void paintEvent(QPaintEvent*);
    void showL();

public slots:
    void addPerson();
    void reset();
    void stDelete();

private:
    Ui::AddPersonDialog *ui;
    void closeEvent( QCloseEvent * event);
};

#endif // ADDPERSONDIALOG_H
