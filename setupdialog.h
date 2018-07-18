#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = 0);
    ~SetupDialog();
    void paintEvent(QPaintEvent*);
    void saveConfig();
    void loadConfig();

signals:
    void changeUi();

public slots:
    void save();

private:
    Ui::SetupDialog *ui;
};

#endif // SETUPDIALOG_H
