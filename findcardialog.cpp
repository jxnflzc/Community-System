#include "findcardialog.h"
#include "ui_findcardialog.h"
#include "addcardialog.h"

#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QTranslator>

extern bool language_en;

QString changeCarUid;
bool changeCar;
extern int power;

FindCarDialog::FindCarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindCarDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showCar();
    ui->tableCar->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableCar->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableCar,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

FindCarDialog::~FindCarDialog()
{
    delete ui;
}

void FindCarDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void FindCarDialog::showCar(){
    QSqlQuery query;
    QSqlQuery queryCarId;
    query.exec("SELECT * FROM car");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableCar->rowCount();
        ui->tableCar->insertRow(RowCont);//增加一行
        ui->tableCar->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
        ui->tableCar->setItem(i,1,new QTableWidgetItem(query.value("ownerUId").toString()));
        QString isRent;
        if(query.value("isRent").toBool()){
            isRent = "是";
        }else{
            isRent = "否";
        }
        ui->tableCar->setItem(i,2,new QTableWidgetItem(isRent));
        ui->tableCar->setItem(i,3,new QTableWidgetItem(query.value("price").toString()));
        if(query.value("ownerUId").toString() != ""){
            queryCarId.exec(QString("SELECT CarId, userName FROM owner WHERE uid = '%1'").arg(query.value("ownerUId").toString()));
            queryCarId.next();
            ui->tableCar->setItem(i,4,new QTableWidgetItem(queryCarId.value("userName").toString()));
            ui->tableCar->setItem(i,5,new QTableWidgetItem(queryCarId.value("CarId").toString()));
        }else{
            ui->tableCar->setItem(i,4,new QTableWidgetItem(""));
            ui->tableCar->setItem(i,5,new QTableWidgetItem(""));
        }
    }
}

void FindCarDialog::getItem(int row, int col){
    if(power != 1){
        changeCarUid = ui->tableCar->item(row, 0)->text();
        changeCar = true;
        AddCarDialog acDlg;
        close();
        acDlg.exec();
    }
}

void FindCarDialog::search(){
    QString CarName = ui->edtCar->text().trimmed();
    int rCount = ui->tableCar->rowCount();
    for(int i=0; i < rCount; i++){
     ui->tableCar->removeRow(0);
    }
    if(CarName == ""){
        showCar();
    }else{
        QSqlQuery query;
        query.exec(QString("SELECT uid, ownerUId, isRent FROM car "
                   "WHERE uid = '%1'").arg(CarName));

        for (int i = 0;query.next(); i++) {
            int RowCont;
            RowCont=ui->tableCar->rowCount();
            ui->tableCar->insertRow(RowCont);//增加一行
            ui->tableCar->setItem(i,0,new QTableWidgetItem(query.value("uid").toString()));
            ui->tableCar->setItem(i,1,new QTableWidgetItem(query.value("ownerUId").toString()));
            QString isRent;
            if(query.value("isRent").toBool()){
                isRent = "是";
            }else{
                isRent = "否";
            }
            ui->tableCar->setItem(i,2,new QTableWidgetItem(isRent));
        }
    }
    ui->edtCar->clear();
}
