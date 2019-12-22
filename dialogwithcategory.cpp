#include "dialogwithcategory.h"
#include "ui_dialogwithcategory.h"

DialogWithCategory::DialogWithCategory(QString competition_key,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWithCategory)
{
    ui->setupUi(this);

    Settings = new QSettings("settings.ini", QSettings::IniFormat);
    Settings->beginGroup("Font");
    int size = Settings->value("Size",12).toInt();
    Settings->endGroup();

    ui->to_main_tatami->setFont(QFont("Calibri",size));
    ui->to_other_tatami->setFont(QFont("Calibri",size));
    ui->buttonBox->setFont(QFont("Calibri",size));
    ui->table_main_tatami->setFont(QFont("Calibri",size));
    ui->table_other_tatami->setFont(QFont("Calibri",size));
    query.exec("SELECT DISTINCT Категория FROM "+competition_key);
    model_main_tatami = new QStandardItemModel;
    while(query.next())
    {
        model_main_tatami->appendRow(new QStandardItem(query.value(0).toString()));
    }
    model_main_tatami->setHorizontalHeaderLabels(QStringList()<<"Категории на основном татами");

    model_other_tatami = new QStandardItemModel;
    model_other_tatami->setHorizontalHeaderLabels(QStringList()<<"Категории на другой татами");
    ui->table_main_tatami->setModel(model_main_tatami);
    ui->table_other_tatami->setModel(model_other_tatami);
    ui->table_main_tatami->resizeRowsToContents();
}

DialogWithCategory::~DialogWithCategory()
{
    delete ui;
}

void DialogWithCategory::on_to_other_tatami_clicked()
{
    if (ui->table_main_tatami->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->table_main_tatami->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        int row = ui->table_main_tatami->selectionModel()->selectedRows().at(i).row();
        QString category = ui->table_main_tatami->model()->data(ui->table_main_tatami->model()->index(row,0)).toString();

        model_other_tatami->appendRow(new QStandardItem(category));
    }
    for (int i=0;i<count_selected_rows;i++)
    {
        ui->table_main_tatami->model()->removeRow(ui->table_main_tatami->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    ui->table_main_tatami->resizeRowsToContents();
    ui->table_other_tatami->resizeRowsToContents();
}

void DialogWithCategory::on_to_main_tatami_clicked()
{
    if (ui->table_other_tatami->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->table_other_tatami->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        int row = ui->table_other_tatami->selectionModel()->selectedRows().at(i).row();
        QString category = ui->table_other_tatami->model()->data(ui->table_other_tatami->model()->index(row,0)).toString();

        model_main_tatami->appendRow(new QStandardItem(category));
    }
    for (int i=0;i<count_selected_rows;i++)
    {
        ui->table_other_tatami->model()->removeRow(ui->table_other_tatami->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    ui->table_other_tatami->resizeRowsToContents();
    ui->table_other_tatami->resizeRowsToContents();
}

QStandardItemModel* DialogWithCategory::return_model()
{
    return model_other_tatami;
}
