#include "data_dialog.h"
#include "ui_data_dialog.h"
#include "QDebug"
#include <QDateEdit>

Data_dialog::Data_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Data_dialog)
{
    ui->setupUi(this);
    Settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    Settings->beginGroup("Font");
    int size = Settings->value("Size",12).toInt();
    Settings->endGroup();
    ui->data_competition->setFont(QFont("Calibri",size));
}

Data_dialog::~Data_dialog()
{
    delete ui;
}

void Data_dialog::on_buttonBox_accepted()
{

    QDate date = ui->data_competition->selectedDate();
    emit push_data(&date);
    this->close();
}

void Data_dialog::on_buttonBox_rejected()
{
    this->close();
}
