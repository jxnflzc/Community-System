#include "applicatecardialog.h"
#include "ui_applicatecardialog.h"

#include <QtSql>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QTranslator>

extern bool language_en;

extern QString uid;
QString CarId;

ApplicateCarDialog::ApplicateCarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicateCarDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showCar();
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

ApplicateCarDialog::~ApplicateCarDialog()
{
    delete ui;
}

void ApplicateCarDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void ApplicateCarDialog::showCar(){
    QSqlQuery query;
    query.exec("SELECT uid, ownerUId, isRent FROM car "
               "WHERE ownerUid = '' And isRent = true");
    while(query.next()){
        ui->boxCar->addItem(query.value("uid").toString());
    }
}

void ApplicateCarDialog::applicate(){
    QSqlQuery query;
    query.exec(QString("SELECT wantCar FROM owner WHERE uid = '%1'").arg(uid));
    query.next();
    if(query.value("wantCar").toString() != ""){
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("您已经申请过车位！"));
    }else{
        int res = QMessageBox::information(this, QObject::tr("请确认"), QObject::tr("是否要申请这个车位？"), QMessageBox::Yes, QMessageBox::No);
        if(res == QMessageBox::Yes){
            query.prepare("UPDATE owner SET wantCar = ? "
                          "WHERE uid = ?");
            query.addBindValue(ui->boxCar->currentText().trimmed());
            query.addBindValue(uid);
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("申请成功！"));;
            close();
        }
    }
}

void ApplicateCarDialog::getPrice(QString text){
    QSqlQuery query;
    query.exec(QString("SELECT price FROM car WHERE uid = '%1'").arg(text));
    query.next();
    ui->txtPrice->setText(query.value("price").toString());
}
