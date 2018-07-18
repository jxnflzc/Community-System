#include "repairscheduledialog.h"
#include "ui_repairscheduledialog.h"
#include "aschredialog.h"
#include "ochredialog.h"

#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QPoint>
#include <QContextMenuEvent>
#include <QTranslator>

extern bool language_en;

QString changeReId;
extern int power;
extern QString uid;

RepairScheduleDialog::RepairScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RepairScheduleDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    if(power == 1){
        showOw();
    }else{
        showAS();
    }
    ui->tableRepair->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableRepair->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableRepair,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

RepairScheduleDialog::~RepairScheduleDialog()
{
    delete ui;
}

void RepairScheduleDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void RepairScheduleDialog::showAS(){
    QSqlQuery query;
    query.exec("SELECT * FROM repair ORDER BY id DESC");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableRepair->rowCount();
        ui->tableRepair->insertRow(RowCont);//增加一行
        ui->tableRepair->setItem(i,0,new QTableWidgetItem(query.value("id").toString()));
        ui->tableRepair->setItem(i,1,new QTableWidgetItem(query.value("ownerUid").toString()));
        ui->tableRepair->setItem(i,2,new QTableWidgetItem(query.value("owner").toString()));
        ui->tableRepair->setItem(i,3,new QTableWidgetItem(query.value("houseId").toString()));
        ui->tableRepair->setItem(i,4,new QTableWidgetItem(query.value("problem").toString()));
        ui->tableRepair->setItem(i,5,new QTableWidgetItem(query.value("solveStaff").toString()));
        ui->tableRepair->setItem(i,6,new QTableWidgetItem(query.value("teleNum").toString()));
        ui->tableRepair->setItem(i,7,new QTableWidgetItem(query.value("state").toString()));

        if(query.value("evaluate").toBool()){
            ui->tableRepair->setItem(i,8, new QTableWidgetItem(QObject::tr("是")));
        }else{
            ui->tableRepair->setItem(i,8,new QTableWidgetItem(QObject::tr("否")));
        }

    }
}

void RepairScheduleDialog::showOw(){
    QSqlQuery query;
    query.exec(QString("SELECT * FROM repair WHERE ownerUid = '%1' ORDER BY id DESC").arg(uid));
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableRepair->rowCount();
        ui->tableRepair->insertRow(RowCont);//增加一行
        ui->tableRepair->setItem(i,0,new QTableWidgetItem(query.value("id").toString()));
        ui->tableRepair->setItem(i,1,new QTableWidgetItem(query.value("ownerUid").toString()));
        ui->tableRepair->setItem(i,2,new QTableWidgetItem(query.value("owner").toString()));
        ui->tableRepair->setItem(i,3,new QTableWidgetItem(query.value("houseId").toString()));
        ui->tableRepair->setItem(i,4,new QTableWidgetItem(query.value("problem").toString()));
        ui->tableRepair->setItem(i,5,new QTableWidgetItem(query.value("solveStaff").toString()));
        ui->tableRepair->setItem(i,6,new QTableWidgetItem(query.value("teleNum").toString()));
        ui->tableRepair->setItem(i,7,new QTableWidgetItem(query.value("state").toString()));

        if(query.value("evaluate").toBool()){
            ui->tableRepair->setItem(i,8, new QTableWidgetItem(QObject::tr("是")));
        }else{
            ui->tableRepair->setItem(i,8,new QTableWidgetItem(QObject::tr("否")));
        }

    }
}

void RepairScheduleDialog::getItem(int row, int col){
    changeReId = ui->tableRepair->item(row, 0)->text();
    if(power == 1){
        OChReDialog ocDlg;
        close();
        ocDlg.exec();
    }else{
        ASChReDialog ascDlg;
        close();
        ascDlg.exec();
    }
}
