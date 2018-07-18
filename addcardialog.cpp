#include "addcardialog.h"
#include "ui_addcardialog.h"
#include "findcardialog.h"

#include <QMessageBox>
#include <QtSql>
#include <QPainter>
#include <QIntValidator>
#include <QString>
#include <QTranslator>

extern bool language_en;
extern QString changeCarUid;
extern bool changeCar;

AddCarDialog::AddCarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCarDialog)
{
    ui->setupUi(this);
    ui->edtCarOwner->setVisible(false);
    ui->txtCarOwner->setVisible(false);
    this->setFixedSize(this->width(), this->height());
    if(changeCar){
        this->setWindowTitle(QObject::tr("修改车位信息"));
        ui->btnSubmit->setText(QObject::tr("修改"));
        QSqlQuery query;
        query.exec(QString("SELECT * FROM car WHERE uid = '%1'").arg(changeCarUid));
        query.next();
        ui->edtCarUid->setText(changeCarUid);
        ui->edtCarOwner->setText(query.value("ownerUid").toString().trimmed());
        ui->boxRent->setChecked(query.value("isRent").toBool());
        ui->edtPrice->setText(query.value("price").toString().trimmed());
        ui->edtCarOwner->setVisible(true);
        ui->txtCarOwner->setVisible(true);
    }
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
    ui->edtPrice->setValidator(new QIntValidator(0, 100000.00, this));
}

AddCarDialog::~AddCarDialog()
{
    delete ui;
}

void AddCarDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void AddCarDialog::reset(){ //重置
    ui->edtCarUid->clear();
    ui->edtCarOwner->clear();
    ui->boxRent->setChecked(false);
    ui->edtCarUid->setFocus();
}

void AddCarDialog::submit(){    //提交
    QSqlQuery query;
    if(ui->edtCarUid->text().trimmed() == "" || ui->edtPrice->text().trimmed() == ""){
        //内容没填完整提示
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("内容请填完整！"));
    }else{
        QString carId = ui->edtCarUid->text().trimmed();
        query.exec(QString("SELECT * FROM owner WHERE uid = '%1'").arg(carId));//查询车位是否存在
        if(query.next() && !changeCar){
            QMessageBox::warning(this, QObject::tr("失败"), QObject::tr("该车位已经存在！"));
        }else if(!changeCar){
            //车位不存在且内容填完整，将数据插入数据库里
            query.prepare("INSERT INTO car(uid, isRent, price) "
                          "VALUE(:uid, :isRent, :price)");
            query.bindValue(":uid", ui->edtCarUid->text().trimmed());
            query.bindValue(":isRent", ui->boxRent->isChecked());
            query.bindValue(":price", ui->edtPrice->text().toDouble());
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("添加成功！"));
        }else{
            query.prepare("UPDATE car SET uid = ?, ownerUid = ?, isRent = ?, price = ? "
                          "WHERE uid = ?");
            query.addBindValue(ui->edtCarUid->text().trimmed());
            query.addBindValue(ui->edtCarOwner->text().trimmed());
            query.addBindValue(ui->boxRent->isChecked());
            query.addBindValue(ui->edtPrice->text().toDouble());
            query.addBindValue(ui->edtCarUid->text().trimmed());
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改成功！"));
            changeCar = false;
            FindCarDialog fcDlg;
            close();
            fcDlg.exec();
        }
    }
    close();
}

void AddCarDialog::closeEvent(QCloseEvent * event){
    if(changeCar){
        FindCarDialog fcDlg;
        this->accept();
        fcDlg.exec();
    }
    changeCar = false;
}
