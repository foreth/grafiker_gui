#ifndef ADDEMPDIALOG_H
#define ADDEMPDIALOG_H

#include <QDialog>

namespace Ui {
class addEmpDialog;
}

class addEmpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addEmpDialog(QWidget *parent = 0);
    ~addEmpDialog();

    QString getFirstName();
    QString getLastName();
    int getPosition();
    int getTime();


private slots:

    void on_positionCombo_activated(int index);

    void on_timeCombo_activated(int index);

private:
    Ui::addEmpDialog *ui;
    int positionIndex;
    int timeIndex;

};

#endif // ADDEMPDIALOG_H
