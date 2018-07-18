#include "findstaffdialog.h"
#include "ui_findstaffdialog.h"
#include "addpersondialog.h"

#include <QtSql>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QTranslator>

extern bool language_en;

QString changeUid;
bool changeStaff = false;

FindStaffDialog::FindStaffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindStaffDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showStaff();
    ui->tableStaff->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableStaff->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableStaff,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

FindStaffDialog::~FindStaffDialog()
{
    delete ui;
}

void FindStaffDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void FindStaffDialog::showStaff(){
    QSqlQuery query;
    query.exec("SELECT uid, userName, tele, sex, status, power FROM staff");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableStaff->rowCount();
        ui->tableStaff->insertRow(RowCont);//增加一行
        ui->tableStaff->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
        ui->tableStaff->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
        ui->tableStaff->setItem(i,2,new QTableWidgetItem(query.value("tele").toString()));
        ui->tableStaff->setItem(i,3,new QTableWidgetItem(query.value("sex").toString()));
        ui->tableStaff->setItem(i,4,new QTableWidgetItem(query.value("status").toString()));
        ui->tableStaff->setItem(i,5,new QTableWidgetItem(query.value("power").toString()));
    }
}

void FindStaffDialog::getItem(int row, int col){
    changeUid = ui->tableStaff->item(row, 0)->text();
    changeStaff = true;
    AddPersonDialog chDlg;
    close();
    chDlg.exec();
}

void FindStaffDialog::search(){
    QString staffName = ui->edtStaff->text().trimmed();

    int rCount = ui->tableStaff->rowCount();
    for(int i = 0; i < rCount; i++){
     ui->tableStaff->removeRow(0);
    }

    if(staffName == ""){
        showStaff();
    }else{
        QSqlQuery query;
        query.exec(QString("SELECT uid, userName, tele, sex, status, power FROM staff "
                   "WHERE userName = '%1'").arg(staffName));

        for (int i = 0;query.next(); i++) {
            int RowCont;
            RowCont=ui->tableStaff->rowCount();
            ui->tableStaff->insertRow(RowCont);//增加一行
            ui->tableStaff->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
            ui->tableStaff->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
            ui->tableStaff->setItem(i,2,new QTableWidgetItem(query.value("tele").toString()));
            ui->tableStaff->setItem(i,3,new QTableWidgetItem(query.value("sex").toString()));
            ui->tableStaff->setItem(i,4,new QTableWidgetItem(query.value("status").toString()));
            ui->tableStaff->setItem(i,5,new QTableWidgetItem(query.value("power").toString()));
        }
    }
    ui->edtStaff->clear();
}
