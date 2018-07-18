#include "attendstatedialog.h"
#include "ui_attendstatedialog.h"

#include <QString>
#include <QtSql>
#include <QMessageBox>
#include <QPainter>
#include <QTranslator>

extern bool language_en;
extern int power;

AttendStateDialog::AttendStateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttendStateDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    show();
    ui->tableAttend->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableAttend->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableAttend,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

AttendStateDialog::~AttendStateDialog()
{
    delete ui;
}

void AttendStateDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void AttendStateDialog::show(){
    QSqlQuery query;
    query.exec("SELECT uid, userName, attend FROM staff");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont = ui->tableAttend->rowCount();
        ui->tableAttend->insertRow(RowCont);//增加一行
        ui->tableAttend->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
        ui->tableAttend->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
        QString isAttend;
        if(query.value("attend").toBool()){
            isAttend = "是";
        }else{
            isAttend = "否";
        }
        ui->tableAttend->setItem(i,2,new QTableWidgetItem(isAttend));

    }
}

void AttendStateDialog::getItem(int row, int col){
    if(power == 3 && ui->tableAttend->item(row, 2)->text().trimmed() == "否"){
        QSqlQuery query;
        QString changeStaff = ui->tableAttend->item(row, 0)->text();
        int res = QMessageBox::information(this, QObject::tr("询问"), QObject::tr("是否要手动替这名员工签到？"),
                                           QMessageBox::Yes, QMessageBox::No);
        if(res == QMessageBox::Yes){
            query.prepare("UPDATE staff SET attend = true "
                          "WHERE uid = ?");
            query.addBindValue(changeStaff);
            query.exec();
            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("手动签到成功！"));
            int rCount = ui->tableAttend->rowCount();

            for(int i=0; i < rCount; i++){
                ui->tableAttend->removeRow(0);
            }
            query.exec("SELECT uid, userName, attend FROM staff");

            for (int i = 0;query.next(); i++) {
                int RowCont;
                RowCont = ui->tableAttend->rowCount();
                ui->tableAttend->insertRow(RowCont);//增加一行
                ui->tableAttend->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
                ui->tableAttend->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
                QString isAttend;
                if(query.value("attend").toBool()){
                    isAttend = "是";
                }else{
                    isAttend = "否";
                }
                ui->tableAttend->setItem(i,2,new QTableWidgetItem(isAttend));

                ui->edtUserName->clear();
            }
        }
    }
}

void AttendStateDialog::search(){
    QSqlQuery query;
    QString StaffName = ui->edtUserName->text().trimmed();
    query.exec(QString("SELECT uid, userName, attend FROM staff "
               "WHERE userName = '%1'").arg(StaffName));
    int rCount = ui->tableAttend->rowCount();

    for(int i=0; i < rCount; i++){
        ui->tableAttend->removeRow(0);
    }

    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont = ui->tableAttend->rowCount();
        ui->tableAttend->insertRow(RowCont);//增加一行
        ui->tableAttend->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
        ui->tableAttend->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
        QString isAttend;
        if(query.value("attend").toBool()){
            isAttend = "是";
        }else{
            isAttend = "否";
        }
        ui->tableAttend->setItem(i,2,new QTableWidgetItem(isAttend));

    }
}
