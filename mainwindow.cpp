#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addempdialog.h"
#include <QDebug>
#include <QDate>

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

    //inicjalizacja gridSchedule

    ui->gridSchedule->addWidget(new QLabel(""), 1, 1);
    ui->gridSchedule->addWidget(new QLabel("Poniedziałek"), 1, 2);
    ui->gridSchedule->addWidget(new QLabel("Wtorek"), 1, 3);
    ui->gridSchedule->addWidget(new QLabel("Środa"), 1, 4);
    ui->gridSchedule->addWidget(new QLabel("Czwartek"), 1, 5);
    ui->gridSchedule->addWidget(new QLabel("Piątek"), 1, 6);
    ui->gridSchedule->addWidget(new QLabel("Sobota"), 1, 7);
    ui->gridSchedule->addWidget(new QLabel("Niedziela"), 1, 8);

   /* for(int i = 0; i < 16; i++) // 14 to liczba godzin roboczych...
    {
        ui->gridSchedule->addWidget(new QLabel(QString::number(7 + i) + ":00"), 2 + i, 1);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 2);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 3);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 4);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 5);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 6);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 7);
        ui->gridSchedule->addWidget(new QLabel(""), 2 + i, 8);
    }*/

    //utworzenie uchwytów do labeli

    for(int i = 0; i < 7; i++)
    {
        cells.push_back(new vector<QLabel*>);

        for(int j = 0; j < 16; j++)
        {
            vector<QLabel*>& currVector = *(cells.at(i));
            currVector.push_back(new QLabel(""));
        }
    }

     for(int i = 0; i < 16; i++) // 16 to liczba godzin roboczych...
     {
         ui->gridSchedule->addWidget(new QLabel(QString::number(7 + i) + ":00"), 2 + i, 1);



         for(int j = 0; j < 7; j++)
         {
             vector<QLabel*>& currVector = *(cells.at(j));
             ui->gridSchedule->addWidget(currVector.at(i), 2 + i, j + 2);
         }
     }

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
    short month = ui->monthCombo->currentIndex();
    QDate data(2016, month + 1, 1);

    Month* month_schedule_pointer = rossmann->makeSchedule(data.daysInMonth(), days(data.dayOfWeek() - 1));

    Month& month_schedule = *month_schedule_pointer;

    int c_temp = 1;
    for (Day& d : month_schedule.getDayList())
    {
        for (WorkHour& wh : d.getTime())
        {
            for (Employee& emp : wh.getEmployees())
            {
                QString prevText = getText(wh.getHour() - 6, c_temp);
                setText(wh.getHour() - 6, c_temp, prevText + "\n" + QString::fromStdString(emp.getName()));
            }
        }

        if(++c_temp == 8)
            break;
    }

}

void MainWindow::setText(int row, int col, QString text)
{
    vector<QLabel*>& currVector = *(cells.at(col - 1));
    QLabel& currLabel = *(currVector.at(row - 1));
    currLabel.setText(text);
}

QString MainWindow::getText(int row, int col)
{
    vector<QLabel*>& currVector = *(cells.at(col - 1));
    QLabel& currLabel = *(currVector.at(row - 1));
    return currLabel.text();
}
