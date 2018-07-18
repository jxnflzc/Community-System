#include "rentcardialog.h"
#include "ui_rentcardialog.h"

#include <QString>
#include <QtSql>
#include <QPainter>
#include <QMessageBox>
#include <QTranslator>

extern bool language_en;

RentCarDialog::RentCarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RentCarDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showApp();
    ui->tableApplicate->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableApplicate->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableApplicate,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

RentCarDialog::~RentCarDialog()
{
    delete ui;
}

void RentCarDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void RentCarDialog::showApp(){
    QSqlQuery query;
    query.exec("SELECT uid, userName, wantCar FROM owner WHERE wantCar != '' AND agCar = false");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableApplicate->rowCount();
        ui->tableApplicate->insertRow(RowCont);//增加一行
        ui->tableApplicate->setItem(i,0,new QTableWidgetItem(query.value("wantCar").toString()));
        ui->tableApplicate->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
        ui->tableApplicate->setItem(i,2,new QTableWidgetItem(query.value("uid").toString()));
    }
}

void RentCarDialog::getItem(int row, int col){
    int res = QMessageBox::information(this, QObject::tr("询问"), QObject::tr("确认通过这个申请吗？"), QMessageBox::Yes, QMessageBox::No,
                                       QMessageBox::Cancel);
    ui->tableApplicate->item(row, 0)->text();
    if(res == QMessageBox::Yes){
        QSqlQuery query;
        query.prepare("UPDATE owner SET wantCar = '' WHERE uid != ? AND wantCar = ?");
        query.addBindValue(ui->tableApplicate->item(row, 2)->text());
        query.addBindValue(ui->tableApplicate->item(row, 0)->text());
        query.exec();

        query.prepare("UPDATE owner SET agCar = true WHERE uid = ?");
        query.addBindValue(ui->tableApplicate->item(row, 2)->text());
        query.exec();

        query.prepare("UPDATE car SET ownerUid = ? WHERE uid = ?");
        query.addBindValue(ui->tableApplicate->item(row, 2)->text());
        query.addBindValue(ui->tableApplicate->item(row, 0)->text());
        query.exec();

        int rCount = ui->tableApplicate->rowCount();
        for(int i=0; i < rCount; i++){
         ui->tableApplicate->removeRow(0);
        }

        query.exec("SELECT uid, userName, wantCar FROM owner WHERE wantCar != '' AND agCar = false");
        for (int i = 0;query.next(); i++) {
            int RowCont;
            RowCont=ui->tableApplicate->rowCount();
            ui->tableApplicate->insertRow(RowCont);//增加一行
            ui->tableApplicate->setItem(i,0,new QTableWidgetItem(query.value("wantCar").toString()));
            ui->tableApplicate->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
            ui->tableApplicate->setItem(i,2,new QTableWidgetItem(query.value("uid").toString()));
        }

        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("申请已通过！"));
    }else if(res == QMessageBox::No){
        QSqlQuery query;
        query.prepare("UPDATE owner SET wantCar = '' WHERE uid = ?");
        query.addBindValue(ui->tableApplicate->item(row, 2)->text());
        query.exec();

        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("申请已驳回！"));

        int rCount = ui->tableApplicate->rowCount();
        for(int i=0; i < rCount; i++){
         ui->tableApplicate->removeRow(0);
        }

        query.exec("SELECT uid, userName, wantCar FROM owner WHERE wantCar != '' AND agCar = false");
        for (int i = 0;query.next(); i++) {
            int RowCont;
            RowCont=ui->tableApplicate->rowCount();
            ui->tableApplicate->insertRow(RowCont);//增加一行
            ui->tableApplicate->setItem(i,0,new QTableWidgetItem(query.value("wantCar").toString()));
            ui->tableApplicate->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
            ui->tableApplicate->setItem(i,2,new QTableWidgetItem(query.value("uid").toString()));
        }
    }

}

void RentCarDialog::search(){
    QString CarName = ui->edtCar->text().trimmed();

    int rCount = ui->tableApplicate->rowCount();

    for(int i=0; i < rCount; i++){
     ui->tableApplicate->removeRow(0);
    }

    if(CarName == ""){
        showApp();
    }else{
        QSqlQuery query;
        query.exec(QString("SELECT uid, userName, wantCar FROM owner "
                   "WHERE wantCar = '%1' AND agCar = false").arg(CarName));
        for (int i = 0;query.next(); i++) {
            int RowCont;
            RowCont=ui->tableApplicate->rowCount();
            ui->tableApplicate->insertRow(RowCont);//增加一行
            ui->tableApplicate->setItem(i,0,new QTableWidgetItem(query.value("wantCar").toString()));
            ui->tableApplicate->setItem(i,1,new QTableWidgetItem(query.value("userName").toString()));
            ui->tableApplicate->setItem(i,2,new QTableWidgetItem(query.value("uid").toString()));
        }
    }
    ui->edtCar->clear();
}
