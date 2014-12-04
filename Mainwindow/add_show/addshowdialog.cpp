#include "addshowdialog.h"
#include "ui_addshowdialog.h"

addShowDialog::addShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addShowDialog)
{
    ui->setupUi(this);

    /*
     * Get the movies/halls and insert them into the movieCBB and hallCBB here
     *
     *
     */

}

addShowDialog::~addShowDialog()
{
    delete ui;
}

void addShowDialog::on_addHallButton_clicked()
{
    QDate date;
    QTime time;
    date = ui->calendarWidget->selectedDate();
    time = ui->timeEdit->time();

    QDateTime dateTime(date, time);

    emit add_Show();

}

void addShowDialog::on_cancelHallButton_clicked()
{
    close();
}
