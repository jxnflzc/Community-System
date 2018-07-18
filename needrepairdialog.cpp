#include "needrepairdialog.h"
#include "ui_needrepairdialog.h"

#include <QtSql>
#include <QMessageBox>
#include <QString>
#include <QDateTime>
#include <QPainter>
#include <QTranslator>

extern bool language_en;

extern QString userName;
extern QString uid;
extern QString status;
QString houseId;
extern int power;

NeedRepairDialog::NeedRepairDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NeedRepairDialog)
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

NeedRepairDialog::~NeedRepairDialog()
{
    delete ui;
}

void NeedRepairDialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/IconPic/pic/backimage.jpg");//图片的位置
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//根据窗口的宽高来将图片画在窗口上
}

void NeedRepairDialog::showL(){
    QSqlQuery query;
    query.exec(QString("SELECT houseId FROM owner WHERE uid = '%1'").arg(uid));
    query.next();
    houseId = query.value("houseId").toString().trimmed();

    ui->boxHouse->addItem(houseId);
}

void NeedRepairDialog::submit(){
    QDateTime time = QDateTime::currentDateTime();
    QSqlQuery query;
    if(ui->edtProblem->toPlainText().trimmed() == ""){
        QMessageBox::information(this, QObject::tr("错误"), QObject::tr("请将信息填完整！"));
    }else{
        query.prepare("INSERT INTO repair(ownerUid, owner, houseId, kind, problem, submitDate) "
                      "VALUES(:ownerUid, :owner, :houseId, :kind, :problem, :submitDate)");
        query.bindValue(":ownerUid", uid);
        query.bindValue(":houseId", ui->boxHouse->currentText());
        query.bindValue(":owner", userName);
        query.bindValue(":kind", ui->boxKind->currentText());
        query.bindValue(":problem", ui->edtProblem->toPlainText().trimmed());
        query.bindValue(":submitDate", time.toString("yyyy-MM-dd hh:mm:ss"));
        query.exec();
        QMessageBox::information(this, QObject::tr("成功"), QObject::tr("报修成功！"));
        close();
    }
}
