#include "setupdialog.h"
#include "ui_setupdialog.h"
#include "mainwindow.h"

#include <QTranslator>
#include <QPainter>
#include <QSettings>
#include <QString>
#include <QMessageBox>

extern bool language_en;

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
    loadConfig();

}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void SetupDialog::saveConfig(){
     QSettings cfg("config.ini",QSettings::IniFormat);
     if(ui->boxEn->isChecked()){
         cfg.setValue("Language/Language", "en");
     }else{
         cfg.setValue("Language/Language", "ch");
     }
     cfg.sync();
}

void SetupDialog::loadConfig(){
     QSettings cfg("config.ini",QSettings::IniFormat);
     if(cfg.value("Language/Language").toString().trimmed() == "en"){
         ui->boxEn->setChecked(true);
         language_en = true;
     }else{
         ui->boxEn->setChecked(false);
         language_en = false;
     }
}

void SetupDialog::save(){
    saveConfig();
    QMessageBox::information(this, QObject::tr("成功"), QObject::tr("保存成功！请重启软件来启用新配置。"));
    loadConfig();
    emit changeUi();
    SetupDialog sDlg;
    accept();
    sDlg.exec();
}

