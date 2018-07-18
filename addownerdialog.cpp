#include "addownerdialog.h"
#include "ui_addownerdialog.h"
#include "findownerdialog.h"

#include <QMessageBox>
#include <QtSql>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QTranslator>

extern bool language_en;
extern QString changeOwUid;
extern bool changeOwner;

AddOwnerDialog::AddOwnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOwnerDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    show();
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

void AddOwnerDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

AddOwnerDialog::~AddOwnerDialog()
{
    delete ui;
}

void AddOwnerDialog::show(){
    ui->btnDelete->setVisible(false);
    ui->checkCar->setCheckable(false);
    if(changeOwner){
        ui->btnDelete->setVisible(true);
        ui->checkCar->setCheckable(true);
        this->setWindowTitle(QObject::tr("修改业主"));
        ui->btnSubmit->setText(QObject::tr("修改"));
        QSqlQuery query;
        query.exec(QString("SELECT * FROM owner WHERE uid = '%1'").arg(changeOwUid));
        query.next();
        ui->edtOwUid->setText(changeOwUid);
        ui->edtOwName->setText(query.value("userName").toString().trimmed());
        ui->edtOwPassword->setText(query.value("password").toString().trimmed());
        ui->edtTele->setText(query.value("tele").toString().trimmed());
        ui->edtOwHouseId->setText(query.value("houseId").toString().trimmed());
        ui->edtOwHouseArea->setText(query.value("houseArea").toString().trimmed());
        ui->edtCarId->setText(query.value("CarId").toString().trimmed());
        ui->boxCar->addItem(query.value("wantCar").toString().trimmed());
        if(query.value("agCar").toBool()){
            ui->checkCar->setChecked(true);
        }else{
            ui->checkCar->setChecked(false);
        }
    }
}

void AddOwnerDialog::reset(){
    ui->edtOwUid->setText("");
    ui->edtOwName->setText("");
    ui->edtOwPassword->setText("");
    ui->edtOwHouseId->setText("");
    ui->edtOwHouseArea->setText("");
    ui->edtOwUid->setFocus();
}

void AddOwnerDialog::submit(){
    QSqlQuery query;
    if(ui->edtOwUid->text().trimmed() == "" || ui->edtOwName->text().trimmed() == ""
            || ui->edtOwPassword->text().trimmed() == "" || ui->edtOwHouseId->text().trimmed() == ""
            || ui->edtOwHouseArea->text().trimmed() == ""){
        //内容没填完整提示
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("内容请填完整！"));
    }else{
        QString ownerId = ui->edtOwUid->text().trimmed();
        query.exec(QString("SELECT * FROM owner WHERE uid = '%1'").arg(ownerId));//查询登录名是否存在
        if(query.next() && !changeOwner){
            QMessageBox::warning(this, QObject::tr("失败"), QObject::tr("该登录名已经存在！"));
        }else if(!changeOwner){
            //登录名不存在且内容填完整，将数据插入数据库里
            query.prepare("INSERT INTO owner(uid, userName, password, tele, sex, houseId, houseArea, CarId) "
                          "VALUE(:uid, :userName, :password, :tele, :sex, :houseId, :houseArea, :CarId)");
            query.bindValue(":uid", ui->edtOwUid->text().trimmed());
            query.bindValue(":userName", ui->edtOwName->text().trimmed());
            query.bindValue(":password", ui->edtOwPassword->text().trimmed());
            query.bindValue(":tele", ui->edtTele->text().trimmed());
            query.bindValue(":sex", ui->boxOwSex->currentText().trimmed());
            query.bindValue(":houseId", ui->edtOwHouseId->text().trimmed());
            query.bindValue(":houseArea", ui->edtOwHouseArea->text().trimmed());
            query.bindValue(":CarId", ui->edtCarId->text().trimmed());
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("添加成功！"));
        }else{
            query.prepare("UPDATE owner SET uid = ?, userName = ?, password = ?, tele = ?, sex = ?, houseId = ?,"
                          "houseArea = ?, CarId = ? "
                          "WHERE uid = ?");
            query.addBindValue(ui->edtOwUid->text().trimmed());
            query.addBindValue(ui->edtOwName->text().trimmed());
            query.addBindValue(ui->edtOwPassword->text().trimmed());
            query.addBindValue(ui->edtTele->text().trimmed());
            query.addBindValue(ui->boxOwSex->currentText().trimmed());
            query.addBindValue(ui->edtOwHouseId->text().trimmed());
            query.addBindValue(ui->edtOwHouseArea->text().trimmed());
            query.addBindValue(ui->edtCarId->text().trimmed());
            query.addBindValue(ui->edtOwUid->text().trimmed());
            query.exec();

            if(ui->checkCar->isChecked() && ui->boxCar->currentText() != ""){
                query.prepare("UPDATE owner SET wantCar = ?, agCar = true "
                              "WHERE uid = ?");
                query.addBindValue(ui->boxCar->currentText().trimmed());
                query.addBindValue(ui->edtOwUid->text().trimmed());
                query.exec();
            }

            if(!ui->checkCar->isChecked()){
                query.prepare("UPDATE owner SET wantCar = '', agCar = false "
                              "WHERE uid = ?");
                query.addBindValue(ui->edtOwUid->text().trimmed());
                query.exec();

                query.prepare("UPDATE car SET ownerUid = '' "
                              "WHERE ownerUid = ?");
                query.addBindValue(ui->edtOwUid->text().trimmed());
                query.exec();
            }

            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改成功！"));
            changeOwner = false;
            FindOwnerDialog foDlg;
            close();
            foDlg.exec();
        }
    }
    close();
}

void AddOwnerDialog::closeEvent(QCloseEvent * event){
    if(changeOwner){
        FindOwnerDialog foDlg;
        this->accept();
        foDlg.exec();
    }
    changeOwner = false;
}

void AddOwnerDialog::owDelete(){
    QSqlQuery query;
    int res = QMessageBox::information(this, QObject::tr("询问"), QObject::tr("确认删除该业主信息？"), QMessageBox::Yes, QMessageBox::No);
    if(res == QMessageBox::Yes){
        QString ownerId = ui->edtOwUid->text().trimmed();
        query.exec(QString("DELETE FROM owner WHERE uid = '%1'").arg(ownerId));
        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("该业主信息已被删除！"));
        close();
    }
}
