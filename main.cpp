#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqldatabase.h>
#include <QString>

extern QString userName;
extern QString uid;
extern QString status;
extern int power;

void createDefaultConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("120.78.141.62");
    //db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("community");
    db.setUserName("jxnflzc");
    db.setPassword("990806");

    if (!db.open()) {
        QMessageBox::critical(0, "失败", "不能连接到数据库!", QMessageBox::Cancel);
        return;
    }
}

QSqlDatabase getDefaultConnection() {
    return QSqlDatabase::database();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createDefaultConnection();
    getDefaultConnection();

    MainWindow w;
    LoginDialog loginDlg;
    loginDlg.show();

    return a.exec();
}
