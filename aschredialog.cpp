#include "aschredialog.h"
#include "ui_aschredialog.h"
#include "repairscheduledialog.h"

#include <QtSql>
#include <QString>
#include <QPainter>
#include <QMessageBox>
#include <QTranslator>

extern bool language_en;

extern QString changeReId;
extern int power;
extern QString uid;

ASChReDialog::ASChReDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ASChReDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    showL();
    if(language_en){
        QTranslator translator;
        translator.load(":language/qzher_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

ASChReDialog::~ASChReDialog()
{
    delete ui;
}

void ASChReDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void ASChReDialog::showL(){
    QSqlQuery query;
    query.exec(QString("SELECT * FROM repair WHERE id = %1").arg(changeReId));
    query.next();

    ui->edtOwnerUid->setText(query.value("ownerUid").toString().trimmed());
    ui->edtName->setText(query.value("owner").toString().trimmed());
    ui->edtHouseId->setText(query.value("houseId").toString().trimmed());
    ui->edtKind->setText(query.value("kind").toString().trimmed());
    ui->edtProblem->setText(query.value("problem").toString().trimmed());
    ui->edtStaff->setText(query.value("solveStaff").toString().trimmed());
    ui->edtTele->setText(query.value("teleNum").toString().trimmed());
    ui->edtState->setText(query.value("state").toString().trimmed());
    if(query.value("evaluate").toBool()){
        QString star;
        ui->edtEvaluate->setText(query.value("thank").toString().trimmed());
        for(int i = 0; i < query.value("star").toInt(); i++){
            star += "★";
        }

        ui->txtStar->setText(star);
    }else{
        ui->edtEvaluate->setText(QObject::tr("尚未评价"));
        ui->txtStar->setText(QObject::tr("尚未评价"));
    }
    if(query.value("state").toString().trimmed() == "已解决"){
        ui->btnSubmit->setEnabled(false);
    }
}

void ASChReDialog::submit(){
    QSqlQuery query;
    query.prepare("UPDATE repair SET solveStaff = ?, teleNum = ?, state = ? "
                  "WHERE id = ?");
    query.addBindValue(ui->edtStaff->text().trimmed());
    query.addBindValue(ui->edtTele->text().trimmed());
    query.addBindValue(ui->boxState->currentText());
    query.addBindValue(changeReId);
    query.exec();

    QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改成功！"));
    RepairScheduleDialog rsDlg;
    this->accept();
    rsDlg.exec();
}

void ASChReDialog::closeEvent(QCloseEvent * event){
    RepairScheduleDialog rsDlg;
    this->accept();
    rsDlg.exec();
}
