#ifndef OCHREDIALOG_H
#define OCHREDIALOG_H

#include <QDialog>

namespace Ui {
class OChReDialog;
}

class OChReDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OChReDialog(QWidget *parent = 0);
    ~OChReDialog();
    void paintEvent(QPaintEvent*);
    void showL();

public slots:
    void change();
    void submit();

private:
    Ui::OChReDialog *ui;
    void closeEvent(QCloseEvent * event);
};

#endif // OCHREDIALOG_H
