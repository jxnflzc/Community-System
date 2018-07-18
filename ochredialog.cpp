#include "ochredialog.h"
#include "ui_ochredialog.h"
#include "repairscheduledialog.h"

#include <QtSql>
#include <QString>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QTranslator>

extern bool language_en;

extern QString changeReId;
extern int power;
extern QString uid;

OChReDialog::OChReDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OChReDialog)
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

OChReDialog::~OChReDialog()
{
    delete ui;
}

void OChReDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void OChReDialog::showL(){
    QSqlQuery query;
    query.exec(QString("SELECT * FROM repair WHERE id = %1").arg(changeReId));
    query.next();

    ui->edtId->setText(query.value("id").toString().trimmed());
    ui->edtKind->setText(query.value("kind").toString().trimmed());
    ui->edtProblem->setText(query.value("problem").toString().trimmed());
    ui->edtEvaluate->setText(query.value("thank").toString().trimmed());

    if(query.value("state").toString().trimmed() == "已解决"){
        ui->btnChange->setEnabled(false);
    }
    if(query.value("evaluate").toBool()){
        ui->btnSubmit->setEnabled(false);
    }
}

void OChReDialog::change(){
    QSqlQuery query;
    query.prepare("UPDATE repair SET kind = ?, problem = ? "
                  "WHERE id = ?");
    query.addBindValue(ui->boxKind->currentText());
    query.addBindValue(ui->edtProblem->toPlainText().trimmed());
    query.addBindValue(changeReId);
    query.exec();

    QMessageBox::information(this, QObject::tr("成功"), QObject::tr("修改成功！"));
    RepairScheduleDialog rsDlg;
    this->accept();
    rsDlg.exec();
}

void OChReDialog::submit(){
    QSqlQuery query;
    int res = QMessageBox::information(this, QObject::tr("询问"), QObject::tr("只有一次提交评价的机会，确定提交吗？"), QMessageBox::Yes, QMessageBox::No);
    if(res == QMessageBox::Yes){
        query.prepare("UPDATE repair SET evaluate = true, thank = ?, star = ? "
                      "WHERE id = ?");
        query.addBindValue(ui->edtEvaluate->toPlainText().trimmed());
        query.addBindValue(ui->boxStar->currentText().toInt());
        query.addBindValue(changeReId);
        query.exec();

        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("提交成功！"));
        RepairScheduleDialog rsDlg;
        this->accept();
        rsDlg.exec();
    }
}

void OChReDialog::closeEvent(QCloseEvent * event){
    RepairScheduleDialog rsDlg;
    this->accept();
    rsDlg.exec();
}
