#include "registration.h"
#include "ui_registration.h"
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
#include <QMessageBox>
#include "QCryptographicHash"
Registration::Registration(QSettings *pyk,bool new_comp,Fight *fooo,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    table = new Table();
    fight = fooo;

    Settings = pyk;
    Settings->beginGroup("Geometry");
    setGeometry(Settings->value("GeometryRegistration", QRect(500,500,600,600)).toRect());
    Settings->endGroup();
    Settings->beginGroup("Font");
    int size = Settings->value("Size",12).toInt();
    Settings->endGroup();

    ui->view_all_categorys->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->loading_members->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view_all_judges->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //TAB_1
    ui->tabWidget->setFont(QFont("Calibri",size));
    ui->label_12->setFont(QFont("Calibri",size));
    ui->number_subjects->setFont(QFont("Calibri",size));
    ui->subjects->setFont(QFont("Calibri",size));
    ui->groupBox->setFont(QFont("Calibri",size));
    ui->groupBox_2->setFont(QFont("Calibri",size));
    ui->label_13->setFont(QFont("Calibri",size));
    ui->number_cities->setFont(QFont("Calibri",size));
    ui->cities->setFont(QFont("Calibri",size));

    ui->category_main_judge->setFont(QFont("Calibri",size));
    ui->city_main_judge->setFont(QFont("Calibri",size));
    ui->judge_main->setFont(QFont("Calibri",size));
    ui->kval_main_judge->setFont(QFont("Calibri",size));

    ui->category_secretary_main->setFont(QFont("Calibri",size));
    ui->city_secretary_main->setFont(QFont("Calibri",size));
    ui->kval_main_secretary->setFont(QFont("Calibri",size));
    ui->secretary_main->setFont(QFont("Calibri",size));

    ui->category_jusge_senior->setFont(QFont("Calibri",size));
    ui->city_judge_senior->setFont(QFont("Calibri",size));
    ui->judge_senior->setFont(QFont("Calibri",size));
    ui->kval_senior_judge->setFont(QFont("Calibri",size));

    ui->category_deputy_judge->setFont(QFont("Calibri",size));
    ui->city_deputy_judge->setFont(QFont("Calibri",size));
    ui->deputy_judge_main->setFont(QFont("Calibri",size));
    ui->kval_deputy_judge->setFont(QFont("Calibri",size));

    ui->competition_data->setFont(QFont("Calibri",size));
    ui->competition_name->setFont(QFont("Calibri",size));
    ui->competition_place->setFont(QFont("Calibri",size));
    ui->get_competiton_data->setFont(QFont("Calibri",size));

    ui->label->setFont(QFont("Calibri",size));
    ui->label_2->setFont(QFont("Calibri",size));
    ui->label_3->setFont(QFont("Calibri",size));
    ui->label_4->setFont(QFont("Calibri",size));
    ui->label_5->setFont(QFont("Calibri",size));
    ui->label_6->setFont(QFont("Calibri",size));
    ui->label_7->setFont(QFont("Calibri",size));
    ui->label_8->setFont(QFont("Calibri",size));

    //TAB_2
    ui->load_members->setFont(QFont("Calibri",size));
    ui->save_data->setFont(QFont("Calibri",size));
    ui->loading_members->setFont(QFont("Calibri",size));

    //TAB_3
    ui->loading_members->setFont(QFont("Calibri",size));
    ui->add_category->setFont(QFont("Calibri",size));
    ui->age_from->setFont(QFont("Calibri",size));
    ui->age_to->setFont(QFont("Calibri",size));
    ui->delete_all_category->setFont(QFont("Calibri",size));
    ui->delete_category->setFont(QFont("Calibri",size));
    ui->gender->setFont(QFont("Calibri",size));
    ui->age->setFont(QFont("Calibri",size));
    ui->gender_J->setFont(QFont("Calibri",size));
    ui->gender_M->setFont(QFont("Calibri",size));
    ui->kval_type->setFont(QFont("Calibri",size));
    ui->kval_dan->setFont(QFont("Calibri",size));
    ui->kval_ku->setFont(QFont("Calibri",size));
    ui->kval_value->setFont(QFont("Calibri",size));
    ui->kval_from->setFont(QFont("Calibri",size));
    ui->kval_to->setFont(QFont("Calibri",size));
    ui->load_template->setFont(QFont("Calibri",size));
    ui->push_category_to_members->setFont(QFont("Calibri",size));
    ui->push_category_to_tatami->setFont(QFont("Calibri",size));
    ui->save_template->setFont(QFont("Calibri",size));
    ui->view_all_categorys->setFont(QFont("Calibri",size));

    //TAB_4
    ui->generate_table->setFont(QFont("Calibri",size));
    ui->groupBox_7->setFont(QFont("Calibri",size));
    ui->step_01->setFont(QFont("Calibri",size));
    ui->step_025->setFont(QFont("Calibri",size));
    ui->step_05->setFont(QFont("Calibri",size));
    ui->step_1->setFont(QFont("Calibri",size));
    ui->groupBox_8->setFont(QFont("Calibri",size));
    ui->from_le->setFont(QFont("Calibri",size));
    ui->label_9->setFont(QFont("Calibri",size));
    ui->label_10->setFont(QFont("Calibri",size));
    ui->to_le->setFont(QFont("Calibri",size));
    ui->label_11->setFont(QFont("Calibri",size));

    //TAB_5
    ui->add_custom_member->setFont(QFont("Calibri",size));
    ui->asc_desc_box->setFont(QFont("Calibri",size));
    ui->categories_box->setFont(QFont("Calibri",size));
    ui->create_category->setFont(QFont("Calibri",size));
    ui->delete_this_member->setFont(QFont("Calibri",size));
    ui->groupBox_10->setFont(QFont("Calibri",size));
    ui->Dan_member->setFont(QFont("Calibri",size));
    ui->KU_member->setFont(QFont("Calibri",size));
    ui->value_kval_member->setFont(QFont("Calibri",size));
    ui->groupBox_11->setFont(QFont("Calibri",size));
    ui->city_member->setFont(QFont("Calibri",size));
    ui->org_member->setFont(QFont("Calibri",size));
    ui->stepen_member->setFont(QFont("Calibri",size));
    ui->trainer_member->setFont(QFont("Calibri",size));

    ui->groupBox_13->setFont(QFont("Calibri",size));
    ui->age_member->setFont(QFont("Calibri",size));
    ui->label_15->setFont(QFont("Calibri",size));
    ui->data_birthday_member->setFont(QFont("Calibri",size));
    ui->label_16->setFont(QFont("Calibri",size));
    ui->groupBox_6->setFont(QFont("Calibri",size));
    ui->first_name_member->setFont(QFont("Calibri",size));
    ui->last_name_member->setFont(QFont("Calibri",size));
    ui->patron_name_member->setFont(QFont("Calibri",size));
    ui->groupBox_9->setFont(QFont("Calibri",size));
    ui->gender_J_member->setFont(QFont("Calibri",size));
    ui->gender_M_member->setFont(QFont("Calibri",size));
    ui->sorting_box->setFont(QFont("Calibri",size));
    ui->teams_box->setFont(QFont("Calibri",size));
    ui->view_all_members->setFont(QFont("Calibri",size));

    //TAB_6
    ui->comboBox->setFont(QFont("Calibri",size));
    ui->crew_box->setFont(QFont("Calibri",size));
    ui->desc_asc_box->setFont(QFont("Calibri",size));
    ui->add_crew_judges->setFont(QFont("Calibri",size));
    ui->add_judge->setFont(QFont("Calibri",size));
    ui->change_position_crew->setFont(QFont("Calibri",size));
    ui->delete_judge->setFont(QFont("Calibri",size));
    ui->groupBox_3->setFont(QFont("Calibri",size));
    ui->label_14->setFont(QFont("Calibri",size));
    ui->value_kval_judge->setFont(QFont("Calibri",size));
    ui->type_kval_judge_KU->setFont(QFont("Calibri",size));
    ui->type_kval_judge_DAN->setFont(QFont("Calibri",size));
    ui->groupBox_4->setFont(QFont("Calibri",size));
    ui->city_judge->setFont(QFont("Calibri",size));
    ui->judges_category->setFont(QFont("Calibri",size));
    ui->groupBox_5->setFont(QFont("Calibri",size));
    ui->fitst_name_judge->setFont(QFont("Calibri",size));
    ui->last_name_judge->setFont(QFont("Calibri",size));
    ui->patron_name_judge->setFont(QFont("Calibri",size));
    ui->view_all_judges->setFont(QFont("Calibri",size));

    //TAB_7
    ui->start_competition->setFont(QFont("Calibri",size));




    Settings->beginGroup("positions");
    for (int i=0;i<Settings->childKeys().count();i++)
    {
        positions.append(Settings->value(QString::number(i)).toString());
    }
    Settings->endGroup();
    connect(this,SIGNAL(open_save_member()), table,SLOT(open_count()));
    connect(this, SIGNAL(recieve_data(double , int , int )), table, SLOT(get_data(double , int , int )));
    connect(this, SIGNAL(go_to_competition(QStringList*, QString, Table*,int)), fight, SLOT(start_competition(QStringList*, QString, Table*,int)));
    model_for_all_members = new QSqlTableModel(this, db);
    model_for_categorys = new QStandardItemModel;
    model = new QStandardItemModel;
    model_for_judges = new QSqlTableModel(this,db);
   model_loading_judges = new QStandardItemModel;
    model_for_categorys->setHorizontalHeaderLabels(QStringList()<<"Пол"<<"Возраст от"<<"До (включительно)"<<"Квалификация"<<"Кю от"<<"Кю до(включительно)"<<"Категория");
    ui->competition_data->setDate(QDate::currentDate());
    if (new_comp==true)
    {
        query.prepare("INSERT INTO competitions(НазваниеСоревнований,ДатаПроведения,МестоПроведения,ГлавныйСудья,СтаршийСудья,ГлавныйСекретарь,ЗаместительГлавногоСудьи,КоличествоСубъектов,Субъекты,КоличествоГородов,Города)"
                   "VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11);");
        query.bindValue(":1","");
        query.bindValue(":2","");
        query.bindValue(":3","");
        query.bindValue(":4","");
        query.bindValue(":5","");
        query.bindValue(":6","");
        query.bindValue(":7","");
        query.bindValue(":8","");
        query.bindValue(":9","");
        query.bindValue(":10","");
        query.bindValue(":11","");
        query.exec();
        query.prepare("SELECT PK FROM competitions WHERE end_competition=:false");
        query.bindValue(":false",false);
        if (query.exec()==true) {
            while (query.next())
            {
            PK = query.value(0).toInt(); //получаем ключ perfomance key для всей работы
        }
            }else{
            //NONE
        }

        competition_key.setNum(PK);
        judges_key ="judges_"+ competition_key;
        competition_key = "competition_"+competition_key;
        query.exec("CREATE TABLE ["+competition_key+ "]("
                      "[Фамилия] VARCHAR(100), "
                      "[Имя] VARCHAR(100), "
                      "[Отчество] VARCHAR(100),"
                      "[ДатаРождения] VARCHAR(100),"
                      "[Возраст] INTEGER(100), "
                      "[Пол] VARCHAR(1), "
                      "[Квалификация] VARCHAR(100),"
                      "[СтепеньКвалификации] INTEGER(100),"
                      "[Разряд] VARCHAR(100), "
                      "[Руководитель] VARCHAR(100),"
                      "[Организация] VARCHAR(100), "
                      "[Город] VARCHAR(100), "
                      "[Категория] VARCHAR(100),"
                      "[Место] INTEGER(100) DEFAULT 0,"
                      "[Судья_1] DOUBLE(1000) DEFAULT 0,"
                      "[Судья_2] DOUBLE(1000) DEFAULT 0, "
                      "[Судья_3] DOUBLE(1000) DEFAULT 0, "
                      "[Судья_4] DOUBLE(1000) DEFAULT 0, "
                      "[Судья_5] DOUBLE(1000) DEFAULT 0, "
                      "[СреднийБалл] DOUBLE(1000) DEFAULT 0,"
                      "[Мин_Балл] DOUBLE(1000) DEFAULT 0, "
                      "[Макс_Балл] DOUBLE(1000) DEFAULT 0);");


        query.exec("CREATE TABLE ["+judges_key+"]("
                      "[Фамилия] VARCHAR(100), "
                      "[Имя] VARCHAR(100), "
                      "[Отчество] VARCHAR(100), "
                      "[Город] VARCHAR(100), "
                      "[ТипКвалификации] VARCHAR(5), "
                      "[СтепеньКвалификации] INTEGER, "
                      "[Суд_Категория] VARCHAR(100), "
                      "[Бригада] INTEGER, "
                      "[Должность] VARCHAR(100));");
    } else
    {
        return;
    }

}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_load_template_clicked()
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
if (docArray.isEmpty())
{
    QMessageBox::critical(this,"Не тот файл?","Программа заметила, что вы загрузили не тот файл");
    return;
}

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
ui->view_all_categorys->setModel(model_for_categorys);
ui->view_all_categorys->resizeColumnsToContents();
ui->view_all_categorys->resizeRowsToContents();

}

void Registration::repeat_data()
/*        Обновление tableview      */
{

    if (categories_box=="Без категории")
    {
        categories_box="-";
    }
        model_for_all_members->clear();

        model_for_all_members->setTable(competition_key);
        model_for_all_members->setEditStrategy(QSqlTableModel::OnFieldChange);
        QStringList dop;
        dop<<"Без сортировки"<<"По фамилии"<<"По имени"<<"По возрасту";
        int index_sorting=0;
        switch (dop.indexOf(sorting_box)) {
        case (0):{
            break;
        }
        case(1):{
            index_sorting=0;
            break;
        }
        case(2):{
            index_sorting=1;
            break;
        }
        case(3):{
            index_sorting=4;
            break;
        }
//        case(4):{
//            index_sorting=4;
//            break;
//        }
        }
        if (teams=="Все команды")
        {

            if (sorting_box=="Без сортировки" && categories_box !="Все"){
               model_for_all_members->setFilter("Категория = '"+categories_box+"'");

            } else if (sorting_box != "Без сортировки" && categories_box=="Все" ) {
                if (asc_desc==true)
                {
                    model_for_all_members->setSort(index_sorting, Qt::AscendingOrder);
                } else {
                    model_for_all_members->setSort(index_sorting, Qt::DescendingOrder);
                }
            }
         else if (sorting_box != "Без сортировки" && categories_box != "Все") {
                model_for_all_members->setFilter("Категория = '"+categories_box+"'");
                if (asc_desc==true)
                {
                    model_for_all_members->setSort(index_sorting, Qt::AscendingOrder);
                } else {
                    model_for_all_members->setSort(index_sorting, Qt::DescendingOrder);
                }
            }
        } else{
            if (sorting_box=="Без сортировки" && categories_box !="Все"){
               model_for_all_members->setFilter("Категория = '"+categories_box+"' AND Организация = '"+teams+"'");

            } else if (sorting_box != "Без сортировки" && categories_box=="Все" ) {
                 model_for_all_members->setFilter("Организация = '"+teams+"'");
                if (asc_desc==true)
                {
                    model_for_all_members->setSort(index_sorting, Qt::AscendingOrder);
                } else {
                    model_for_all_members->setSort(index_sorting, Qt::DescendingOrder);
                }
            }
         else if (sorting_box != "Без сортировки" && categories_box != "Все") {
                model_for_all_members->setFilter("Категория = '"+categories_box+"' AND Организация = '"+teams+"'");
                if (asc_desc==true)
                {
                    model_for_all_members->setSort(index_sorting, Qt::AscendingOrder);
                } else {
                    model_for_all_members->setSort(index_sorting, Qt::DescendingOrder);
                }
            } else{
                 model_for_all_members->setFilter("Организация = '"+teams+"'");
            }
        }
        model_for_all_members->removeColumn(22);
        model_for_all_members->select();
        ui->view_all_members->setModel(model_for_all_members);

    ui->view_all_members->setModel(model_for_all_members);
}
void Registration::on_save_template_clicked()
{
QString save_file_route = QFileDialog::getSaveFileName(this,"Сохранить шаблон","шаблон","*.json");
if (save_file_route==""){
    return;
}
QJsonObject main_framework;
QJsonArray categorys_array;
QJsonObject one_category;

int count_categorys = ui->view_all_categorys->model()->rowCount();

for (int i=0; i<count_categorys; i++)
{
    one_category["gender"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,0)).toString();
    one_category["age_from"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,1)).toString();
    one_category["age_to"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,2)).toString();
    one_category["kvalification"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,3)).toString();
    one_category["k:val_from"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,4)).toString();
    one_category["kval_to"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,5)).toString();
    one_category["category"] = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,6)).toString();
    categorys_array.append(one_category);
}

main_framework["categorys"] = categorys_array;

QFileInfo file_info(save_file_route);
QDir::setCurrent(file_info.path());

QFile json_file(save_file_route);

if (!json_file.open(QIODevice::WriteOnly)){

        return;

}

json_file.write(QJsonDocument(main_framework).toJson(QJsonDocument::Indented));

json_file.close();

QMessageBox::information(this,"Сохранено","Шаблон сохранён успешно :)");

}

void Registration::on_delete_category_clicked()
{
    if (ui->view_all_categorys->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->view_all_categorys->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        ui->view_all_categorys->model()->removeRow(ui->view_all_categorys->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    ui->view_all_categorys->resizeRowsToContents();
    ui->view_all_categorys->resizeColumnsToContents();
    ui->view_all_categorys->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Registration::on_delete_all_category_clicked()
{

   QMessageBox::StandardButton reply =  QMessageBox::question(this,"Удалить все категории","Удалить все категории?", QMessageBox::Yes | QMessageBox::No);
   if (reply==QMessageBox::Yes)
   {
       if (ui->view_all_categorys->model() ==nullptr)
       {
           QMessageBox::warning(this,"Пусто", "Таблица пустая");
           return;
       }
       int count_rows = ui->view_all_categorys->model()->rowCount();
       for (int i=0;i<count_rows;i++) {
        ui->view_all_categorys->model()->removeRow(0);
       }
   }else if (reply == QMessageBox::No) {
          return;
       }
   ui->view_all_categorys->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

   }

void Registration::on_add_category_clicked()
{
    if (ui->kval_to->text()=="" || ui->kval_from->text()=="" || ui->age_to->text()=="" || ui->age_from->text()=="" || gender =="" || kvalifications==""){
        QMessageBox::critical(this, "Ошибка", "Кажется вы не ввели какие-либо данные");
        return;
    }
    QStandardItem *kvalifications_i = new QStandardItem(kvalifications);
    QStandardItem *gender_i = new QStandardItem(gender);
    QStandardItem *age_from_i = new QStandardItem(ui->age_from->text());
    QStandardItem *age_to_i = new QStandardItem(ui->age_to->text());
    QStandardItem *ku_from_i = new QStandardItem(ui->kval_from->text());
    QStandardItem *ku_to_i = new QStandardItem(ui->kval_to->text());
    QString final_category = gender+", "+ui->age_from->text()+"-"+ui->age_to->text()+",лет, "+ui->kval_from->text()+"-"+ui->kval_to->text()+','+kvalifications;
    QStandardItem *final_category_i = new QStandardItem(final_category);
    model_for_categorys->appendRow(QList<QStandardItem*>()<<gender_i<<age_from_i<<age_to_i<<kvalifications_i<<ku_from_i<<ku_to_i<<final_category_i);
    ui->view_all_categorys->setModel(model_for_categorys);
    ui->view_all_categorys->resizeColumnsToContents();
    ui->kval_to->setText("");
    ui->kval_from->setText("");
    ui->kval_to->setText("");
    ui->age_to->setText("");
    ui->age_from->setText("");
    all_members_with_category = false;
    set_enabled_to_push_cat_to_tatami();
    ui->view_all_categorys->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::on_kval_dan_clicked()
{
    kvalifications = "дан";
}

void Registration::on_kval_ku_clicked()
{
    kvalifications = "кю";
}

void Registration::on_gender_M_clicked()
{
    gender = "м";
}

void Registration::on_gender_J_clicked()
{
    gender = "ж";
}

void Registration::on_load_members_clicked()
{

    QString excel_route = QFileDialog::getOpenFileName(this, "Open Excel", "", "*.xlsx  *.xlsm  *.xlsb *.xltx *.xls");//открываем диалоговое окно выбора файла
    if (excel_route==""){
        return;
    }
    QAxObject* excel = new QAxObject("Excel.Application",this);//выделяем память на объект excel

    QAxObject* workbooks = excel->querySubObject("Workbooks"); //возвращаем указатель на книги

    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", excel_route); //открываем

    QAxObject* sheets = workbook->querySubObject("Worksheets"); //возвращаем указатель на все листы в книге

    QAxObject* sheet = sheets->querySubObject("Item(int)",1); //указатель на первый лист

    QAxObject *check_cell = sheet->querySubObject("Cells(int,int)",6,2);

    QString check_template =check_cell->property("Value").toString();

    if (check_template=="Список участников команды по ката")
    {
        QAxObject *cell_check = sheet->querySubObject("Cells(int,int)",2,6);
        QString valuta = cell_check->property("Value").toString();
        if (valuta=="1")
        {
             QMessageBox::StandardButton io = QMessageBox::question(this,"Шаблон уже загружен","Кажется этот шаблон был уже загружен \n"
                                                                                               "Вы уверена, что хотите его загрузить еще раз?", QMessageBox::Yes | QMessageBox::No);
             if (io==QMessageBox::No)
             {
                 workbook->dynamicCall("Close()");//dynamicCall - вызов функции метода com объекта, с переданными в него параметрами
                 excel->dynamicCall("Quit()"); //вызываем функцию объекта закрыться
                 return;
             } else if (io==QMessageBox::Yes) {
                 //None
    }
        } else if(valuta !="" && valuta !="1"){
            QMessageBox::StandardButton io = QMessageBox::question(this,"Кто-то испортил шаблон","Кажется кто-то испортил проверку на загрузку шаблона \n"
                                                                                                 "Проверьте клетку F:2 в шаблоне. Она должна иметь состояние 1 или 0. \n"
                                                                                              "Загрузить шаблон, не смотря на ошибку?", QMessageBox::Yes | QMessageBox::No);
            if (io==QMessageBox::No)
            {
                workbook->dynamicCall("Close()");//dynamicCall - вызов функции метода com объекта, с переданными в него параметрами
                excel->dynamicCall("Quit()"); //вызываем функцию объекта закрыться
                return;
            } else if (io==QMessageBox::Yes) {
                //None
    }
        }
        cell_check->setProperty("Value",1);
        workbook->dynamicCall("Save");
        QAxObject* usedRange = sheet->querySubObject("UsedRange"); //указатель на используемую часть листа
        QAxObject* rows = usedRange->querySubObject("Rows"); //указатель на строки в используемой части
        int countRows = rows->property("Count").toInt(); //считаем все строки

        QAxObject* columns = usedRange->querySubObject("Columns"); //указатель на столбцы
        int countCols = columns->property("Count").toInt(); //считаем все используемые столбцы


        QStringList horisontal; //массив для заполнения строк в таблице
        QStringList vertical; //массив для заполнения заголовков в таблице

        horisontal.append(QStringList()<<"Фамилия"<<"Имя"<<"Отчество"<<"Дата рождения"<<"Полных лет"<<"Пол"
                          <<"Квалификация"<<"Степень квалификации"<<"Разряд"<<"Руководитель"<<"Организация"<<"Город");

        QString shelf; //массив горизонтальный

        QStandardItem* true_value;
        for (int rows=9;rows<=countRows;rows++) {
           shelf.setNum(rows-8); //строка = преобразованное число индекса
            vertical.append(shelf);
        }

        for (int row=9;row<=countRows;row++) {
            QAxObject* cell;
            cell = sheet->querySubObject("Cells(int,int)",3,2);//3.2
            QVariant trainer = cell->property("Value");
            QStandardItem* trainer_item;
            trainer_item = new QStandardItem(trainer.toString());
           model->setItem(row-9,9,trainer_item);
            cell = sheet->querySubObject("Cells(int,int)",2,2); //2.2
            QVariant team = cell->property("Value");
            QStandardItem* team_item;
            team_item = new QStandardItem(team.toString());
            model->setItem(row-9,10,team_item);

            cell = sheet->querySubObject("Cells(int,int)",4,2);//4.2
            QVariant city = cell->property("Value");
            QStandardItem* city_item;
            city_item = new QStandardItem(city.toString());
            model->setItem(row-9,11,city_item);



        for (int column=0;column<countCols;column++) {



                QAxObject* cell = sheet->querySubObject("Cells(int,int)",row,column+1); //забираем определенную клетку
                QVariant value = cell->property("Value"); //забираем значение из клетки
                true_value = new QStandardItem(value.toString()); //создаем новый объект типа стандартный предмет
                model->setItem(row-9,column,true_value); //устанавливаем  определенный item в определенную строку и колонку
            }

        }

        workbook->dynamicCall("Close()");//dynamicCall - вызов функции метода com объекта, с переданными в него параметрами
        excel->dynamicCall("Quit()"); //вызываем функцию объекта закрыться

        delete excel; //забываем навсегда про excel
        excel  = nullptr;

       model->setVerticalHeaderLabels(vertical);//устанавливаем вертикальный лэйблы
       model->setHorizontalHeaderLabels(horisontal); //устанавливаем горизонтальные столбы
       ui->loading_members->setModel(model); //устанавливаем модель в виджет

      end_rows =  countRows-8;

       ui->loading_members->resizeRowsToContents(); //обновляем длину строк
       ui->loading_members->resizeColumnsToContents(); //обновляем длину  колонок

       true_value = nullptr;
       delete true_value;
       ui->save_data->setEnabled(true);
       ui->load_members->setEnabled(false);
       whos_load = true;
       all_members_with_category = false;
       set_enabled_to_push_cat_to_tatami();
       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    } else if (check_template=="Список судей") {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        QAxObject *cell_check = sheet->querySubObject("Cells(int,int)",2,6);
        QString valuta = cell_check->property("Value").toString();
        if (valuta=="1")
        {
             QMessageBox::StandardButton io = QMessageBox::question(this,"Шаблон уже загружен","Кажется этот шаблон был уже загружен \n"
                                                                                               "Вы уверена, что хотите его загрузить еще раз?", QMessageBox::Yes | QMessageBox::No);
             if (io==QMessageBox::No)
             {
                 workbook->dynamicCall("Close()");//dynamicCall - вызов функции метода com объекта, с переданными в него параметрами
                 excel->dynamicCall("Quit()"); //вызываем функцию объекта закрыться
                 return;
             } else if (io==QMessageBox::Yes) {
                 //None
    }
        } else if(valuta !="" && valuta !="1"){
            QMessageBox::StandardButton io = QMessageBox::question(this,"Кто-то испортил шаблон","Кажется кто-то испортил проверку на загрузку шаблона \n"
                                                                                                 "Проверьте клетку F:2 в шаблоне. Она должна иметь состояние 1 или 0. \n"
                                                                                              "Загрузить шаблон, не смотря на ошибку?", QMessageBox::Yes | QMessageBox::No);
            if (io==QMessageBox::No)
            {
                workbook->dynamicCall("Close()");//dynamicCall - вызов функции метода com объекта, с переданными в него параметрами
                excel->dynamicCall("Quit()"); //вызываем функцию объекта закрыться
                return;
            } else if (io==QMessageBox::Yes) {
                //None
    }
        }
        cell_check->setProperty("Value",1);
        workbook->dynamicCall("Save");

        QAxObject* usedRange = sheet->querySubObject("UsedRange"); //указатель на используемую часть листа
        QAxObject* rows = usedRange->querySubObject("Rows"); //указатель на строки в используемой части
        int countRows = rows->property("Count").toInt(); //считаем все строки

        QAxObject* columns = usedRange->querySubObject("Columns"); //указатель на столбцы
        int countCols = columns->property("Count").toInt(); //считаем все используемые столбцы


        QStringList horisontal;

        horisontal.append(QStringList()<<"Фамилия"<<"Имя"<<"Отчество"<<"Степень квалификации"<<"Тип квалификации"<<"Судейская категория"
                          <<"Город");

        for (int row=9;row<=countRows;row++) {
            QAxObject* cell;



            cell = sheet->querySubObject("Cells(int,int)",4,2);//4.2
            QVariant city = cell->property("Value");
            QStandardItem* city_item;
            city_item = new QStandardItem(city.toString());
            model_loading_judges->setItem(row-9,6,city_item);


            QStandardItem *true_value;
        for (int column=0;column<countCols;column++) {
                QAxObject* cell = sheet->querySubObject("Cells(int,int)",row,column+1); //забираем определенную клетку
                QVariant value = cell->property("Value"); //забираем значение из клетки
                true_value = new QStandardItem(value.toString()); //создаем новый объект типа стандартный предмет
                model_loading_judges->setItem(row-9,column,true_value); //устанавливаем  определенный item в определенную строку и колонку
            }

        }
        workbook->dynamicCall("Close()");//dynamicCall - вызов функции метода com объекта, с переданными в него параметрами
        excel->dynamicCall("Quit()"); //вызываем функцию объекта закрыться

        model_loading_judges->setHorizontalHeaderLabels(horisontal); //устанавливаем горизонтальные столбы
        ui->loading_members->setModel(model_loading_judges);
        end_rows =  countRows-8;

        ui->loading_members->resizeRowsToContents(); //обновляем длину строк
        ui->loading_members->resizeColumnsToContents(); //обновляем длину  колонок

        ui->save_data->setEnabled(true);
        ui->load_members->setEnabled(false);
        whos_load = false;


    } else{
        QMessageBox::critical(this,"Что это за шаблон?","Программа не может определить вид шаблона\n Клетка В:6 должна иметь следующие названия:\n"
                                                        "1) Список судей\n"
                                                        "2) Список участников команды по ката");
    }
    ui->loading_members->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Registration::on_generate_table_clicked()
{
    from_le = ui->from_le->value();
    to_le = ui->to_le->value();
    if (step==0.0){
        QMessageBox::critical(this,"Шаг", "Вы не выбрали шаг");
        return;
    }
    if (to_le<from_le){
        QMessageBox::critical(this,"Начало и конец", "Начало отсчета баллов должно быть меньше конца");
        return;
    }
    QString st;
    st.setNum(step);
    QString fr;
    fr.setNum(from_le);
    QString to;
    to.setNum(to_le);
    QString temp = st+"_"+fr+"_"+to;
    query.prepare("UPDATE competitions SET Таблица=:temp WHERE PK=:pk");
    query.bindValue(":temp",temp);
    query.bindValue(":pk",PK);
    query.exec();
    emit recieve_data(step, from_le,to_le); //если ошибок нет, вызываем толчок данных
    was_generate = true;
    table->show(); //вызываем форму
    set_enabled_to_push_cat_to_tatami();
}

void Registration::on_save_data_clicked()
{
    bool all_query_exec = true;
    if (whos_load == true)
    {
        for (int row = 0;row<end_rows;row++) {
            query.prepare("INSERT INTO "+competition_key+"(Фамилия, Имя, Отчество, ДатаРождения, Возраст, Пол,Квалификация, СтепеньКвалификации, Разряд, Руководитель, Организация, Город, Категория,Место ) "
                                                         "VALUES(:last_name, :first_name, :patronymic_name , :date_of_birthday , :age , :gender , :type_kval , :kval , :rank , :trainer , :organization , :city, :category,:place);");

            query.bindValue(":last_name",ui->loading_members->model()->data(ui->loading_members->model()->index(row,0)).toString() );
            query.bindValue(":first_name",ui->loading_members->model()->data(ui->loading_members->model()->index(row,1)).toString() );
            query.bindValue(":patronymic_name",ui->loading_members->model()->data(ui->loading_members->model()->index(row,2)).toString() );
            query.bindValue(":date_of_birthday",ui->loading_members->model()->data(ui->loading_members->model()->index(row,3)).toString() );
            query.bindValue(":age",ui->loading_members->model()->data(ui->loading_members->model()->index(row,4)).toInt() );
            query.bindValue(":gender",ui->loading_members->model()->data(ui->loading_members->model()->index(row,5)).toString() );
            query.bindValue(":type_kval",ui->loading_members->model()->data(ui->loading_members->model()->index(row,6)).toString() );
            query.bindValue(":kval",ui->loading_members->model()->data(ui->loading_members->model()->index(row,7)).toInt() );
            query.bindValue(":rank",ui->loading_members->model()->data(ui->loading_members->model()->index(row,8)).toString() );
            query.bindValue(":trainer",ui->loading_members->model()->data(ui->loading_members->model()->index(row,9)).toString() );
            query.bindValue(":organization",ui->loading_members->model()->data(ui->loading_members->model()->index(row,10)).toString() );
            query.bindValue(":city",ui->loading_members->model()->data(ui->loading_members->model()->index(row,11)).toString() );
            query.bindValue(":category","-");
            query.bindValue(":place",0);



            if ( query.exec()==false && all_query_exec==true){
                all_query_exec = false;
            }
        }
        if (all_query_exec !=false){
            QMessageBox::information(this, "Загрузка завершена","Все участники загружены в базу данных успешно.");
            int count_rows = ui->loading_members->model()->rowCount();
            for (int i=0;i<count_rows;i++) {
                ui->loading_members->model()->removeRow(0);
            }
        } else{
            QMessageBox::warning(this,"Что-то пошло не так", "Во время загрузки участников возникли неполадки. \n Некоторые участники могут быть не загружены");
        }

        //ONLY FOR TRIAL VARIANT
		//check_out_members();
        //IN FULL VARIANT DELETE THIS FUNCTION
        repeat_teams_box();
        repeat_data();
    } else {
        for (int i=0; i<end_rows;i++)
        {
        query.prepare("INSERT INTO "+judges_key+"(Фамилия, Имя, Отчество, Город, ТипКвалификации, СтепеньКвалификации, Суд_Категория, Бригада,Должность) "
                                                "VALUES(:last_name,:first_name,:patron_name,:city,:type_kval,:value_kval,:judges_cat,:crew,:pos);");
        query.bindValue(":last_name",ui->loading_members->model()->data(ui->loading_members->model()->index(i,0)).toString() );
        query.bindValue(":first_name",ui->loading_members->model()->data(ui->loading_members->model()->index(i,1)).toString() );
        query.bindValue(":patron_name",ui->loading_members->model()->data(ui->loading_members->model()->index(i,2)).toString() );
        query.bindValue(":city",ui->loading_members->model()->data(ui->loading_members->model()->index(i,6)).toString() );
        query.bindValue(":type_kval",ui->loading_members->model()->data(ui->loading_members->model()->index(i,4)).toString() );
        query.bindValue(":value_kval",ui->loading_members->model()->data(ui->loading_members->model()->index(i,3)).toInt() );
        query.bindValue(":judges_cat",ui->loading_members->model()->data(ui->loading_members->model()->index(i,5)).toString() );
        query.bindValue(":crew",0 );
        query.bindValue(":pos","-" );

        if ( query.exec()==false && all_query_exec==true){
            all_query_exec = false;
        }
        }
        if (all_query_exec !=false){
            QMessageBox::information(this, "Загрузка завершена","Все судьи загружены в базу данных успешно.");
            int count_rows = ui->loading_members->model()->rowCount();
            for (int i=0;i<count_rows;i++) {
                ui->loading_members->model()->removeRow(0);
            }
        } else{
            QMessageBox::warning(this,"Что-то пошло не так", "Во время загрузки судей возникли неполадки. \n Некоторые судьи могут быть не загружены");
        }
        repeat_judges();
    }
ui->save_data->setEnabled(false);
ui->load_members->setEnabled(true);
}

void Registration::on_push_category_to_members_clicked()
{
    if (ui->view_all_categorys->model()==nullptr)
    {
        QMessageBox::critical(this,"Категории","Категории отсутствуют. \n Загрузите шаблон или создайте категории вручную");
        return;
    }
    int count_rows = ui->view_all_categorys->model()->rowCount();

        all_categorys.clear();

    for (int row=0;row<count_rows;row++) {
        QString gender = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,0)).toString();
        int age_from =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,1)).toInt();
        int age_to =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,2)).toInt();
        QString kvalifications =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,3)).toString();
        int kval_from =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,4)).toInt();
        int kval_to =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,5)).toInt();
        QString category =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(row,6)).toString();
        all_categorys.append(category);
        if (kvalifications=="дан")
        {
            query.prepare("UPDATE "+competition_key+" SET Категория=:category WHERE Возраст>=:age_from AND Возраст<=:age_to AND Пол=:gender "
                      "AND Квалификация=:kvalification AND СтепеньКвалификации>=:kval_from AND СтепеньКвалификации<=:kval_to");
            query.bindValue(":category", category);
            query.bindValue(":age_from", age_from);
            query.bindValue(":age_to",age_to);
            query.bindValue(":gender",gender);
            query.bindValue(":kvalification",kvalifications);
            query.bindValue(":kval_from",kval_from);
            query.bindValue(":kval_to",kval_to);

            query.exec();

        } else if(kvalifications=="кю")
        {
            if (kval_from==0)
            {
                query.prepare("UPDATE "+competition_key+" SET Категория=:category WHERE Возраст>=:age_from AND Возраст<=:age_to AND Пол=:gender AND "
                                                        "СтепеньКвалификации=:kval_from");
                query.bindValue(":category", category);
                query.bindValue(":age_from", age_from);
                query.bindValue(":age_to",age_to);
                query.bindValue(":gender",gender);
                query.bindValue(":kvalification",kvalifications);
                query.bindValue(":kval_from",kval_from);
                query.exec();
                if (kval_to==0)
                {
                    return;
                }
                kval_from=11;
            }
            query.prepare("UPDATE "+competition_key+" SET Категория=:category WHERE Возраст>=:age_from AND Возраст<=:age_to AND Пол=:gender "
                      "AND Квалификация=:kvalification AND СтепеньКвалификации<=:kval_from AND СтепеньКвалификации>=:kval_to");

            query.bindValue(":category", category);
            query.bindValue(":age_from", age_from);
            query.bindValue(":age_to",age_to);
            query.bindValue(":gender",gender);
            query.bindValue(":kvalification",kvalifications);
            query.bindValue(":kval_from",kval_from);
            query.bindValue(":kval_to",kval_to);
            query.exec();
        }
    }

    query.prepare("SELECT Категория FROM "+competition_key+" WHERE Категория=:123");
    query.bindValue(":123","-");
    query.exec();

    if (query.next()==true)
    {
        all_categorys.clear();
       QMessageBox::warning(this,"Категории", "Кажется кто-то остался без категории.\nПроверьте участников во вкладке 'Участники'");
       all_members_with_category = false;
    } else {
        all_members_with_category = true;
        QMessageBox::information(this,"Категории", "Участники распределены по категориям.");
}

    ui->categories_box->clear();
    ui->categories_box->addItem("Все");
    ui->categories_box->addItem("Без категории");
    bool empty_cat=false;
    QStringList empty_categ;
    for (int i=0;i<ui->view_all_categorys->model()->rowCount();i++)
    {
        QString categ = ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,6)).toString();

        query.prepare("SELECT Фамилия FROM "+competition_key+" WHERE Категория=:category ");
        query.bindValue(":category",categ);
        query.exec();

        if (query.next() ==false)
        {
            empty_categ.append(categ);
            empty_cat = true;
            for (int j=0;j<7;j++) {
                model_for_categorys->item(i,j)->setBackground(QBrush(QColor("#FFC8C7")));
            }
            } else{
            ui->categories_box->addItem(categ);
            for (int j=0;j<7;j++) {
                model_for_categorys->item(i,j)->setBackground(QBrush(QColor("#ffffff")));
            }
            }


    }

    if (empty_cat==true)
    {
        QString empty = empty_categ.join(";\n ");
        QMessageBox::warning(this,"Пустые категории","Категории в которых нет ни одного участника:\n"+empty);
    }

    set_enabled_to_push_cat_to_tatami();
    repeat_data();
    ui->view_all_categorys->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::on_step_01_clicked()
{
    step = 0.1;
}

void Registration::on_step_025_clicked()
{
    step = 0.25;
}

void Registration::on_step_05_clicked()
{
    step = 0.5;
}

void Registration::on_step_1_clicked() {
    step = 1.0;
}

void Registration::on_start_competition_clicked()
{
    query.exec("SELECT * FROM "+competition_key+" WHERE Категория='-'");
    if (query.first())
    {
        QMessageBox::critical(this,"Участники без категории","Некоторые участники остались без категорий\nПроверьте вкладку участников");
        return;
    }
    if (ui->competition_name->text()==""){
        QMessageBox::critical(this,"Название соревнований","Вы не ввели название соревнований.");
        return;
    }
    if (ui->competition_data->text()==""){
        QMessageBox::critical(this,"Дата соревнований","У соревнований должна быть дата проведения.");
        return;
    }
    if (was_generate==false){
        QMessageBox::critical(this,"Таблица оценок","Пожалуйста, посмотрите таблицу оценок участника.\nПосле начала соревнований, вы не сможете её изменить.");
        return;
    }
    if (ui->judge_main->text()==""){
        QMessageBox::critical(this, "Главный судья.", "У соревнований должен быть главный судья.\nЗаполните поле главного судьи");
        return;
    }
    if (ui->judge_senior->text()==""){
        QMessageBox::critical(this, "Cтарший судья.", "У соревнований должен быть старший судья, занимающийся распределением других судей.\nЗаполните поле старшего судьи");
        return;
    }
    if (ui->judge_main->text()==""){
        QMessageBox::critical(this, "Главный судья.", "У соревнований должен быть главный судья.\nЗаполните поле главного судьи");
        return;
    }
    if (ui->secretary_main->text()==""){
        QMessageBox::critical(this, "Главный секретарь.", "У соревнований должен быть главный секретарь, занимающийся соревнованиями.\nЗаполните поле секретаря");
        return;
    }
    if (ui->judge_main->text()==""){
        QMessageBox::critical(this, "Главный судья.", "У соревнований должен быть главный судья.\nЗаполните поле главного судьи");
        return;
    }
    if (ui->deputy_judge_main->text()==""){
        QMessageBox::critical(this, "Заместитель главного судьи.", "Заполните поле заместителя главного судьи");
        return;
    }
    if (ui->judge_main->text()==""){
        QMessageBox::critical(this, "Главный судья.", "У соревнований должен быть главный судья.\nЗаполните поле главного судьи");
        return;
    }
    if (ui->judge_main->text()==""){
        QMessageBox::critical(this, "Главный судья.", "У соревнований должен быть главный судья.\nЗаполните поле главного судьи");
        return;
    }
    if (ui->number_subjects->value()==0){
        QMessageBox::critical(this, "Количество субъектов.", "Число субъектов не может быть равно нулю");
        return;
    }
    if (ui->subjects->toPlainText()==""){
        QMessageBox::critical(this, "Субъекты.", "Перечислите субъекты, участвующие в соревнованиях");
        return;
    }
    if (ui->number_cities->value()==0){
        QMessageBox::critical(this, "Количество городов.", "Количество городов, участвующих в соревнованиях не может быть равно нулю");
        return;
    }
    if (ui->cities->toPlainText()==""){
        QMessageBox::critical(this, "Города", "Перечислите города, участвующие в соревнованиях");
        return;
    }
    //ДОБАВИТЬ ПРОВЕРКУ ГОРОДОВ И ТАК ДАЛЕЕ


    query.prepare("UPDATE competitions SET НазваниеСоревнований=:name, ДатаПроведения=:date, МестоПроведения=:place, ГлавныйСудья=:main_judge, СтаршийСудья=:oldest_judge, ГлавныйСекретарь=:main_secretary,"
                  "ЗаместительГлавногоСудьи=:deputy_main_judge, КоличествоСубъектов=:number_subjects,Субъекты=:subjects, КоличествоГородов=:number_citys, Города=:citys ,Таблица=:table, Категории=:categorys,Должности=:pos, was_started=true WHERE PK=:key");
    query.bindValue(":name", ui->competition_name->text());
    query.bindValue(":date",ui->competition_data->text());
    query.bindValue(":place",ui->competition_place->text());
    query.bindValue(":main_judge",ui->judge_main->text()+"_"+ui->city_main_judge->text()+"_"+ui->category_main_judge->text()+"_"+ui->kval_main_judge->text());
    query.bindValue(":oldest_judge",ui->judge_senior->text()+"_"+ui->city_judge_senior->text()+"_"+ui->category_jusge_senior->text()+"_"+ui->kval_senior_judge->text());
    query.bindValue(":main_secretary",ui->secretary_main->text()+"_"+ui->city_secretary_main->text()+"_"+ui->category_secretary_main->text()+"_"+ui->kval_main_secretary->text());
    query.bindValue(":deputy_main_judge",ui->deputy_judge_main->text()+"_"+ui->city_deputy_judge->text()+"_"+ui->category_deputy_judge->text()+"_"+ui->kval_deputy_judge->text());
    query.bindValue(":number_subjects",ui->number_subjects->text().toInt());
    query.bindValue(":subjects",ui->subjects->toPlainText());
    query.bindValue(":number_citys",ui->number_cities->text().toInt());
    query.bindValue(":citys",ui->cities->toPlainText());
    query.bindValue(":key",PK);

    QString all_cat;
    Settings->beginGroup("positions");
    QStringList poses;
    for (int i = 0; i < Settings->childKeys().count(); i++) {
        poses.append(Settings->value(QString::number(i)).toString());
    }
    query.bindValue(":pos",poses.join("_"));
    all_categorys.clear();
    for (int i=0;i<ui->view_all_categorys->model()->rowCount();i++)
    {
        QString category =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,6)).toString();
        all_categorys.append(category);
    }
        for (int i=0;i<all_categorys.count();i++)
        {
            if (i+1==all_categorys.count())
            {
                all_cat+=all_categorys.at(i);
                break;
            }
            all_cat+=all_categorys.at(i)+"_";
        }

                  query.bindValue(":categorys",all_cat);


                  QString table_24;
                  QString st;
                  st.setNum(step);
                  QString fr;
                  fr.setNum(from_le);
                  QString to;
                  to.setNum(to_le);
                  table_24=st+"_"+fr+"_"+to;
                  query.bindValue(":table", table_24);

                  query.exec();
                  QStringList *categories = &all_categorys; //передаем указатель на массив категорий
                  emit go_to_competition(categories, competition_key, table,PK);
                  emit open_save_member();
                  was_started=true;
                  this->close();
                  fight->show();
                  model_for_categorys = nullptr;
                  model_for_all_members = nullptr;
                  delete model_for_all_members;
                  delete model_for_categorys;
}

void Registration::on_sorting_box_activated(const QString &arg1)
{
    sorting_box = arg1;
    if (arg1=="Без сортировки")
    {
        ui->asc_desc_box->setEnabled(false);
    } else {
        ui->asc_desc_box->setEnabled(true);
}

    repeat_data();
}

void Registration::on_categories_box_activated(const QString &arg1)
{
//    if  (arg1 !="Все")
//    {
//        ui->teams_box->setEnabled(false);
//    }
    categories_box = arg1;
    repeat_data();
}

void Registration::on_asc_desc_box_activated(const QString &arg1)
{
    if (arg1=="По возрастанию")
    {
        asc_desc=true;
    } else {
        asc_desc=false;
}
    repeat_data();
}

void Registration::closeEvent(QCloseEvent *event)
{
    SaveGeometry();
    if (was_started==true)
    {
        event->accept();
        return;
    }
      QString name_comp = ui->competition_name->text();
      if (name_comp=="")
      {
          QMessageBox::critical(this,"Название соревнований","Для сохранения мероприятия и последующей идентификации \n"
                                                             " введите введите название мероприятия");
          event->ignore();
          return;
      }
      if (ui->view_all_categorys->model() !=nullptr)
      {
          all_categorys.clear();
          for (int i=0;i<ui->view_all_categorys->model()->rowCount();i++)
          {
              QString category =  ui->view_all_categorys->model()->data(ui->view_all_categorys->model()->index(i,6)).toString();
              all_categorys.append(category);
          }
      }
      QString table;
      query.prepare("UPDATE competitions SET НазваниеСоревнований=:name, ДатаПроведения=:date, МестоПроведения=:place, ГлавныйСудья=:main_judge, СтаршийСудья=:oldest_judge, ГлавныйСекретарь=:main_secretary,"
                    "ЗаместительГлавногоСудьи=:deputy_main_judge, КоличествоСубъектов=:number_subjects,Субъекты=:subjects, КоличествоГородов=:number_citys, Города=:citys ,Таблица=:table, Категории=:categorys WHERE PK=:key");
      query.bindValue(":name", ui->competition_name->text());
      query.bindValue(":date",ui->competition_data->text());
      query.bindValue(":place",ui->competition_place->text());
      if (ui->judge_main->text() !="" && ui->city_main_judge->text()!="" && ui->category_main_judge->text()!="" && ui->kval_main_judge->text()!="")
      {
          query.bindValue(":main_judge",ui->judge_main->text()+"_"+ui->city_main_judge->text()+"_"+ui->category_main_judge->text()+"_"+ui->kval_main_judge->text());
      } else {
          query.bindValue(":main_judge","");
      }
      if (ui->secretary_main->text()!="" && ui->city_secretary_main->text() !="" && ui->category_secretary_main->text()!="" && ui->kval_main_secretary->text() !="")
      {
          query.bindValue(":main_secretary",ui->secretary_main->text()+"_"+ui->city_secretary_main->text()+"_"+ui->category_secretary_main->text()+"_"+ui->kval_main_secretary->text());
      } else{
          query.bindValue(":main_secretary","");
      }
      if (ui->judge_senior->text()!="" && ui->city_judge_senior->text() != "" && ui->category_jusge_senior->text() !="" && ui->kval_senior_judge->text() !="")
      {
          query.bindValue(":oldest_judge",ui->judge_senior->text()+"_"+ui->city_judge_senior->text()+"_"+ui->category_jusge_senior->text()+"_"+ui->kval_senior_judge->text());
      } else{
          query.bindValue(":oldest_judge","");
      }
      if (ui->deputy_judge_main->text() != "" && ui->city_deputy_judge->text() != "" && ui->category_deputy_judge->text()!="" && ui->kval_deputy_judge->text()!="")
      {
          query.bindValue(":deputy_main_judge",ui->deputy_judge_main->text()+"_"+ui->city_deputy_judge->text()+"_"+ui->category_deputy_judge->text()+"_"+ui->kval_deputy_judge->text());
      } else{
          query.bindValue(":deputy_main_judge","");
      }
      query.bindValue(":number_subjects",ui->number_subjects->text().toInt());
      query.bindValue(":subjects",ui->subjects->toPlainText());
      query.bindValue(":number_citys",ui->number_cities->text().toInt());
      query.bindValue(":citys",ui->cities->toPlainText());
      query.bindValue(":key",PK);
      if (step !=0.0 && from_le != -1 && to_le != -1)
      {
          QString st;
          st.setNum(step);
          QString fr;
          fr.setNum(from_le);
          QString to;
          to.setNum(to_le);
          table=st+"_"+fr+"_"+to;
          query.bindValue(":table", table);
      } else {
          query.bindValue(":table", "-");
}
      QString all_cat;
      if (!all_categorys.isEmpty())
      {
          for (int i=0;i<all_categorys.count();i++)
          {
              if (i+1==all_categorys.count())
              {
                  all_cat+=all_categorys.at(i);
                  break;
              }
              all_cat+=all_categorys.at(i)+"_";
          }

          query.bindValue(":categorys",all_cat);
      } else{
          query.bindValue(":categorys","-");
      }

      query.exec();

   emit get_open_main();

   event->accept();
}

void Registration::get_open_not_end_comp(QString name_comp){
    query.prepare("SELECT * FROM competitions WHERE НазваниеСоревнований=:name;");
    query.bindValue(":name",name_comp);
    query.exec();
    QString categorys;
    QString table;
    was_started=false;
    while (query.next())
    {
        was_started = query.value(16).toBool();
        ui->competition_name->setText(query.value(0).toString());
        QString date = query.value(1).toString();
        QStringList data = date.split(".");
        ui->competition_data->setDate(QDate(data[2].toInt(),data[1].toInt(),data[0].toInt()));
        ui->competition_place->setText(query.value(2).toString());

        QStringList main_judge;
        if (query.value(3).toString()!="")
        {
        main_judge = query.value(3).toString().split("_");
        ui->judge_main->setText(main_judge[0]);
        ui->city_main_judge->setText(main_judge[1]);
        ui->category_main_judge->setText(main_judge[2]);
        ui->kval_main_judge->setText(main_judge[3]);
        }

        main_judge.clear();
        if  (query.value(4).toString()!="")
        {
            main_judge = query.value(4).toString().split("_");
            ui->judge_senior->setText(main_judge[0]);
            ui->city_judge_senior->setText(main_judge[1]);
            ui->category_jusge_senior->setText(main_judge[2]);
            ui->kval_senior_judge->setText(main_judge[3]);
        }

        main_judge.clear();

        if (query.value(5).toString()!="")
        {
            main_judge = query.value(5).toString().split("_");
             ui->secretary_main->setText(main_judge[0]);
             ui->city_secretary_main->setText(main_judge[1]);
             ui->category_secretary_main->setText(main_judge[2]);
             ui->kval_main_secretary->setText(main_judge[3]);
        }

         main_judge.clear();

         if (query.value(6).toString() !="")
         {
             main_judge = query.value(6).toString().split("_");
             ui->deputy_judge_main->setText(main_judge[0]);
             ui->city_deputy_judge->setText(main_judge[1]);
             ui->category_deputy_judge->setText(main_judge[2]);
             ui->kval_deputy_judge->setText(main_judge[3]);
         }

        ui->number_subjects->setValue(query.value(7).toInt());
        ui->subjects->setText(query.value(8).toString());
        ui->number_cities->setValue(query.value(9).toInt());
        ui->cities->setText(query.value(10).toString());
        categorys = query.value(12).toString();
        table = query.value(11).toString();
        PK = query.value(14).toInt();
        competition_key = "competition_"+query.value(14).toString();
        judges_key = "judges_"+query.value(14).toString();
    }

    if (table != "-")
    {
        QStringList table_d = table.split("_");
        was_generate = true;
        step = table_d[0].toDouble();
        from_le = table_d[1].toInt();
        to_le = table_d[2].toInt();
        ui->from_le->setValue(table_d[1].toInt());
        ui->to_le->setValue(table_d[2].toInt());
        emit recieve_data(step,from_le,to_le);
    }

    if (categorys !="-")
    {

        all_categorys = categorys.split("_");
        for (int i=0;i<all_categorys.count();i++)
        {
            QStringList one_category = all_categorys.at(i).split(",");
            QStandardItem *gender = new QStandardItem(one_category.at(0));
            QStringList age = one_category.at(1).split("-");
            QStandardItem *age_from =  new QStandardItem(age.at(0));
            QStandardItem *age_to = new QStandardItem(age.at(1));
            QStringList kval = one_category.at(3).split("-");
            QStandardItem *kval_from = new QStandardItem(kval.at(0));
            QStandardItem *kval_to = new QStandardItem(kval.at(1));
            QStandardItem *type = new QStandardItem(one_category.at(4));
            QStandardItem *cat = new QStandardItem(all_categorys.at(i));
            ui->categories_box->addItem(all_categorys.at(i));
            model_for_categorys->appendRow(QList<QStandardItem*>()<<gender<<age_from
                                           <<age_to<<type<<kval_from<<kval_to
                                           <<cat);
        }
        ui->view_all_categorys->setModel(model_for_categorys);
        ui->view_all_categorys->resizeRowsToContents();
        ui->view_all_categorys->resizeColumnsToContents();
    }
    repeat_data();
    repeat_judges();
	repeat_teams_box();
    ui->view_all_judges->resizeRowsToContents();
    ui->view_all_categorys->resizeRowsToContents();
}

void Registration::on_get_competiton_data_clicked()
{

    dialog = new Data_dialog();
    connect(dialog, SIGNAL(push_data(QDate*)), this, SLOT(get_data_competition(QDate*)));
    dialog->show();
}

void Registration::get_data_competition(QDate* data)
{

  ui->competition_data->setDate(*data);
}

void Registration::on_add_judge_clicked()
{
    query.prepare("INSERT INTO "+judges_key+" (Фамилия, Имя, Отчество, Город, ТипКвалификации, СтепеньКвалификации, Суд_Категория, Бригада, Должность)"
                                            " VALUES (:last, :first, :patron, :city, :type, :value, :judge_cat, :crew, :post);");
    query.bindValue(":last", ui->last_name_judge->text());
    query.bindValue(":first", ui->fitst_name_judge->text());
    query.bindValue(":patron", ui->patron_name_judge->text());
    query.bindValue(":city",ui->city_judge->text());
    query.bindValue(":type",judges_type_kval);
    query.bindValue(":value", ui->value_kval_judge->value());
    query.bindValue(":judge_cat",ui->judges_category->text());
    query.bindValue(":crew",0);
    query.bindValue(":post", "-");
    
    query.exec();

    repeat_judges();

    ui->last_name_judge->clear();
    ui->fitst_name_judge->clear();
    ui->patron_name_judge->clear();
    ui->city_judge->clear();
    ui->value_kval_judge->clear();
    ui->judges_category->clear();
    ui->view_all_judges->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::on_type_kval_judge_KU_clicked()
{
    judges_type_kval = "кю";
}

void Registration::on_type_kval_judge_DAN_clicked()
{
    judges_type_kval = "дан";
}

void Registration::repeat_judges(){

    model_for_judges->clear();

    model_for_judges->setTable(judges_key);
    model_for_judges->setEditStrategy(QSqlTableModel::OnFieldChange);
    if (categorys1=="Без бригады")
    {
        categorys1 = "0";
    }
    QStringList dop;
    dop<<"Без сортировки"<<"По фамилии"<<"По имени"<<"По бригаде"<<"По городу";
    int index_sorting=0;
    switch (dop.indexOf(sorting)) {
    case (0):{
        break;
    }
    case(1):{
        index_sorting=0;
        break;
    }
    case(2):{
        index_sorting=1;
        break;
    }
    case(3):{
        index_sorting=7;
        break;
    }
    case(4):{
        index_sorting=3;
        break;
    }
    }

    if (sorting=="Без сортировки" && categorys1 !="Бригада"){
       model_for_judges->setFilter("Бригада = '"+categorys1+"'");

    } else if (sorting != "Без сортировки" && categorys1=="Бригада" ) {
        if (asc_desc==true)
        {
            model_for_judges->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            model_for_judges->setSort(index_sorting, Qt::DescendingOrder);
        }
    }
 else if (sorting != "Без сортировки" && categorys1 != "Бригада") {
        model_for_judges->setFilter("Бригада = '"+categorys1+"'");
        if (asc_desc2==true)
        {
            model_for_judges->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            model_for_judges->setSort(index_sorting, Qt::DescendingOrder);
        }
    }
    model_for_judges->select();
    ui->view_all_judges->setModel(model_for_judges);
   ui->view_all_judges->resizeRowsToContents();
   ui->view_all_judges->resizeColumnsToContents();
}

void Registration::on_add_crew_judges_clicked()
{
    int c123 = ui->view_all_judges->selectionModel()->selectedRows().count();
    if (c123<5)
    {
        QMessageBox::warning(this,"Судейская бригада","Судейская бригада не может быть меньше 5 человек \n Выберите 5 человек для составления категории");
        return;
    }
    bool referi = false;
    int bok = 0;
    query.exec("SELECT MAX(Бригада) AS Бригада FROM "+judges_key);
    int brig=-5;
    while (query.next())
    {
        brig = query.value(0).toInt();
    }
    brig+=1;
    for (int i=0;i<c123;i++) {
        int row_selected = ui->view_all_judges->selectionModel()->selectedIndexes().at(i*9).row();
        QString last_name = ui->view_all_judges->model()->data(ui->view_all_judges->model()->index(row_selected,0)).toString();
        QString first_name = ui->view_all_judges->model()->data(ui->view_all_judges->model()->index(row_selected,1)).toString();
        QString patron_name = ui->view_all_judges->model()->data(ui->view_all_judges->model()->index(row_selected,2)).toString();
        QString fio = "Выберите должность для: \n"+ last_name + " " + first_name + " " + patron_name;
        bool ok;
        QString position = QInputDialog::getItem(this,"Должность",fio,positions,0,false, &ok);

        if (!ok)
        {
            return;
        }
        if (position=="Рефери" || position=="рефери")
        {
            referi = true;
        }
        if ( position=="Боковой судья" || position=="боковой судья")
        {
            bok+=1;
        }

        query.prepare("UPDATE "+judges_key+" SET Должность = :position, Бригада=:brig WHERE Фамилия=:last_name AND Имя=:first_name; ");
        query.bindValue(":position",position);
        query.bindValue(":brig",brig);
        query.bindValue(":last_name",last_name);
        query.bindValue(":first_name",first_name);

        query.exec();

    }
    repeat_judges();
    QString brigada;
    brigada.setNum(brig);
    ui->crew_box->addItem(brigada);
    if (referi==false || bok<4)
    {
        QString mess;
        mess.setNum(brig);
        mess = "Кажется вы не сформировали минимальный состав судейской бригады"
                       " \n Состав должен предполагать в себе 1 рефери и 4 боковых судей.\n Проверьте судейскую бригаду номер "+mess;
        QMessageBox::warning(this, "Минимальный состав судейской бригады",mess);
    }
    ui->view_all_judges->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::on_delete_judge_clicked()
{
    if (ui->view_all_judges->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->view_all_judges->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        ui->view_all_judges->model()->removeRow(ui->view_all_judges->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    repeat_judges();
    ui->view_all_judges->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::on_change_position_crew_clicked()
{
    int c123 = ui->view_all_judges->selectionModel()->selectedRows().count();
    if (c123>1 || c123==0)
    {
        QMessageBox::critical(this,"Один","Выберите одного судью для внесения изменений");
        return;
    }
    QStringList mem228;
    mem228<<"Боковой судья"<<"Рефери"<<"Судья при участниках"<<"Судья-секундометрист";
    int row_selected = ui->view_all_judges->selectionModel()->selectedIndexes().at(0).row();
    QString last_name = ui->view_all_judges->model()->data(ui->view_all_judges->model()->index(row_selected,0)).toString();
    QString first_name = ui->view_all_judges->model()->data(ui->view_all_judges->model()->index(row_selected,1)).toString();
    QString patron_name = ui->view_all_judges->model()->data(ui->view_all_judges->model()->index(row_selected,2)).toString();
        QString fio = "Выберите должность для: \n"+ last_name + " " + first_name + " " + patron_name;
        bool ok;
        QString position = QInputDialog::getItem(this,"Должность",fio,mem228,0,false, &ok);

        if (!ok)
        {
            return;
        }
        query.prepare("UPDATE "+judges_key+" SET Должность = :position WHERE Фамилия=:last_name AND Имя=:first_name; ");
        query.bindValue(":position",position);
        query.bindValue(":last_name",last_name);
        query.bindValue(":first_name",first_name);
        query.exec();
        repeat_judges();
        ui->view_all_judges->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="Без сортировки")
    {
        ui->desc_asc_box->setEnabled(false);
    } else {
        ui->desc_asc_box->setEnabled(true);
}
    sorting = arg1;
    repeat_judges();
}

void Registration::on_crew_box_activated(const QString &arg1)
{
    categorys1 = arg1;
    repeat_judges();
}

void Registration::on_desc_asc_box_activated(const QString &arg1)
{
    if (arg1=="По возрастанию")
    {
        asc_desc2=true;
    } else {
        asc_desc2=false;
}
    repeat_judges();
}

void Registration::on_delete_this_member_clicked()
{
    if (ui->view_all_members->model()==nullptr)
    {
        return;
    }
    int count_selected_rows = ui->view_all_members->selectionModel()->selectedRows().count();
    for (int i=0;i<count_selected_rows;i++) {
        ui->view_all_members->model()->removeRow(ui->view_all_members->selectionModel()->selectedRows().at(0).row(), QModelIndex());
    }
    repeat_data();
    repeat_teams_box();
}

void Registration::on_add_custom_member_clicked()
{

    if (ui->last_name_member->text()=="" || ui->first_name_member->text()=="" || gender_member=="" || kval_member==""
            || ui->data_birthday_member->text()=="" || ui->age_member->text()=="" || ui->value_kval_member->text()=="" || ui->trainer_member->text()==""
            || ui->org_member->text()=="" || ui->city_member->text()=="")
    {
        QMessageBox::critical(this,"Не заполнено","Вы забыли что-то заполнить из основных данных.\n Проверьте поля ввода участника");
        return;
    }

    query.prepare("INSERT INTO "+competition_key+" (Фамилия, Имя, Отчество, ДатаРождения, Возраст, Пол, Квалификация, СтепеньКвалификации, Разряд, Руководитель, Организация, Город, Категория)"
                                                 "  VALUES (:last,:first,:patron,:data,:age,:gender,:kval,:value,:razor,:trainer,:org,:city,:cat)");

    query.bindValue(":last",ui->last_name_member->text());

    query.bindValue(":first",ui->first_name_member->text());

    query.bindValue(":patron",ui->patron_name_member->text());

    query.bindValue(":data",ui->data_birthday_member->text());

    query.bindValue(":age",ui->age_member->text());

    query.bindValue(":gender",gender_member);

    query.bindValue(":kval",kval_member);

    query.bindValue(":value",ui->value_kval_member->text());

    query.bindValue(":razor",ui->stepen_member->text());

    query.bindValue(":trainer",ui->trainer_member->text());

    query.bindValue(":org",ui->org_member->text());

    query.bindValue(":city",ui->city_member->text());
    query.bindValue(":cat","-");

    query.exec(); //YOURSELF

    repeat_data();

    ui->last_name_member->clear();
    ui->first_name_member->clear();
    ui->patron_name_member->clear();
    ui->data_birthday_member->clear();
    ui->age_member->clear();
    gender_member="";
    kval_member="";
    ui->value_kval_member->clear();
    ui->stepen_member->clear();
    ui->trainer_member->clear();
    ui->org_member->clear();
    ui->city_member->clear();
    all_members_with_category = false;
    set_enabled_to_push_cat_to_tatami();
    repeat_teams_box();
}

void Registration::on_gender_M_member_clicked()
{
    gender_member = "м";
}

void Registration::on_gender_J_member_clicked()
{
    gender_member = "ж";
}

void Registration::on_KU_member_clicked()
{
    kval_member = "кю";
}

void Registration::on_Dan_member_clicked()
{
    kval_member = "дан";
}

void Registration::on_create_category_clicked()
{
    if (categories_box=="Все" || categories_box=="Без категории")
    {
        QMessageBox::critical(this,"Создание категории в формате doc","Для создания категории в бумажном формате \n выберите категорию");
        return;
    }
    QAxObject *WordApp = new QAxObject("Word.Application");
    QAxObject *WordDoc = WordApp->querySubObject("Documents()");
    QAxObject *NewDoc = WordDoc->querySubObject("Add()");


    QAxObject *page_setup = NewDoc->querySubObject("PageSetup()");
    page_setup->setProperty("LeftMargin",35);
    page_setup->setProperty("RightMargin",30);
    page_setup->setProperty("TopMargin",40);
    page_setup->setProperty("BottomMargin",40);

    QAxObject *main_table = NewDoc->querySubObject("Range()");
    main_table->dynamicCall("SetRange(int,int)",1,100);
    main_table->setProperty("Text",categories_box);
    QAxObject *font = main_table->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    QAxObject *par = main_table->querySubObject("ParagraphFormat");
    par->setProperty("Alignment","wdAlignParagraphCenter");

    query.prepare("SELECT COUNT(*) FROM "+competition_key+" WHERE Категория=:cat");
    query.bindValue(":cat",categories_box);
    query.exec();

    int count_cat=0;
    while (query.next())
    {
        count_cat = query.value(0).toInt();
    }
   QAxObject *tables = NewDoc->querySubObject("Tables()");
   QAxObject *range_table = NewDoc->querySubObject("Range()");
   int end_range = 101+count_cat*100;
   int start_range = 101;
   range_table->dynamicCall("SetRange(int,int)",start_range,end_range);
   QAxObject *category_table = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_table->asVariant(), count_cat+1, 13, 1, 2);

   QAxObject *cell = category_table->querySubObject("Cell(Row,Column)",1,1);
   QAxObject *data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Фамилия");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,2);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Имя");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,3);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Отчество");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,4);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Город");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,5);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Тренер");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,6);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","1");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,7);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","2");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,8);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","3");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,9);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","4");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,10);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","5");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,11);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Сумма");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,12);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Мин");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,13);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Макс");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");


   for (int row=0;row<count_cat;row++)
   {
       cell = category_table->querySubObject("Cell(Row,Column)",row+2,1); //LAST
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",ui->view_all_members->model()->data(ui->view_all_members->model()->index(row,0)).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row+2,2); //FIRST
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",ui->view_all_members->model()->data(ui->view_all_members->model()->index(row,1)).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row+2,3); //PATRON
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",ui->view_all_members->model()->data(ui->view_all_members->model()->index(row,2)).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row+2,4); //CITY
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",ui->view_all_members->model()->data(ui->view_all_members->model()->index(row,11)).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row+2,5); //TRAINER
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",ui->view_all_members->model()->data(ui->view_all_members->model()->index(row,9)).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

   }

   WordApp->setProperty("Visible",true);
}

void Registration::check_out_members()
{
    query.exec("SELECT COUNT(*) FROM "+competition_key);
    int count=0;
    while(query.next())
    {
        count = query.value(0).toInt();
    }
    if (count==10)
    {
        QMessageBox::critical(this,"Пробная версия","В пробной версии может быть не более 10 участников\n Будут удалены случайные участники");
        return;
    } else if (count<10) {
        return;
}
    query.exec("DELETE  FROM "+competition_key+" WHERE Фамилия IN (SELECT Фамилия FROM "+competition_key+" ORDER BY RANDOM() LIMIT 1)");
    check_out_members();


}

void Registration::on_push_category_to_tatami_clicked()
{
    QMessageBox::StandardButton baton = QMessageBox::question(this,"Разделение категорий на отдельное татами","Начать разделение категорий?\n"
                                                                                                              "После начала разденеия категорий, распределять новых участников по категориям будет нельзя!!!", QMessageBox::Yes | QMessageBox::No);
    if (baton==QMessageBox::No)
    {
        return;

    } else if (baton==QMessageBox::Yes) {
        DialogWithCategory *dialogCategory = new DialogWithCategory(competition_key);

        if (dialogCategory->exec()==QDialog::Accepted)
        {
            QString save_file_route = QFileDialog::getSaveFileName(this,"Сохранение категорий","Категории","*.json");
            if (save_file_route==""){
                return;
            }

            QStandardItemModel *model = dialogCategory->return_model();
            QJsonObject objectMainJson;
            QJsonObject all_categories;

            for(int i=0;i<model->rowCount();i++)
            {
                QString category = model->data(model->index(i,0)).toString();
                QJsonObject categoryJson;
                query.prepare("SELECT * FROM "+competition_key+" WHERE Категория=:category");
                query.bindValue(":category",category);
                query.exec();
                    int index = 1;
                while (query.next()) {
                    QJsonObject member;
                    member.insert("LastName",query.value(0).toString());
                    member.insert("FirstName",query.value(1).toString());
                    member.insert("PatronName",query.value(2).toString());
                    member.insert("Data",query.value(3).toString());
                    member.insert("Age",query.value(4).toString());
                    member.insert("Gender",query.value(5).toString());
                    member.insert("TypeKval",query.value(6).toString());
                    member.insert("PosKval",query.value(7).toString());
                    member.insert("Razor",query.value(8).toString());
                    member.insert("Trainer",query.value(9).toString());
                    member.insert("Organization",query.value(10).toString());
                    member.insert("City", query.value(11).toString());
                    categoryJson.insert(QString::number(index),member);
                    index++;
                }
                all_categories.insert(category,categoryJson);
                query.prepare("DELETE FROM "+competition_key+" WHERE Категория=:cat");
                query.bindValue(":cat",category);
                query.exec();

            }
            objectMainJson.insert("CATEGORIES",all_categories);
            query.prepare("SELECT Таблица FROM competitions WHERE PK=:pk");
            query.bindValue(":pk",PK);
            query.exec();
            while (query.next())
            {
                objectMainJson.insert("Table",query.value(0).toString());
            }

            Settings->beginGroup("causes");
            QJsonObject exclude_causes;
            QStringList childKeys = Settings->childKeys();
            for (int i=0; i<childKeys.count();i++)
            {
                exclude_causes.insert(childKeys.at(i),Settings->value(childKeys.at(i)).toString());
            }
            objectMainJson.insert("causes",exclude_causes);
            Settings->endGroup();
            objectMainJson.insert("WHAT_THIS","ITSME");
            objectMainJson.insert("WAS_OPENED","FALSE");
            QFileInfo info(save_file_route);
            QDir::setCurrent(info.path());

            QFile Json_file(save_file_route);

            if(!Json_file.open(QIODevice::WriteOnly))
            {
                return;
            }

            Json_file.write(QJsonDocument(objectMainJson).toJson(QJsonDocument::Indented));
            Json_file.close();
			QMessageBox::information(this,"Категории сохранены.","Категории были сохранены.\nНе теряйте файл категорий, восстановить его будет нельзя\n"
																 "Далее запустите приложение на другом татами, нажмите кнопку 'Режим дополнительного татами' и выберите этот файл");
        }
        ui->push_category_to_members->setEnabled(false);
        delete dialogCategory;
    }
    ui->view_all_categorys->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Registration::set_enabled_to_push_cat_to_tatami()
{
    if (all_members_with_category==true && was_generate==true)
    {
        ui->push_category_to_tatami->setEnabled(true);
    }else{
        ui->push_category_to_tatami->setEnabled(false);
    }
}

void Registration::on_teams_box_activated(const QString &arg1)
{
//    if (arg1 != "Все команды")
//    {
//        ui->categories_box->setEnabled(false);
//    }
    teams = arg1;
    repeat_data();
}

void Registration::repeat_teams_box()
{
    ui->teams_box->clear();
    ui->teams_box->addItem("Все команды");
    query.prepare("SELECT DISTINCT(Организация) FROM "+competition_key);
    query.exec();
    while (query.next())
    {
        ui->teams_box->addItem(query.value(0).toString());
    }
}

void Registration::SaveGeometry()
{
    Settings->beginGroup("Geometry");
    Settings->setValue("GeometryRegistration",geometry());
    Settings->endGroup();
}
