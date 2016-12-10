#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addempdialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rossmann = new Shop;

    rossmann->addEmployee("Magdalena", "Pastuszak", ASSISTANT, THREE);
    rossmann->addEmployee("Katarzyna", "Maj", REGULAR, THREE);
    rossmann->addEmployee("Joanna", "Budzik", MANAGER, FULL);
    rossmann->addEmployee("Anna", "Poranna", REGULAR, HALF);
    rossmann->addEmployee("Marzena", "Zzalasu", REGULAR, THREE);
    rossmann->addEmployee("Maja", "Kwiatkowska", ASSISTANT, FULL);

    updateEmpCombo();

    on_employeeList_activated(0);   // reczne wywolanie slota, zeby zainicjalizowac labela z opisem pierwszego pracownika

    ui->monthCombo->addItem("Styczeń");
    ui->monthCombo->addItem("Luty");
    ui->monthCombo->addItem("Marzec");
    ui->monthCombo->addItem("Kwiecień");
    ui->monthCombo->addItem("Maj");
    ui->monthCombo->addItem("Czerwiec");
    ui->monthCombo->addItem("Lipiec");
    ui->monthCombo->addItem("Sierpień");
    ui->monthCombo->addItem("Październik");
    ui->monthCombo->addItem("Listopad");
    ui->monthCombo->addItem("Grudzień");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_employeeList_activated(int index)
{
    Employee current = rossmann->getEmployeeList().at(index);
    QString name = "Imie:\t" + QString::fromStdString(current.getName());
    QString id = "ID:\t" + QString::number(current.getID());

    QString position = "Pozycja:\t";

    switch (current.getPosition())
    {
    case 0: position += "sprzedawca/kasjer"; break;
    case 1: position += "asystent"; break;
    case 2: position += "zastępca kierownika"; break;
    case 3: position += "kierownik"; break;
    default: position += "niepoprawna pozycja";
    }

    QString time = "Etat:\t";

    switch (current.getTimeDimension())
    {
    case 0: time += "1/4"; break;
    case 1: time += "1/2"; break;
    case 2: time += "3/4"; break;
    case 3: time += "pełny"; break;
    default: time += "niepoprawna pozycja";
    }

    ui->employeeDescription->setText(name + "\n" + id + "\n" + position + "\n" + time);
}

void MainWindow::updateEmpCombo()
{

    ui->employeeList->clear();

    for(Employee& emp : rossmann->getEmployeeList())
    {
        QString name = QString::fromStdString(emp.getName());
        ui->employeeList->addItem(name);
    }
}

void MainWindow::on_pushButton_clicked()
{
    addEmpDialog aeD;
    aeD.setWindowTitle("Dodaj pracownika");
    aeD.setModal(true);
    if(aeD.exec() == QDialog::Accepted)
    {
       QString fn = aeD.getFirstName();
       QString sn = aeD.getLastName();
       int p = aeD.getPosition();
       int t = aeD.getTime();

        qDebug() << fn << endl;
        qDebug() << sn << endl;
        qDebug() << p << endl;
        qDebug() << 3 - t << endl;

       rossmann->addEmployee(fn.toStdString(), sn.toStdString(), positions(p), times(3 - t));   //w ostatnim, bo odwrotnie jest w combo

       updateEmpCombo();

       ui->employeeList->setCurrentIndex(ui->employeeList->count() - 1);

       on_employeeList_activated(ui->employeeList->count() - 1);
    }

}

void MainWindow::on_pushButton_3_clicked()
{
   short index = ui->employeeList->currentIndex();
   rossmann->getEmployeeList().erase(rossmann->getEmployeeList().begin() + index);

    updateEmpCombo();

    ui->employeeList->setCurrentIndex(index==0 ? 0 : index - 1);

    on_employeeList_activated(index==0 ? 0 : index - 1);

}

void MainWindow::on_buttonMakeSchedule_clicked()
{
  //  rossmann.makeSchedule(9, 2016);
}