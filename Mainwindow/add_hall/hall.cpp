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

    hallView->setMode(true);
}

hall::~hall()
{

    delete ui;
}


