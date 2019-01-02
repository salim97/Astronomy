#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "math.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void reCalc();
    double ddd(int D, int M, double S);
    double mjd(int year, int month, int day, int hour, int min, double sec);
private slots:
    void on_calendarWidget_selectionChanged();

    void on_timeEdit_userTimeChanged(const QTime &time);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
