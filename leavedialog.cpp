#include "leavedialog.h"
#include "ui_leavedialog.h"

#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QTranslator>

extern bool language_en;

extern QString uid;
extern QString userName;

LeaveDialog::LeaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaveDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

LeaveDialog::~LeaveDialog()
{
    delete ui;
}

void LeaveDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void LeaveDialog::submit(){
    QSqlQuery query;
    query.exec(QString("SELECT vacation FROM staff WHERE uid = '%1'").arg(uid));
    query.next();
    int vacation = query.value("vacation").toInt();
    if(!vacation){
        query.prepare("UPDATE staff SET vacation = ? "
                      "WHERE uid = ?");
        query.addBindValue(1);
        query.addBindValue(uid);
        query.exec();

        query.prepare("INSERT INTO vacation(uid, userName, kind, reason) "
                      "VALUE(:uid, :userName, :kind, :reason)");
        query.bindValue(":uid", uid);
        query.bindValue(":userName", userName);
        query.bindValue(":kind", ui->boxKind->currentText().trimmed());
        query.bindValue(":reason", ui->edtReason->toPlainText().trimmed());
        query.exec();
        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("请假成功！"));
        close();
    }else{
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("您尚未销假！"));
    }
}
