#include "agreevacdialog.h"
#include "ui_agreevacdialog.h"

#include <QMessageBox>
#include <QtSql>
#include <QPainter>
#include <QDebug>
#include <QString>
#include <QTranslator>

extern bool language_en;

AgreeVacDialog::AgreeVacDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgreeVacDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showWants();
    ui->tableAgree->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编辑内容
    ui->tableAgree->setSelectionBehavior(QAbstractItemView::SelectRows);//选定一行
    connect(ui->tableAgree,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getItem(int,int)));
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

AgreeVacDialog::~AgreeVacDialog()
{
    delete ui;
}

void AgreeVacDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void AgreeVacDialog::showWants(){
    QSqlQuery query;
    query.exec("SELECT id, uid, userName, kind, reason FROM vacation WHERE finish = false AND isRead = false");
    for (int i = 0;query.next(); i++) {
        int RowCont;
        RowCont=ui->tableAgree->rowCount();
        ui->tableAgree->insertRow(RowCont);//增加一行
        ui->tableAgree->setItem(i,0,new QTableWidgetItem(query.value("id").toString()));
        ui->tableAgree->setItem(i,1,new QTableWidgetItem(query.value("uid").toString()));
        ui->tableAgree->setItem(i,2,new QTableWidgetItem(query.value("userName").toString()));
        ui->tableAgree->setItem(i,3,new QTableWidgetItem(query.value("kind").toString()));
        ui->tableAgree->setItem(i,4,new QTableWidgetItem(query.value("reason").toString()));
    }
}

void AgreeVacDialog::getItem(int row, int col){
    QSqlQuery query;
    query.exec(QString("SELECT isRead FROM vacation WHERE id = '%1'").arg(ui->tableAgree->item(row, 0)->text()));
    query.next();
    if(!query.value("isRead").toInt()){
        int res = QMessageBox::question(this,"询问", "准许放假吗？",QMessageBox::Yes,QMessageBox::No,
                                        QMessageBox::Cancel);
        if(res == QMessageBox::Yes){
            query.prepare("UPDATE vacation SET agree = true, isRead = true "
                          "WHERE id = ?");
            query.addBindValue(ui->tableAgree->item(row, 0)->text());
            query.exec();

            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("批准成功！"));
        }

        if(res == QMessageBox::No){
            query.prepare("UPDATE vacation SET finish = true, agree = false, isRead = true "
                          "WHERE id = ?");
            query.addBindValue(ui->tableAgree->item(row, 0)->text());
            query.exec();

            query.prepare("UPDATE staff SET vacation = false "
                          "WHERE uid = ?");
            query.addBindValue(ui->tableAgree->item(row, 1)->text());
            query.exec();

            QMessageBox::information(this, QObject::tr("成功"), QObject::tr("驳回成功！"));
        }
    }else{
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("已经审核过了！"));
    }
    close();
    AgreeVacDialog avDlg;
    avDlg.exec();
}
