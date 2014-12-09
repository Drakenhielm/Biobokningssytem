#include "hall.h"
#include "ui_hall.h"
#include "hallview.h"
#include <QVBoxLayout>

hall::hall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hall)
{
    ui->setupUi(this);

    hallView = new HallView(this);
    QHBoxLayout *lineLayout = new QHBoxLayout;
    ui->frame_hall->setLayout(lineLayout);
    ui->frame_hall->layout()->addWidget(hallView);

    connect(ui->spinBox_rows, SIGNAL(valueChanged(int)), hallView, SLOT(setRows(int)));
    connect(ui->spinBox_columns, SIGNAL(valueChanged(int)), hallView, SLOT(setColumns(int)));

    connect(hallView, SIGNAL(selectedSeatsChanged(QList<int>)), this, SLOT(setLabelNumberOfSeats()));

    hallView->setMode(true);
}

hall::~hall()
{

    delete ui;
}

void hall::setLabelNumberOfSeats()
{
    ui->label_number_of_seats->setText("Seats: " + QString::number(hallView->getTotalNumberOfSeats()));
}

void hall::on_AddButton_clicked()
{
    QString hallName = ui->hall_name->text();
    QString screenSize = QString::number(ui->spinBox_screen_width->value()) + " X " + QString::number(ui->spinBox_screen_height->value());
    QString soundSystem = ui->comboBox_sound->currentText();
    QList<QList<bool>> seats = hallView->getSeats();
    emit addHall(hallName, screenSize, soundSystem, seats);
    close();
}