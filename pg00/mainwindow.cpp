#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reCalc();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_calendarWidget_selectionChanged()
{
    reCalc();
}

void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    Q_UNUSED(time)
    reCalc();
}

void MainWindow::reCalc()
{
    int year  = ui->calendarWidget->selectedDate().toString("yyyy").toInt();
    int month  = ui->calendarWidget->selectedDate().toString("MM").toInt();
    int day  = ui->calendarWidget->selectedDate().toString("dd").toInt();
    int hour = ui->timeEdit->time().toString("hh").toInt() ;
    int min = ui->timeEdit->time().toString("mm").toInt() ;
    double sec = ui->timeEdit->time().toString("ss").toDouble() ;

    double MJD = mjd(year, month, day, hour, min, sec) ;
    double JD = MJD + 2400000.5; // Julian Date
    ui->label->setText(
                "<center>Modified Julian Date: "+QString::number(MJD)+
                "<br>Julian Date: "+QString::number(JD) +"</center>");
}

double MainWindow::ddd(int D, int M, double S)
{
  double sign;


  if ( (D<0) || (M<0) || (S<0) ) sign = -1.0; else sign = 1.0;

  return  sign * ( fabs((double)D)+fabs((double)M)/60.0+fabs(S)/3600.0 );
}



double MainWindow::mjd ( int year, int month, int day, int hour, int min, double sec )
{
  long    mjdMidnight;
  double  fracOfDay;
  int     b;


  if (month<=2) { month+=12; --year;}

  if ( (10000L*year+100L*month+day) <= 15821004L )
    b = -2 + ((year+4716)/4) - 1179;     // Julian calendar
  else
    b = (year/400)-(year/100)+(year/4);  // Gregorian calendar

  mjdMidnight = 365L*year - 679004L + b + int(30.6001*(month+1)) + day;
  fracOfDay   = ddd(hour,min,sec) / 24.0;

  return mjdMidnight + fracOfDay;
}
