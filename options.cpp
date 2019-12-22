#include "options.h"
#include "ui_options.h"

#include "QFileDialog"
#include "QDebug"
#include "QtGui"
#include "QAxWidget"
#include "QAxObject"
#include "QtSql"
#include "QMessageBox"
#include "QSqlTableModel"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonParseError"
#include "QFile"
#include "QRegExp"
#include "QSqlTableModel"
#include "mainwindow.h"
#include <QInputDialog>
#include "QFontDatabase"
Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    model_positions = new QStandardItemModel;
    model_positions->setHorizontalHeaderLabels(QStringList()<<"Должность");
    model_causes = new QStandardItemModel;
    model_causes->setHorizontalHeaderLabels(QStringList()<<"Индекс исключения"<<"Причина");
    model_for_categorys = new QStandardItemModel;
}

Options::~Options()
{
    delete ui;
}

void Options::get_options(QSettings *pyk)
{
    Settings = pyk;
    Settings->beginGroup("Geometry");
    setGeometry(Settings->value("GeometryOptions",QRect(500,500,600,600)).toRect());
    Settings->endGroup();
    Settings->beginGroup("causes");
    QStringList keys = Settings->childKeys();
    for (int i=0; i<keys.size();i++)
    {
     QString cause = Settings->value(keys[i]).toString();
     QString key = keys.at(i);
      model_causes->appendRow(QList<QStandardItem*>()<<new QStandardItem(key)<< new QStandardItem(cause));
    }
    Settings->endGroup();
    ui->view_cause->setModel(model_causes);
    model_causes->sort(0, Qt::AscendingOrder);
    ui->view_cause->resizeRowsToContents();
    ui->view_cause->resizeColumnsToContents();

    ui->view_position->setModel(model_positions);
    Settings->beginGroup("positions");
    for (int i=0;i<Settings->childKeys().count();i++)
    {
        QStandardItem *item = new QStandardItem(Settings->value(QString::number(i)).toString());
        model_positions->appendRow(item);
    }
    Settings->endGroup();
    ui->view_position->resizeRowsToContents();
    Settings->beginGroup("Font");

    int size = Settings->value("Size",12).toInt();
    QApplication::setFont(QFont("Calibri",size));
    ui->FontSize_SpinBox->setValue(size);
    Settings->endGroup();
}

void Options::on_load_template_2_clicked()
{
QString Json_file;
Json_file = QFileDialog::getOpenFileName(this,"Выберите Json", "","json (*.json)");
if (Json_file==""){
return;
}

QFile File;
File.setFileName(Json_file);
File.open(QIODevice::ReadOnly|QFile::Text);
QJsonDocument doc;
if (File.isOpen()){
doc = QJsonDocument::fromJson(QByteArray(File.readAll()));
} else{
return;
}
File.close();

QJsonArray docArray = QJsonValue(doc.object().value("categorys")).toArray();


for (int i=0;i<docArray.count();i++) {
QStandardItem *item_age_from = new QStandardItem(docArray.at(i).toObject().value("age_from").toString());
QStandardItem *item_age_to = new QStandardItem(docArray.at(i).toObject().value("age_to").toString());
QStandardItem *item_gender = new QStandardItem(docArray.at(i).toObject().value("gender").toString());
QStandardItem *kvalifications = new QStandardItem(docArray.at(i).toObject().value("kvalification").toString());
QStandardItem *item_ku_from = new QStandardItem(docArray.at(i).toObject().value("kval_from").toString());
QStandardItem *item_ku_to = new QStandardItem(docArray.at(i).toObject().value("kval_to").toString());
QStandardItem *category = new QStandardItem(docArray.at(i).toObject().value("category").toString());

model_for_categorys->appendRow(QList<QStandardItem*>()<<item_gender<<item_age_from<<item_age_to<<kvalifications<<item_ku_from<<item_ku_to<<category);

}
ui->view_all_categorys_2->setModel(model_for_categorys);
ui->view_all_categorys_2->resizeColumnsToContents();
ui->view_all_categorys_2->resizeRowsToContents();

}

void Options::on_save_template_2_clicked()
{
    QString save_file_route = QFileDialog::getSaveFileName(this,"Сохранить шаблон","шаблон","*.json");
    if (save_file_route==""){
        return;
    }
    QJsonObject main_framework;
    QJsonArray categorys_array;
    QJsonObject one_category;

    int count_categorys = ui->view_all_categorys_2->model()->rowCount();

    for (int i=0; i<count_categorys; i++)
    {
        one_category["gender"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,0)).toString();
        one_category["age_from"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,1)).toString();
        one_category["age_to"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,2)).toString();
        one_category["kvalification"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,3)).toString();
        one_category["kval_from"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,4)).toString();
        one_category["kval_to"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,5)).toString();
        one_category["category"] = ui->view_all_categorys_2->model()->data(ui->view_all_categorys_2->model()->index(i,6)).toString();
        categorys_array.append(one_category);
    }

    main_framework["categorys"] = categorys_array;

    QFileInfo file_info(save_file_route);
    QDir::setCurrent(file_info.path());

    QFile json_file(save_file_route);

    if (!json_file.open(QIODevice::WriteOnly)){

            return;
    }
}

void Options::on_delete_category_2_clicked()
{
    if (ui->view_all_categorys_2->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->view_all_categorys_2->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        ui->view_all_categorys_2->model()->removeRow(ui->view_all_categorys_2->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    ui->view_all_categorys_2->resizeRowsToContents();
    ui->view_all_categorys_2->resizeColumnsToContents();
}

void Options::on_delete_all_category_2_clicked()
{
    QMessageBox::StandardButton reply =  QMessageBox::question(this,"Удалить все категории","Удалить все категории?", QMessageBox::Yes | QMessageBox::No);
    if (reply==QMessageBox::Yes)
    {
        if (ui->view_all_categorys_2->model() ==nullptr)
        {
            QMessageBox::warning(this,"Пусто", "Таблица пустая");
            return;
        }
        int count_rows = ui->view_all_categorys_2->model()->rowCount();
        for (int i=0;i<count_rows;i++) {
         ui->view_all_categorys_2->model()->removeRow(0);
        }
    }else if (reply == QMessageBox::No) {
           return;
        }
}

void Options::on_create_category_2_clicked()
{
    if (ui->kval_to_2->text()=="" || ui->kval_from_2->text()=="" || ui->age_to_2->text()=="" || ui->age_from_2->text()=="" || gender =="" || kvalifications==""){
        QMessageBox::critical(this, "Ошибка", "Кажется вы не ввели какие-либо данные");
        return;
    }
    QStandardItem *kvalifications_i = new QStandardItem(kvalifications);
    QStandardItem *gender_i = new QStandardItem(gender);
    QStandardItem *age_from_i = new QStandardItem(ui->age_from_2->text());
    QStandardItem *age_to_i = new QStandardItem(ui->age_to_2->text());
    QStandardItem *ku_from_i = new QStandardItem(ui->kval_from_2->text());
    QStandardItem *ku_to_i = new QStandardItem(ui->kval_to_2->text());
    QString final_category = gender+", "+ui->age_from_2->text()+"-"+ui->age_to_2->text()+",лет, "+ui->kval_from_2->text()+"-"+ui->kval_to_2->text()+','+kvalifications;
    QStandardItem *final_category_i = new QStandardItem(final_category);
    model_for_categorys->appendRow(QList<QStandardItem*>()<<gender_i<<age_from_i<<age_to_i<<kvalifications_i<<ku_from_i<<ku_to_i<<final_category_i);
    ui->view_all_categorys_2->setModel(model_for_categorys);
    ui->view_all_categorys_2->resizeColumnsToContents();
    ui->kval_to_2->setText("");
    ui->kval_from_2->setText("");
    ui->kval_to_2->setText("");
    ui->age_to_2->setText("");
    ui->age_from_2->setText("");
}

void Options::on_gender_M_2_clicked()
{
    gender="м";
}

void Options::on_gender_J_2_clicked()
{
    gender = "ж";
}

void Options::on_kval_dan_2_clicked()
{
    kvalifications = "дан";
}

void Options::on_kval_ku_2_clicked()
{
    kvalifications="кю";
}

void Options::closeEvent(QCloseEvent *event)
{
    Settings->beginGroup("Geometry");
    Settings->setValue("GeometryOptions",geometry());
    Settings->endGroup();
    QMessageBox::StandardButton baton = QMessageBox::question(this,"Сохранить настройки?","Сохранить настройки, перед закрытием окна?", QMessageBox::Yes | QMessageBox::No);
    if (baton == QMessageBox::Yes)
    {

        Settings->beginGroup("Font");
        Settings->setValue("Size",QString::number(ui->FontSize_SpinBox->value()));
        Settings->endGroup();

        Settings->beginGroup("causes");
        QStringList caus = Settings->childKeys();
        for (int i=0;i<caus.count();i++)
        {
            Settings->remove(caus[i]);
        }
        for (int row=0;row<ui->view_cause->model()->rowCount();row++)
        {
            QString index = ui->view_cause->model()->data(ui->view_cause->model()->index(row,0)).toString();
            QString cause = ui->view_cause->model()->data(ui->view_cause->model()->index(row,1)).toString();
            Settings->setValue(index,cause);
        }

        Settings->endGroup();

        Settings->beginGroup("positions");
        QStringList pos;
        caus = Settings->childKeys();
                for (int i=0;i<caus.count();i++)
                {
                    Settings->remove(caus[i]);
                }
        for (int i=0;i<ui->view_position->model()->rowCount();i++)
        {
            Settings->setValue(QString::number(i),ui->view_position->model()->data(ui->view_position->model()->index(i,0)).toString());
        }
        Settings->endGroup();
    } else if (baton == QMessageBox::No) {
        //None
}
    emit repeat_font();
    emit get_open_main();
    event->accept();
}

void Options::on_add_cause_clicked()
{
    if (ui->cauese_excude_edit->text()=="")
    {
        QMessageBox::warning(this,"Добавление причины","Введите поле причины");
        return;
    }
    int index=1;
    if (ui->view_cause->model()->rowCount()==0)
    {

        model_causes->appendRow(QList<QStandardItem*>()<<new QStandardItem(QString::number(-1))<< new QStandardItem(ui->cauese_excude_edit->text()));
        ui->cauese_excude_edit->clear();
        model_causes->sort(0, Qt::DescendingOrder);
        ui->view_cause->setModel(model_causes);
        ui->view_cause->resizeRowsToContents();
        return;
    }

    QList<int> indexes;
    for (int row=0;row<ui->view_cause->model()->rowCount();row++)
    {
      indexes.append(ui->view_cause->model()->data(ui->view_cause->model()->index(row,0)).toInt());
    }
    int min=-1;
    bool was= false;
    for (int i=0;i<indexes.count();i++)
    {
        if (min !=indexes[i])
        {
            index=min;
            was = true;
            break;
        }
        min-=1;
    }
    if (was==false)
    {
        index = indexes.at(indexes.count()-1)-1;
    }
    model_causes->appendRow(QList<QStandardItem*>()<<new QStandardItem(QString::number(index))<< new QStandardItem(ui->cauese_excude_edit->text()));
    ui->cauese_excude_edit->clear();
    model_causes->sort(0, Qt::AscendingOrder); //Good
    ui->view_cause->setModel(model_causes);
}

void Options::on_delete_cause_clicked()
{
    QMessageBox::StandardButton baton = QMessageBox::question(this,"Удалить причину?","Удаление причины может привести к тому, что у участников в проведенных мероприятиях будет неизвестна причина исключения"
                                                                                      "\nВы уверены?",QMessageBox::Yes | QMessageBox::No);
    if (baton==QMessageBox::No)
    {
        return;
    }
    if (ui->view_cause->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->view_cause->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        ui->view_cause->model()->removeRow(ui->view_cause->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    ui->view_cause->resizeRowsToContents();
    ui->view_cause->resizeColumnsToContents();
}

void Options::on_add_position_clicked()
{
    if (ui->position_work_edit->text()=="")
    {
        QMessageBox::warning(this,"Пустое поле","Для добавления должности \n введите её в поле");
    }
    model_positions->appendRow(new QStandardItem(ui->position_work_edit->text()));
    ui->position_work_edit->clear();
    ui->view_position->resizeRowsToContents();
}

void Options::on_delete_position_clicked()
{
    if (ui->view_position->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->view_position->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        ui->view_position->model()->removeRow(ui->view_position->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    ui->view_position->resizeRowsToContents();
}

void Options::on_FontSize_SpinBox_valueChanged(int arg1)
{
    ui->FontSize_SpinBox->setFont(QFont("Calibri",arg1));
    QApplication::setFont(QFont("Calibri",arg1));
    ui->tabWidget->setFont(QFont("Calibri",arg1));
    ui->add_cause->setFont(QFont("Calibri",arg1));
    ui->add_position->setFont(QFont("Calibri",arg1));
    ui->cauese_excude_edit->setFont(QFont("Calibri",arg1));
    ui->delete_cause->setFont(QFont("Calibri",arg1));
    ui->delete_position->setFont(QFont("Calibri",arg1));
    ui->position_work_edit->setFont(QFont("Calibri",arg1));
    ui->view_cause->setFont(QFont("Calibri",arg1));
    ui->view_position->setFont(QFont("Calibri",arg1));

    ui->create_category_2->setFont(QFont("Calibri",arg1));
    ui->delete_all_category_2->setFont(QFont("Calibri",arg1));
    ui->delete_category_2->setFont(QFont("Calibri",arg1));
    ui->groupBox_12->setFont(QFont("Calibri",arg1));
    ui->gender_J_2->setFont(QFont("Calibri",arg1));
    ui->gender_M_2->setFont(QFont("Calibri",arg1));
    ui->groupBox_14->setFont(QFont("Calibri",arg1));
    ui->age_from_2->setFont(QFont("Calibri",arg1));
    ui->age_to_2->setFont(QFont("Calibri",arg1));
    ui->groupBox_15->setFont(QFont("Calibri",arg1));
    ui->kval_from_2->setFont(QFont("Calibri",arg1));
    ui->kval_to_2->setFont(QFont("Calibri",arg1));
    ui->groupBox_16->setFont(QFont("Calibri",arg1));
    ui->kval_ku_2->setFont(QFont("Calibri",arg1));
    ui->kval_dan_2->setFont(QFont("Calibri",arg1));
    ui->load_template_2->setFont(QFont("Calibri",arg1));
    ui->save_template_2->setFont(QFont("Calibri",arg1));
    ui->view_all_categorys_2->setFont(QFont("Calibri",arg1));


}
