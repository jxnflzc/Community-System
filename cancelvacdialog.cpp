#include "cancelvacdialog.h"
#include "ui_cancelvacdialog.h"

CancelVacDialog::CancelVacDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CancelVacDialog)
{
    ui->setupUi(this);
}

CancelVacDialog::~CancelVacDialog()
{
    delete ui;
}
