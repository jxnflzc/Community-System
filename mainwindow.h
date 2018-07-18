#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "addpersondialog.h"
#include "findstaffdialog.h"
#include "leavedialog.h"
#include "agreevacdialog.h"
#include "addownerdialog.h"
#include "findownerdialog.h"
#include "addcardialog.h"
#include "findcardialog.h"
#include "applicatecardialog.h"
#include "rentcardialog.h"
#include "needrepairdialog.h"
#include "repairscheduledialog.h"
#include "helpdialog.h"
#include "attendstatedialog.h"
#include "setupdialog.h"
#include "chpassworddialog.h"

#include <QMainWindow>
#include <QMenu>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showL();
    void btnShow();
    void paintEvent(QPaintEvent*);
    void conn();

public slots:
    void cancel();
    void actAddPerson();
    void actFindStaff();
    void actVacation();
    void actPassVaca();
    void actCancelVaca();
    void actAddOwner();
    void actFindOwner();
    void actAddCar();
    void actFindCar();
    void actAppCar();
    void actRentCar();
    void actNeedRepair();
    void actReSchedule();
    void actAttend();
    void actInit();
    void actHelp();
    void actAttendState();
    void actSetup();
    void changeMainUi();
    void actChPassword();

private:
    Ui::MainWindow *ui;
    void changeMenu();
    void addAdminLayout();

    QLabel *statusLabel = new QLabel(this);
};

#endif // MAINWINDOW_H
