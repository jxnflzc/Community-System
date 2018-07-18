#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"

#include <QString>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QPainter>
#include <QtSql>
#include <QDesktopServices>
#include <QPainter>
#include <QTranslator>

bool language_en;
QString userName;
QString uid;
QString status;
int power;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    loginConn();
    loadConfig();
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

void LoginDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::login(){
    if(ui->edtUid->text().trimmed() == "" || ui->edtPassword->text().trimmed() == ""){
        //内容没填完整提示
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("内容请填完整！"));
    }else{
        //从数据库中选出数据
        QSqlQuery query;
        query.exec(QString("SELECT uid, password FROM owner WHERE uid = '%1' "
                   "union all "
                   "SELECT uid, password FROM staff WHERE uid = '%1' ").arg(ui->edtUid->text().trimmed()));
        if(query.next()){
            //判断用户名和密码是否正确，如果错误则弹出警告对话框
            bool rightLogin = false;
            if(ui->edtUid->text().trimmed() == query.value("uid").toString() &&
                   ui->edtPassword->text().trimmed() == query.value("password").toString()){
                rightLogin = true;
                uid = ui->edtUid->text().trimmed();
                query.exec(QString("SELECT userName, status, power FROM owner WHERE uid='%1' "
                                   "union all "
                                   "SELECT userName, status, power FROM staff WHERE uid='%1'").arg(uid));
                query.next();

                userName = query.value("userName").toString().trimmed();
                status = query.value("status").toString().trimmed();
                power = query.value("power").toInt();
                MainWindow *w = new MainWindow;
                w->show();
                saveConfig();
                accept();
            }

            if(!rightLogin){    //登录失败
                QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("用户名或密码错误!"), QMessageBox::Yes);
                ui->edtUid->clear();
                ui->edtPassword->clear();
                ui->edtUid->setFocus();
            }
        }else{
            QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("用户名不存在！"), QMessageBox::Yes);
        }
    }
}

void LoginDialog::loginConn(){
    connect(ui->btnLogin,SIGNAL(clicked(bool)),this,SLOT(login()));
}

void LoginDialog::on_checkRem_stateChanged(int arg1){
    if(ui->checkRem->isChecked()){
        rememberPassword = true;
    }else{
        rememberPassword = false;
    }
}

void LoginDialog::saveConfig(){ //保存设定
        QSettings cfg("config.ini",QSettings::IniFormat);
        remUid= ui->edtUid->text();
        remPassword= ui->edtPassword->text();
        cfg.setValue("RememberPsd/Uid", remUid);
        cfg.setValue("RememberPsd/Password", remPassword);
        cfg.setValue("RememberPsd/Remember",rememberPassword);
        cfg.sync();

}

void LoginDialog::loadConfig(){ //读取设定
    QSettings cfg("config.ini",QSettings::IniFormat);
    if(cfg.value("RememberPsd/Remember").toBool()){
        ui->edtUid->setText(cfg.value("RememberPsd/Uid").toString());
        ui->edtPassword->setText(cfg.value("RememberPsd/Password").toString());
        ui->checkRem->setChecked(true);
    }
    if(cfg.value("Language/Language").toString().trimmed() == "en"){
        language_en = true;
    }else{
        language_en = false;
    }
}
