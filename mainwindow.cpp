#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTranslator>
#include <QString>
#include <QAction>
#include <QPainter>
#include <QMenu>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QTranslator>

extern bool language_en;

extern QString userName;
extern QString uid;
extern QString status;
extern int power;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage(QObject::tr("%1，欢迎登录。").arg(userName), 5000);
    btnShow();
    showL();
    changeMenu();
    conn();
    QTranslator translator;
    if(language_en){
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }else{
        qApp->removeTranslator(&translator);
        ui->retranslateUi(this);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void MainWindow::conn(){
    connect(ui->btnAddCar,SIGNAL(clicked(bool)),this,SLOT(actAddCar()));
    connect(ui->btnAddOwner,SIGNAL(clicked(bool)),this,SLOT(actAddOwner()));
    connect(ui->btnAddStaff,SIGNAL(clicked(bool)),this,SLOT(actAddPerson()));
    connect(ui->btnAppCar,SIGNAL(clicked(bool)),this,SLOT(actAppCar()));
    connect(ui->btnAttend,SIGNAL(clicked(bool)),this,SLOT(actAttend()));
    connect(ui->btnChangeOwner,SIGNAL(clicked(bool)),this,SLOT(actFindOwner()));
    connect(ui->btnChangeStaff,SIGNAL(clicked(bool)),this,SLOT(actFindStaff()));
    connect(ui->btnPassCar,SIGNAL(clicked(bool)),this,SLOT(actRentCar()));
    connect(ui->btnPassVacation,SIGNAL(clicked(bool)),this,SLOT(actPassVaca()));
    connect(ui->btnRepair,SIGNAL(clicked(bool)),this,SLOT(actNeedRepair()));
    connect(ui->btnReSchedule,SIGNAL(clicked(bool)),this,SLOT(actReSchedule()));
}

void MainWindow::showL(){
    QSqlQuery query;
    query.exec(QString("SELECT * FROM vacation WHERE finish = false AND agree = true AND uid = '%1'").arg(uid));
    if(query.next() != NULL){
        statusLabel->setText(QObject::tr("当前用户：%1  %2  %3  %4").arg(uid).arg(status).arg(userName).arg("休假中"));
    }else{
        statusLabel->setText(QObject::tr("当前用户：%1  %2  %3").arg(uid).arg(status).arg(userName));
    }
    ui->statusBar->addPermanentWidget(statusLabel);
}

void MainWindow::btnShow(){
    QIcon icoAddStaff(":/IconPic/pic/addStaff.png");
    ui->btnAddStaff->setMinimumSize(64,64);
    ui->btnAddStaff->setMaximumSize(64,64);
    ui->btnAddStaff->setText("");
    ui->btnAddStaff->setIcon(icoAddStaff);
    ui->btnAddStaff->setIconSize(QSize(64,64));
    ui->btnAddStaff->setFlat(true);
    QIcon icoChangeStaff(":/IconPic/pic/changeStaff.png");
    ui->btnChangeStaff->setMinimumSize(64,64);
    ui->btnChangeStaff->setMaximumSize(64,64);
    ui->btnChangeStaff->setText("");
    ui->btnChangeStaff->setIcon(icoChangeStaff);
    ui->btnChangeStaff->setIconSize(QSize(64,64));
    ui->btnChangeStaff->setFlat(true);
    QIcon icoAttend(":/IconPic/pic/staffAttend.png");
    ui->btnAttend->setMinimumSize(64,64);
    ui->btnAttend->setMaximumSize(64,64);
    ui->btnAttend->setText("");
    ui->btnAttend->setIcon(icoAttend);
    ui->btnAttend->setIconSize(QSize(64,64));
    ui->btnAttend->setFlat(true);
    QIcon icoPassCar(":/IconPic/pic/passCar.png");
    ui->btnPassCar->setMinimumSize(64,64);
    ui->btnPassCar->setMaximumSize(64,64);
    ui->btnPassCar->setText("");
    ui->btnPassCar->setIcon(icoPassCar);
    ui->btnPassCar->setIconSize(QSize(64,64));
    ui->btnPassCar->setFlat(true);
    QIcon icoPassVacation(":/IconPic/pic/passVacation.png");
    ui->btnPassVacation->setMinimumSize(64,64);
    ui->btnPassVacation->setMaximumSize(64,64);
    ui->btnPassVacation->setText("");
    ui->btnPassVacation->setIcon(icoPassVacation);
    ui->btnPassVacation->setIconSize(QSize(64,64));
    ui->btnPassVacation->setFlat(true);
    QIcon icoReSchedule(":/IconPic/pic/reSchedule.png");
    ui->btnReSchedule->setMinimumSize(64,64);
    ui->btnReSchedule->setMaximumSize(64,64);
    ui->btnReSchedule->setText("");
    ui->btnReSchedule->setIcon(icoReSchedule);
    ui->btnReSchedule->setIconSize(QSize(64,64));
    ui->btnReSchedule->setFlat(true);
    QIcon icoRepair(":/IconPic/pic/repair.png");
    ui->btnRepair->setMinimumSize(64,64);
    ui->btnRepair->setMaximumSize(64,64);
    ui->btnRepair->setText("");
    ui->btnRepair->setIcon(icoRepair);
    ui->btnRepair->setIconSize(QSize(64,64));
    ui->btnRepair->setFlat(true);
    QIcon icoAddOwner(":/IconPic/pic/addOwner.png");
    ui->btnAddOwner->setMinimumSize(64,64);
    ui->btnAddOwner->setMaximumSize(64,64);
    ui->btnAddOwner->setText("");
    ui->btnAddOwner->setIcon(icoAddOwner);
    ui->btnAddOwner->setIconSize(QSize(64,64));
    ui->btnAddOwner->setFlat(true);
    QIcon icoChangeOwner(":/IconPic/pic/changeOwner.png");
    ui->btnChangeOwner->setMinimumSize(64,64);
    ui->btnChangeOwner->setMaximumSize(64,64);
    ui->btnChangeOwner->setText("");
    ui->btnChangeOwner->setIcon(icoChangeOwner);
    ui->btnChangeOwner->setIconSize(QSize(64,64));
    ui->btnChangeOwner->setFlat(true);
    QIcon icoAppCar(":/IconPic/pic/appCar.png");
    ui->btnAppCar->setMinimumSize(64,64);
    ui->btnAppCar->setMaximumSize(64,64);
    ui->btnAppCar->setText("");
    ui->btnAppCar->setIcon(icoAppCar);
    ui->btnAppCar->setIconSize(QSize(64,64));
    ui->btnAppCar->setFlat(true);
    QIcon icoAddCar(":/IconPic/pic/addCar.png");
    ui->btnAddCar->setMinimumSize(64,64);
    ui->btnAddCar->setMaximumSize(64,64);
    ui->btnAddCar->setText("");
    ui->btnAddCar->setIcon(icoAddCar);
    ui->btnAddCar->setIconSize(QSize(64,64));
    ui->btnAddCar->setFlat(true);
}

void MainWindow::changeMenu(){  //根据用户权限显示菜单
    if(power != 3){ //非管理员
        ui->btnAddOwner->setVisible(false);
        ui->txtAddOwner->setVisible(false);
        ui->btnAddStaff->setVisible(false);
        ui->txtAddStaff->setVisible(false);
        ui->btnPassVacation->setVisible(false);
        ui->txtPassVacation->setVisible(false);
        ui->btnPassCar->setVisible(false);
        ui->txtPassCar->setVisible(false);
        ui->btnAddCar->setVisible(false);
        ui->txtAddCar->setVisible(false);
        ui->btnChangeStaff->setVisible(false);
        ui->txtChangeStaff->setVisible(false);
        ui->action_11->setVisible(false);
        ui->action_23->setVisible(false);
    }
    if(power != 1){ //非业主
        ui->action_10->setVisible(false);
        ui->action_12->setVisible(false);
        ui->btnRepair->setVisible(false);
        ui->btnAppCar->setVisible(false);
        ui->txtRepair->setVisible(false);
        ui->txtAppCar->setVisible(false);
    }

    if(power == 1){ //业主用户
        ui->menuPerson->menuAction()->setVisible(false);
        ui->menuOwner->menuAction()->setVisible(false);
        ui->btnAttend->setVisible(false);
        ui->btnChangeOwner->setVisible(false);
        ui->action_7->setVisible(false);
        ui->txtAttend->setVisible(false);
        ui->txtChangeOwner->setVisible(false);
    }else if(power == 2){   //员工用户
        ui->action_4->setVisible(false);
        ui->menu->menuAction()->setVisible(false);
        ui->action_18->setVisible(false);
        ui->action_19->setVisible(false);
        ui->action_6->setVisible(false);
    }
}

void MainWindow::cancel(){  //注销当前账户
    close();
    LoginDialog loginDlg;
    loginDlg.exec();

}

void MainWindow::actAddPerson(){    //添加员工
    AddPersonDialog apDlg;
    apDlg.exec();
}

void MainWindow::actFindStaff(){    //查询员工
    FindStaffDialog fsDlg;
    fsDlg.exec();
}

void MainWindow::actVacation(){ //请假
    LeaveDialog lDlg;
    lDlg.exec();
}

void MainWindow::actPassVaca(){ //批假
    AgreeVacDialog avDlg;
    avDlg.exec();
}

void MainWindow::actCancelVaca(){   //销假
    QSqlQuery query;
    query.exec(QString("SELECT vacation FROM staff WHERE uid = '%1'").arg(uid));
    query.next();
    if(query.value("vacation").toBool()){
        int res = QMessageBox::question(this,"询问", "确定销假吗？",QMessageBox::Yes,QMessageBox::No);
        if(res == QMessageBox::Yes){
            query.prepare("UPDATE staff SET vacation = false "
                          "WHERE uid = ?");
            query.addBindValue(uid);
            query.exec();

            query.prepare("UPDATE vacation SET finish = true "
                          "WHERE finish = false AND uid = ?");
            query.addBindValue(uid);
            query.exec();
            showL();

            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("销假成功！"));
        }
    }else{
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("你没有请假！"));
    }
}

void MainWindow::actAddOwner(){ //添加业主
    AddOwnerDialog aoDlg;
    aoDlg.exec();
}

void MainWindow::actFindOwner(){    //业主查询修改
    FindOwnerDialog foDlg;
    foDlg.exec();
}

void MainWindow::actAddCar(){   //添加车位
    AddCarDialog acDlg;
    acDlg.exec();
}

void MainWindow::actFindCar(){  //查询车位
    FindCarDialog fcDlg;
    fcDlg.exec();
}

void MainWindow::actAppCar(){   //申请车位
    ApplicateCarDialog appcDlg;
    appcDlg.exec();
}

void MainWindow::actRentCar(){  //车位出租
    RentCarDialog rcDlg;
    rcDlg.exec();
}

void MainWindow::actNeedRepair(){   //申请维修
    NeedRepairDialog nrDlg;
    nrDlg.exec();
}

void MainWindow::actReSchedule(){   //维修进度
    RepairScheduleDialog rsDlg;
    rsDlg.exec();
}

void MainWindow::actAttend(){   //出勤登记
    QSqlQuery query;
    query.exec(QString("SELECT attend FROM staff WHERE uid = '%1'").arg(uid));
    query.next();

    if(query.value("attend").toBool()){
        QMessageBox::information(this, QObject::tr("抱歉"), QObject::tr("您今天已出勤，请勿重复登记！"));
    }else{
        query.exec(QString("UPDATE staff SET attend = true WHERE uid = '%1'").arg(uid));
        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("登记成功！"));
    }
}

void MainWindow::actInit(){ //系统初始化
    int res = QMessageBox::information(this, QObject::tr("询问"), QObject::tr("确定要初始化吗？"), QMessageBox::Yes, QMessageBox::No);
    if(res == QMessageBox::Yes){
        QSettings cfg("config.ini",QSettings::IniFormat);
        cfg.setValue("RememberPsd/Uid", "");
        cfg.setValue("RememberPsd/Password", "");
        cfg.setValue("RememberPsd/Remember",false);
        cfg.setValue("Language/Language","ch");
        cfg.sync();
        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("初始化成功！"));
    }
}

void MainWindow::actHelp(){ //帮助
    HelpDialog sDlg;
    sDlg.exec();
}

void MainWindow::actAttendState(){  //出勤状况
    AttendStateDialog asDlg;
    asDlg.exec();
}

void MainWindow::actSetup(){    //设置
    SetupDialog sDlg;
    connect(&sDlg, SIGNAL(changeUi()), this, SLOT(changeMainUi()));
    sDlg.exec();
}

void MainWindow::changeMainUi(){
    QTranslator translator;
    if(language_en){
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }else{
        qApp->removeTranslator(&translator);
        ui->retranslateUi(this);
    }
}

void MainWindow::actChPassword(){  //修改密码
    ChPasswordDialog cpDlg;
    cpDlg.exec();
}
