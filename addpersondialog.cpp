#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include "findstaffdialog.h"

#include <QMessageBox>
#include <QtSql>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QTranslator>

extern bool language_en;

extern QString changeUid;
extern bool changeStaff;

AddPersonDialog::AddPersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->btnDelete->setVisible(false);
    showL();
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

void AddPersonDialog::showL(){
    if(changeStaff){
        this->setWindowTitle(QObject::tr("修改员工"));
        ui->btnAdd->setText(QObject::tr("修改"));
        QSqlQuery query;
        query.exec(QString("SELECT * FROM staff WHERE uid = '%1'").arg(changeUid));
        query.next();
        ui->edtAddUid->setText(changeUid);
        ui->edtAddUserName->setText(query.value("userName").toString().trimmed());
        ui->edtAddPassword->setText(query.value("password").toString().trimmed());
        ui->edtTele->setText(query.value("tele").toString().trimmed());
        ui->edtAddStatus->setText(query.value("status").toString().trimmed());
        ui->btnDelete->setVisible(true);
    }
}

void AddPersonDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void AddPersonDialog::addPerson(){  //添加员工
    QSqlQuery query;
    if(ui->edtAddUid->text().trimmed() == "" || ui->edtAddUserName->text().trimmed() == ""
            || ui->edtAddPassword->text().trimmed() == "" || ui->edtAddStatus->text().trimmed() == ""){
        //内容没填完整提示
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("内容请填完整！"));
    }else{
        QString userId = ui->edtAddUid->text().trimmed();
        query.exec(QString("SELECT * FROM staff WHERE uid = '%1'").arg(userId));//查询登录名是否存在
        if(query.next() && !changeStaff){
            QMessageBox::warning(this, QObject::tr("失败"), QObject::tr("该登录名已经存在！"));
        }else if(!changeStaff){
            //登录名不存在且内容填完整，将数据插入数据库里
            query.prepare("INSERT INTO staff(uid, userName, password, tele, sex, status, power) "
                          "VALUE(:uid, :userName, :password, :tele, :sex, :status, :power)");
            query.bindValue(":uid", ui->edtAddUid->text().trimmed());
            query.bindValue(":userName", ui->edtAddUserName->text().trimmed());
            query.bindValue(":password", ui->edtAddPassword->text().trimmed());
            query.bindValue(":tele", ui->edtTele->text().trimmed());
            query.bindValue(":sex", ui->boxAddSex->currentText().trimmed());
            query.bindValue(":status", ui->edtAddStatus->text().trimmed());
            query.bindValue(":power", ui->boxAddPower->currentText().trimmed());
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("添加成功！"));
        }else{
            query.prepare("UPDATE staff SET uid = ?, userName = ?, password = ?, tele = ?, sex = ?, status = ?, power = ? "
                          "WHERE uid = ?");
            query.addBindValue(ui->edtAddUid->text().trimmed());
            query.addBindValue(ui->edtAddUserName->text().trimmed());
            query.addBindValue(ui->edtAddPassword->text().trimmed());
            query.addBindValue(ui->edtTele->text().trimmed());
            query.addBindValue(ui->boxAddSex->currentText().trimmed());
            query.addBindValue(ui->edtAddStatus->text().trimmed());
            query.addBindValue(ui->boxAddPower->currentText().trimmed());
            query.addBindValue(ui->edtAddUid->text().trimmed());
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改成功！"));
            changeStaff = false;
            FindStaffDialog fsDlg;
            close();
            fsDlg.exec();
        }
    }
    close();
}

void AddPersonDialog::reset(){
    ui->edtAddUid->clear();
    ui->edtAddUserName->clear();
    ui->edtAddPassword->clear();
    ui->edtAddStatus->clear();
    ui->edtAddUid->setFocus();
    QMessageBox::information(this, QObject::tr("成功"), QObject::tr("重置成功！"));
}

void AddPersonDialog::closeEvent(QCloseEvent * event){
    if(changeStaff){
        FindStaffDialog fsDlg;
        this->accept();
        fsDlg.exec();
    }
    changeStaff = false;
}

void AddPersonDialog::stDelete(){
    QSqlQuery query;
    int res = QMessageBox::information(this, QObject::tr("询问"), QObject::tr("确认删除该员工信息？"), QMessageBox::Yes, QMessageBox::No);
    if(res == QMessageBox::Yes){
        QString staffId = ui->edtAddUid->text().trimmed();
        query.exec(QString("DELETE FROM staff WHERE uid = '%1'").arg(staffId));
        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("该员工信息已被删除！"));
        close();
    }
}
