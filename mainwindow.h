#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "scheduler.h"
#include <QLabel>
#include <vector>

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
    void setText(int row, int col, QString text);
    QString getText(int row, int col);

private:
    Ui::MainWindow *ui;
    Shop* rossmann;
    vector<vector<QLabel*>*> cells;

    void updateEmpCombo();
};

#endif // MAINWINDOW_H
