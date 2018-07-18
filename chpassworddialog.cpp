#include "chpassworddialog.h"
#include "ui_chpassworddialog.h"

#include <QtSql>
#include <QString>
#include <QPainter>
#include <QTranslator>
#include <QMessageBox>

extern bool language_en;
extern QString uid;
extern int power;

ChPasswordDialog::ChPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChPasswordDialog)
{
    ui->setupUi(this);
}

ChPasswordDialog::~ChPasswordDialog()
{
    delete ui;
}

void ChPasswordDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void ChPasswordDialog::submit(){
    if(ui->edtOldPsd->text().trimmed() == "" || ui->edtNewPsd->text().trimmed() == ""
            || ui->edtNewPsd_2->text().trimmed() == ""){
        //内容没填完整提示
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("内容请填完整！"));
    }else if(ui->edtNewPsd->text().trimmed() != ui->edtNewPsd_2->text().trimmed()){
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("两次新密码必须一致！"));
    }else{
        QSqlQuery query;
        if(power == 1){
            query.exec(QString("SELECT password FROM owner WHERE uid = '%1'").arg(uid));
            query.next();
            if(query.value("password").toString().trimmed() != ui->edtOldPsd->text().trimmed()){
                QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("原密码填写错误！"));
            }else{
                query.prepare("UPDATE owner SET password = ? WHERE uid = ?");
                query.addBindValue(ui->edtNewPsd->text().trimmed());
                query.addBindValue(uid);
                query.exec();
                QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改密码成功！"));
                accept();
            }
        }else{
            query.exec(QString("SELECT password FROM staff WHERE uid = '%1'").arg(uid));
            query.next();
            if(query.value("password").toString().trimmed() != ui->edtOldPsd->text().trimmed()){
                QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("原密码填写错误！"));
            }else{
                query.prepare("UPDATE staff SET password = ? WHERE uid = ?");
                query.addBindValue(ui->edtNewPsd->text().trimmed());
                query.addBindValue(uid);
                query.exec();
                QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改密码成功！"));
                accept();
            }
        }
    }
}
