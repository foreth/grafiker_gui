#include "addempdialog.h"
#include "ui_addempdialog.h"

addEmpDialog::addEmpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEmpDialog)
{
    ui->setupUi(this);

    ui->positionCombo->addItem("sprzedawca/kasjer");
    ui->positionCombo->addItem("asystent");
    ui->positionCombo->addItem("zastępca kierownika");
    ui->positionCombo->addItem("kierownik");

    ui->timeCombo->addItem("pełny");
    ui->timeCombo->addItem("3/4");
    ui->timeCombo->addItem("1/2");
    ui->timeCombo->addItem("1/4");

    positionIndex = 0;
    timeIndex = 0;


}

addEmpDialog::~addEmpDialog()
{
    delete ui;
}

QString addEmpDialog::getFirstName()
{
   return ui->lineEdit->text();
}

QString addEmpDialog::getLastName()
{
   return ui->lineEdit_2->text();
}

int addEmpDialog::getPosition()
{
    return positionIndex;
}

int addEmpDialog::getTime()
{
    return timeIndex;
}


void addEmpDialog::on_positionCombo_activated(int index)
{
    positionIndex = index;
}

void addEmpDialog::on_timeCombo_activated(int index)
{
    timeIndex = index;
}
