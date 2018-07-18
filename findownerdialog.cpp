#include "findownerdialog.h"
#include "ui_findownerdialog.h"
#include "addownerdialog.h"

#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QTranslator>

extern bool language_en;

QString changeOwUid;
bool changeOwner = false;
extern int power;

FindOwnerDialog::FindOwnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindOwnerDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showOwner();
    ui->tableOwner->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableOwner->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableOwner,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

FindOwnerDialog::~FindOwnerDialog()
{
    delete ui;
}

void FindOwnerDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void FindOwnerDialog::showOwner(){
    QSqlQuery query;
    query.exec("SELECT * FROM owner");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableOwner->rowCount();
        ui->tableOwner->insertRow(RowCont);//增加一行
        ui->tableOwner->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
        ui->tableOwner->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
        ui->tableOwner->setItem(i,2,new QTableWidgetItem(query.value("tele").toString()));
        ui->tableOwner->setItem(i,3,new QTableWidgetItem(query.value("sex").toString()));
        ui->tableOwner->setItem(i,4,new QTableWidgetItem(query.value("houseId").toString()));
        ui->tableOwner->setItem(i,5,new QTableWidgetItem(query.value("houseArea").toString()));
        ui->tableOwner->setItem(i,6,new QTableWidgetItem(query.value("CarId").toString()));
    }
}

void FindOwnerDialog::getItem(int row, int col){
    if(power == 3){
        changeOwUid = ui->tableOwner->item(row, 0)->text();
        changeOwner = true;
        AddOwnerDialog aoDlg;
        close();
        aoDlg.exec();
    }
}

void FindOwnerDialog::search(){
    QString ownerName = ui->edtOwner->text().trimmed();

    int rCount = ui->tableOwner->rowCount();
    for(int i=0; i < rCount; i++){
     ui->tableOwner->removeRow(0);
    }

    if(ownerName == ""){
        showOwner();
    }else{
        QSqlQuery query;
        query.exec(QString("SELECT * FROM owner "
                   "WHERE userName = '%1'").arg(ownerName));

        for (int i = 0;query.next(); i++) {
            int RowCont;
            RowCont=ui->tableOwner->rowCount();
            ui->tableOwner->insertRow(RowCont);//增加一行
            ui->tableOwner->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
            ui->tableOwner->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
            ui->tableOwner->setItem(i,2,new QTableWidgetItem(query.value("tele").toString()));
            ui->tableOwner->setItem(i,3,new QTableWidgetItem(query.value("sex").toString()));
            ui->tableOwner->setItem(i,4,new QTableWidgetItem(query.value("houseId").toString()));
            ui->tableOwner->setItem(i,5,new QTableWidgetItem(query.value("houseArea").toString()));
            ui->tableOwner->setItem(i,6,new QTableWidgetItem(query.value("CarId").toString()));
        }
        ui->edtOwner->clear();
    }

}
