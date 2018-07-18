#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void paintEvent(QPaintEvent*);
    void loginConn();
    QString remUid;
    QString remPassword;
    bool rememberPassword = false;
    void saveConfig();
    void loadConfig();

public slots:
    void login();
    void on_checkRem_stateChanged(int arg1);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
