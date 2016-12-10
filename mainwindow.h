#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "scheduler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_employeeList_activated(int index);
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_buttonMakeSchedule_clicked();

private:
    Ui::MainWindow *ui;
    Shop* rossmann;

    void updateEmpCombo();
};

#endif // MAINWINDOW_H
