#ifndef ASCHREDIALOG_H
#define ASCHREDIALOG_H

#include <QDialog>

namespace Ui {
class ASChReDialog;
}

class ASChReDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ASChReDialog(QWidget *parent = 0);
    ~ASChReDialog();
    void paintEvent(QPaintEvent*);
    void showL();

public slots:
    void submit();

private:
    Ui::ASChReDialog *ui;
    void closeEvent(QCloseEvent * event);
};

#endif // ASCHREDIALOG_H
