#include "fight.h"
#include "ui_fight.h"
#include "QDebug"
#include "QSqlTableModel"
#include "registration.h"
#include "QSql"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "QSqlError"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "QJsonArray"
#include "table.h"
Fight::Fight(bool categ_mod, QSettings* pyk,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fight)
{
    ui->setupUi(this);
    Settings = pyk;

    Settings->beginGroup("Geometry");
    setGeometry(Settings->value("GeometryFight",QRect(500,500,600,600)).toRect());
    Settings->endGroup();

    ui->view_fighters->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    Settings->beginGroup("Font");
    int size = Settings->value("Size",12).toInt();
    Settings->endGroup();

    ui->tabWidget->setFont(QFont("Calibri",size));
    ui->tab->setFont(QFont("Calibri",size));
    ui->tab_2->setFont(QFont("Calibri",size));
    ui->tab_3->setFont(QFont("Calibri",size));
    ui->tab_4->setFont(QFont("Calibri",size));
    //TAB_1
    ui->end_competition->setFont(QFont("Calibri",size));

    //TAB_2
    ui->categories_box->setFont(QFont("Calibri",size));
    ui->desc_asc_box->setFont(QFont("Calibri",size));
    ui->history_member->setFont(QFont("Calibri",size));
    ui->sorting_box->setFont(QFont("Calibri",size));
    ui->view_members->setFont(QFont("Calibri",size));
    //TAB_3
    ui->categories->setFont(QFont("Calibri",size));
    ui->count_member->setFont(QFont("Calibri",size));
    ui->end_category->setFont(QFont("Calibri",size));
    ui->end_loop->setFont(QFont("Calibri",size));
    ui->label_FIO->setFont(QFont("Calibri",size));
    ui->out_member->setFont(QFont("Calibri",size));
    ui->start_loop->setFont(QFont("Calibri",size));
    ui->view_fighters->setFont(QFont("Calibri",size));
    //TAB_4
    ui->create_ended_category->setFont(QFont("Calibri",size));
    ui->load_ended_category->setFont(QFont("Calibri",size));
    if(categ_mod==false)
    {
        Settings->beginGroup("causes");
        QStringList keys = Settings->childKeys();
        for (int i=0;i<keys.count();i++) {
            list_causes.append(Settings->value(keys.at(i)).toString());
            causes.insert(keys.at(i).toInt(),Settings->value(keys.at(i)).toString());
        }
        Settings->endGroup();
    }
    model_fighters = new QStandardItemModel;
    model_fighters->setHorizontalHeaderLabels(QStringList()<<"Фамилия"<<"Имя"<<"Отчество"<<"Дата Рождения"<<"Возраст"<<"Тренер"<<"Организация"
                                              <<"Город"<<"Судья_1"<<"Судья_2"<<"Судья_3"<<"Судья_4"<<"Судья_5"<<"Сред_Балл"<<"Мин_Балл"<<"Макс_Балл");
    model_for_fight = new QSqlTableModel(this,db);
    history_fighter = new QStandardItemModel;
    history_fighter->setHorizontalHeaderLabels(QStringList()<<"Сумма"<<"Мин_Балл"<<"Макс_Балл"<<"Судья_1"
                                               <<"Судья_2"<<"Судья_3"<<"Судья_4"<<"Судья_5");
}

Fight::~Fight()
{
    delete ui;
}

void Fight::start_competition(QStringList *categories, QString main_key, Table *s1, int Perf){
    QStringList categ = *categories;
    table = s1;
    PK= Perf;
    connect(table, SIGNAL(push_count_kata(double*,double,double,double)), this, SLOT(get_count_kata(double*,double,double,double)));

    competition_key = main_key;
    for (int i = 0;i<categ.count();i++){
        query.prepare("SELECT COUNT(*) FROM "+competition_key+" WHERE Категория=:categ");
        query.bindValue(":categ",categ.at(i));
        query.exec();
        int count=0;
        while (query.next())
        {
            count = query.value(0).toInt();
        }
        if (count>0)
        {
            ui->categories_box->addItem(categ.at(i));
            query.prepare("SELECT COUNT(*) FROM "+competition_key+" WHERE Категория=:categ AND Место=:place");
            query.bindValue(":categ",categ.at(i));
            query.bindValue(":place",0);
            query.exec();
            while (query.next())
            {
                count = query.value(0).toInt();
            }
            if (count>0)
            {
                ui->categories->addItem(categ.at(i));
            }
        }
    }
    ui->create_ended_category->setEnabled(false);
    repeat_view_fighters();
}

void Fight::on_categories_currentIndexChanged(const QString &arg1)
{

    model_fighters->removeRows(0,model_fighters->rowCount());
    query.prepare("SELECT * FROM "+competition_key+" WHERE Категория = :category AND Место = 0;");
    query.bindValue(":category", arg1);
    query.exec();
    category = arg1;
    while (query.next())
    {
        QStandardItem *L_name = new QStandardItem(query.value(0).toString());
        QStandardItem *F_name = new QStandardItem(query.value(1).toString());
        QStandardItem *P_name = new QStandardItem(query.value(2).toString());
        QStandardItem *data = new QStandardItem(query.value(3).toString());
        QStandardItem *age = new QStandardItem(query.value(4).toString());
        QStandardItem *trainer = new QStandardItem(query.value(9).toString());
        QStandardItem *org = new QStandardItem(query.value(10).toString());
        QStandardItem *city = new QStandardItem(query.value(11).toString());



        model_fighters->appendRow(QList<QStandardItem*>()<<L_name<<F_name<<P_name<<data<<age<<trainer<<org<<city<<new QStandardItem("0")<<
                                  new QStandardItem("0")<<new QStandardItem("0")<<new QStandardItem("0")<<new QStandardItem("0")<<new QStandardItem("0")<<
                                  new QStandardItem("0")<<new QStandardItem("0"));
    }
    ui->view_fighters->setModel(model_fighters);
    ui->view_fighters->resizeColumnsToContents();
    ui->view_fighters->resizeRowsToContents();

    ui->view_fighters->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Fight::on_start_loop_clicked()
{
    ui->end_loop->setEnabled(true);
    ui->end_category->setEnabled(true);
    ui->count_member->setEnabled(true);
    ui->categories->setEnabled(false);
    ui->start_loop->setEnabled(false);
    ui->out_member->setEnabled(true);
}

void Fight::on_end_loop_clicked()
{
    bool ok_circle;
    int  count = ui->view_fighters->model()->rowCount();
    for (int i = 0;i<count;i++) {

        if (model_fighters->item(i,8)->background().color().toRgb() != QColor("#CBFFC7").toRgb() && model_fighters->item(i,8)->background().color().toRgb() != QColor("#FFC7C7").toRgb())
        {
            QMessageBox::critical(this,"Кто-то не прошёл круг.","Один или несколько участников не выступили.\n Проверьте таблицу.");
            return;
        }
    }
    int next_tour;
    if (ui->view_fighters->model()->rowCount()<=3)
    {
        next_tour = ui->view_fighters->model()->rowCount();
    } else {
        next_tour =  QInputDialog::getInt(this, "Окончание круга.","Сколько человек пройдет в следующий круг?",2,2,count,1,&ok_circle);
        if (!ok_circle)
        {
            return;
        }
}

    int last_place=-1;
    query.prepare("SELECT MIN(Место) AS Место FROM "+competition_key+" WHERE Категория = :category;");
    query.bindValue(":category", category);
    query.exec();
    while (query.next())
    {
        last_place = query.value(0).toInt();
    }
    if (last_place==0)
    {
        last_place=count;
    } else {
        last_place-=1;
}

    for (int i=count-1;i>=0;i--) {
        double middle_data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,13)).toDouble();
        if (middle_data<0)
        {
            QString last_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,0)).toString();
            QString first_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,1)).toString();
            QString patronymic_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,2)).toString();
            QString data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,3)).toString();

            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND Отчество=:patronymic_name AND "
                                                    "ДатаРождения=:data AND Категория=:category;");
            query.bindValue(":place",last_place);
            query.bindValue(":first_name",first_name);
            query.bindValue(":last_name",last_name);
            query.bindValue(":patronymic_name", patronymic_name);
            query.bindValue(":data", data);
            query.bindValue(":category",category);

            query.exec();
            last_place-=1;
            ui->view_fighters->model()->removeRow(i);
        }
    }

    count = ui->view_fighters->model()->rowCount();
    if (count>next_tour)
    {
        double middle_data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(next_tour-1,13)).toDouble();
        double min_data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(next_tour-1,14)).toDouble();
        double max_data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(next_tour-1,15)).toDouble();


        for (int i=count-1;i>=0;i--)
        {

            double mid_last = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,13)).toDouble();
            double min_last = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,14)).toDouble();
            double max_last = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,15)).toDouble();
            if (mid_last == middle_data && min_last == min_data && max_data == max_last)
            {
                break;
            }
            else {
                QString last_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,0)).toString();
                QString first_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,1)).toString();
                QString patronymic_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,2)).toString();
                QString data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,3)).toString();

                query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND Отчество=:patronymic_name AND "
                                                        "ДатаРождения=:data AND Категория=:category;");
                query.bindValue(":place",last_place);
                query.bindValue(":first_name",first_name);
                query.bindValue(":last_name",last_name);
                query.bindValue(":patronymic_name", patronymic_name);
                query.bindValue(":data", data);
                query.bindValue(":category",category);

                query.exec();
                last_place-=1;
            }
        }
    }
    save_data_count_member();
    ui->end_loop->setEnabled(false);
    ui->end_category->setEnabled(false);
    ui->count_member->setEnabled(false);
    ui->categories->setEnabled(true);
    ui->start_loop->setEnabled(true);
    ui->out_member->setEnabled(false);
    on_categories_currentIndexChanged(category);
    repeat_view_fighters();
    ui->label_FIO->setText("Фамилия Имя Отчество");
}

void Fight::on_count_member_clicked()
{
    last_name =  ui->view_fighters->model()->data(ui->view_fighters->model()->index(ui->view_fighters->currentIndex().row(), 0)).toString();

    if (last_name == "" || ui->label_FIO->text()=="Фамилия Имя Отчество")
    {
        QMessageBox::critical(this,"Участник для оценки", "Выберите участника для оценки\nКликните по его клетке в таблице или выберите полную строку");
        return;
    }

   table->show();
}

void Fight::get_count_kata(double* all_judge,double min_ball,double max_bal,double middle_ball)
{
    double j_1 = *all_judge;
    double j_2= *(all_judge+1);
    double j_3= *(all_judge+2);
    double j_4= *(all_judge+3);
    double j_5= *(all_judge+4);

    for (int i=0;i<16;i++) {
        model_fighters->item(selected_member,i)->setBackground(QBrush(QColor("#CBFFC7")));
    }
    model_fighters->item(selected_member,8)->setData(j_1, Qt::DisplayRole);
    model_fighters->item(selected_member,9)->setData(j_2, Qt::DisplayRole);
    model_fighters->item(selected_member,10)->setData(j_3, Qt::DisplayRole);
    model_fighters->item(selected_member,11)->setData(j_4, Qt::DisplayRole);
    model_fighters->item(selected_member,12)->setData(j_5, Qt::DisplayRole);

    model_fighters->item(selected_member,13)->setData(middle_ball, Qt::DisplayRole);
    model_fighters->item(selected_member,14)->setData(min_ball, Qt::DisplayRole);
    model_fighters->item(selected_member,15)->setData(max_bal, Qt::DisplayRole);

    ui->view_fighters->setModel(model_fighters);

        int  count = ui->view_fighters->model()->rowCount();
        if (count==1)
        {
            return;
        }


        QList<QStandardItem *> list_count =model_fighters->takeRow(selected_member);
        for (int i=0;i<count;i++) {
            double middle_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,13)).toDouble();
            double min_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,14)).toDouble();
            double max_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,15)).toDouble();

            if (middle_ball>middle_this_member)
            {
                model_fighters->insertRow(i, list_count);
                last_name="";
                ui->label_FIO->setText("Фамилия Имя Отчество");
                return;
            }
            if (middle_ball==middle_this_member)
            {
                if (min_ball>min_this_member)
                {
                    model_fighters->insertRow(i,list_count);
                    last_name="";
                    ui->label_FIO->setText("Фамилия Имя Отчество");
                    return;
                }
                if (min_ball==min_this_member)
                {
                    if (max_bal>max_this_member)
                    {
                        model_fighters->insertRow(i,list_count);
                        last_name="";
                        ui->label_FIO->setText("Фамилия Имя Отчество");
                        return;
                    }
                }
            }
            ui->view_fighters->resizeRowsToContents();
        }
        model_fighters->insertRow(ui->view_fighters->model()->rowCount(),list_count);
        last_name="";
        ui->label_FIO->setText("Фамилия Имя Отчество");

        ui->view_fighters->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Fight::categories_mod(QJsonDocument *doc_pyk)
{
    this->show();
    QJsonDocument doc = *doc_pyk;
    competition_key = "categories_mode";
    QStringList table_qs = QJsonValue(doc.object().value("Table")).toString().split("_");
    double step = table_qs[0].toDouble();
    int from_le = table_qs[1].toInt();
    int to_le = table_qs[2].toInt();
    Settings->beginGroup("TABLE_ForTatami");
    Settings->setValue("Step_save",QString::number(step));
    Settings->setValue("From_save",QString::number(from_le));
    Settings->setValue("To_save",QString::number(to_le));
    Settings->endGroup();
    table = new Table();
    connect(this,SIGNAL(open_save_member()), table,SLOT(open_count()));
    connect(table, SIGNAL(push_count_kata(double*,double,double,double)), this, SLOT(get_count_kata(double*,double,double,double)));
    connect(this, SIGNAL(recieve_data(double , int , int )), table, SLOT(get_data(double , int , int )));

    emit recieve_data(step,from_le,to_le);
    emit open_save_member();


    QJsonObject causes_object = QJsonValue(doc.object().value("causes")).toObject();
    QStringList keys_causes = causes_object.keys();
    Settings->beginGroup("ForTatami");
    QStringList OLD_keys = Settings->childKeys();
    for (int j=0;j<OLD_keys.count();j++)
    {
        Settings->remove(OLD_keys[j]);
    }
    for (int i=0;i<keys_causes.count();i++)
    {

        Settings->setValue(keys_causes[i],causes_object.value(keys_causes[i]).toString());
        list_causes.append(causes_object.value(keys_causes[i]).toString());
        causes.insert(keys_causes[i].toInt(),causes_object.value(keys_causes[i]).toString());
    }
    Settings->endGroup();
    QJsonObject categories = QJsonValue(doc.object().value("CATEGORIES")).toObject();
    QStringList keys_cat = categories.keys();
    for (int i=0;i<keys_cat.count();i++)
    {
        ui->categories->addItem(keys_cat[i]);
        ui->categories_box->addItem(keys_cat[i]);
        QJsonObject categ = QJsonValue(categories.value(keys_cat[i])).toObject();
        QStringList members = categ.keys();
        for (int j=0;j<members.count();j++) {

            QJsonObject one_member = QJsonValue(categ.value(members[j])).toObject();

            QString last_name = QJsonValue(one_member.value("LastName")).toString();
            QString first_name = QJsonValue(one_member.value("FirstName")).toString();
            QString patron_name = QJsonValue(one_member.value("PatronName")).toString();
            QString gender = QJsonValue(one_member.value("Gender")).toString();
            QString data = QJsonValue(one_member.value("Data")).toString();
            QString org = QJsonValue(one_member.value("Organization")).toString();
            QString TypeKval = QJsonValue(one_member.value("TypeKval")).toString();
            QString razryad = QJsonValue(one_member.value("Razor")).toString();
            QString PosKval = QJsonValue(one_member.value("PosKval")).toString();
            QString Trainer = QJsonValue(one_member.value("Trainer")).toString();
            QString city = QJsonValue(one_member.value("City")).toString();
            QString age = QJsonValue(one_member.value("Age")).toString();

            query.prepare("INSERT INTO categories_mode(Фамилия, Имя, Отчество, ДатаРождения, Возраст, Пол, Квалификация, СтепеньКвалификации, Разряд, Руководитель, Организация, Город, Категория) "
                          "VALUES(:last, :first, :patron, :data, :age, :gender, :typeKval, :ValueKval, :razor, :trainer, :org, :city, :category)");
            query.bindValue(":last",last_name);
            query.bindValue(":first",first_name);
            query.bindValue(":patron",patron_name);
            query.bindValue(":data",data);
            query.bindValue(":age",age);
            query.bindValue(":gender",gender);
            query.bindValue(":typeKval",TypeKval);
            query.bindValue(":ValueKval",PosKval);
            query.bindValue(":razor",razryad);
            query.bindValue(":trainer",Trainer);
            query.bindValue(":org",org);
            query.bindValue(":city",city);
            query.bindValue(":category",keys_cat[i]);

            query.exec();

        }
    }
    on_categories_currentIndexChanged(ui->categories->currentText());
    repeat_view_fighters();
    ui->end_competition->setEnabled(false);
    ui->load_ended_category->setEnabled(false);
}

void Fight::not_new_cat_mode()
{
    this->show();
    competition_key = "categories_mode";

    QStringList list_cat;
    sup_query.exec("SELECT DISTINCT(Категория) FROM categories_mode");
    while(sup_query.next())
    {
        QString val = sup_query.value(0).toString();
        list_cat.append(val);
        ui->categories_box->addItem(val);
    }
    sup_query.exec("SELECT DISTINCT(Категория) FROM categories_mode WHERE Место=0");
    while(sup_query.next())
    {
        QString val = sup_query.value(0).toString();
        ui->categories->addItem(val);
    }
    Settings->beginGroup("TABLE_ForTatami");
    double step = Settings->value("Step_save").toDouble();
    int from_le  = Settings->value("From_save").toInt();
    int to_le  = Settings->value("To_save").toInt();
    Settings->endGroup();
    repeat_view_fighters();
    ui->end_competition->setEnabled(false);
    ui->load_ended_category->setEnabled(false);

    Settings->beginGroup("ForTatami");
    QStringList keys = Settings->childKeys();
    for (int i=0;i<keys.count();i++) {
        list_causes.append(Settings->value(keys.at(i)).toString());
        causes.insert(keys.at(i).toInt(),Settings->value(keys.at(i)).toString());
    }
    Settings->endGroup();

    table = new Table();
    connect(this,SIGNAL(open_save_member()), table,SLOT(open_count()));
    connect(table, SIGNAL(push_count_kata(double*,double,double,double)), this, SLOT(get_count_kata(double*,double,double,double)));
    connect(this, SIGNAL(recieve_data(double , int , int )), table, SLOT(get_data(double , int , int )));

    emit recieve_data(step,from_le,to_le);
    emit open_save_member();
}

void Fight::closeEvent(QCloseEvent *event)
{
    SaveGeometry();
    event->accept();
}

void Fight::SaveGeometry()
{
    Settings->beginGroup("Geometry");
    Settings->setValue("GeometryFight",geometry());
    Settings->endGroup();
}

void Fight::on_view_fighters_clicked(const QModelIndex &index)
{
    selected_member = index.row();
    QString Lname = ui->view_fighters->model()->data(ui->view_fighters->model()->index(selected_member,0)).toString();
    QString Fname = ui->view_fighters->model()->data(ui->view_fighters->model()->index(selected_member,1)).toString();
    QString Pname = ui->view_fighters->model()->data(ui->view_fighters->model()->index(selected_member,2)).toString();
    ui->label_FIO->setText(Lname+" "+Fname+" "+Pname);
    sel_mem  = index;
}

void Fight::on_out_member_clicked()
{
    last_name =  ui->view_fighters->model()->data(ui->view_fighters->model()->index(ui->view_fighters->currentIndex().row(), 0)).toString();

    if (last_name == "" || ui->label_FIO->text()=="Фамилия Имя Отчество")
    {

        QMessageBox::critical(this,"Участник для оценки", "Выберите участника для исключения\nКликните по его клетке в таблице или выберите полную строку");
        return;
    }
    bool ok;
    QString key = QInputDialog::getItem(this,"Причина исключения","Выберите причину исключения участника",list_causes,0,false,&ok);
    if (!ok)
    {
        return;
    }
    int index = causes.key(key);
    for (int i=0;i<16;i++) {
        model_fighters->item(selected_member,i)->setBackground(QBrush(QColor("#FFC7C7")));
    }
    for  (int i=8;i<16;i++)
    {
        model_fighters->item(selected_member,i)->setData(index, Qt::DisplayRole);
    }
    QList<QStandardItem*> list = model_fighters->takeRow(selected_member);
   int  count = ui->view_fighters->model()->rowCount();
    model_fighters->insertRow(count,list);
    ui->view_fighters->resizeRowsToContents();
    ui->view_fighters->resizeColumnsToContents();

    ui->view_fighters->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Fight::on_end_category_clicked()
{
        int  c229 = ui->view_fighters->model()->rowCount();
    for (int i = 0;i<c229;i++) {

        if (model_fighters->item(i,8)->background().color().toRgb() != QColor("#CBFFC7").toRgb() && model_fighters->item(i,8)->background().color().toRgb() != QColor("#FFC7C7").toRgb())
        {
            QMessageBox::critical(this,"Кто-то не прошёл круг.","Один или несколько участников не выступили.\n Проверьте таблицу.");
            return;
        }
    }
    QString winners="Категория завершена! \n";
    QMessageBox::StandardButton quest =  QMessageBox::question(this,"Завершение категории","Завершить категорию и расставить места участникам?", QMessageBox::Yes | QMessageBox::No);
    if (quest == QMessageBox::No)
    {
        return;
    } else if (quest==QMessageBox::Yes) {

        query.prepare("SELECT Фамилия FROM "+competition_key+" WHERE Макс_Балл > 0 AND Категория=:category");
        query.bindValue(":category",category);
        query.exec();
        if (query.first())
        {
            second_tour=true;
        } else{
            second_tour=false;
        }
        save_data_count_member();
        //УДАЛЯЕМ ТЕХ, КОГО ИСКЛЮЧИЛИ ЧТОБЫ НЕ ПОПАЛИ В АЛГОРИТМ
        int cat = ui->view_fighters->model()->rowCount();
        int crit = -1;
        for(int i=0;i<cat;i++)
        {
            double middle_ball = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,13)).toDouble();
            if (middle_ball<0)
            {
                if (crit==-1)
                {
                    crit = i;
                }
                query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND "
                                                       "ДатаРождения=:data AND Категория=:category;");
                QString last_name_this_member= ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,0)).toString();
                QString first_name_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,1)).toString();
                QString data_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,3)).toString();

                query.bindValue(":place",i+1);
                query.bindValue(":first_name",first_name_this_member);
                query.bindValue(":last_name",last_name_this_member);
                query.bindValue(":data", data_this_member);
                query.bindValue(":category",category);
                query.exec();
            }
        }
       for (int z=crit;z<cat;z++)
       {
           ui->view_fighters->model()->removeRow(crit);
         }


        //ALGORITM CHECKING
        bool was_first_add = false;
        QList<QList<int>> crying_members;
        QList<int> second;
        int add_k = 0;
        int indeh=-1;
        int save_count = ui->view_fighters->model()->rowCount();
        if (save_count>=5)
        {
            indeh = 4;
        } else{
            indeh = save_count-1;
        }
        bool last_place_check = false;
        for(int row=0;row<indeh;row++)
        {
            double sum_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row,13)).toDouble();
            double min_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row,14)).toDouble();
            double max_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row,15)).toDouble();


                double sum_next_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row+1,13)).toDouble();
                double min_next_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row+1,14)).toDouble();
                double max_next_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row+1,15)).toDouble();

                QString last_name_next_member= ui->view_fighters->model()->data(ui->view_fighters->model()->index(1+row,0)).toString();
                QString first_name_next_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(1+row,1)).toString();
                QString data_next_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(1+row,3)).toString();


                QString last_name_this_member= ui->view_fighters->model()->data(ui->view_fighters->model()->index(row,0)).toString();
                QString first_name_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row,1)).toString();
                QString data_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(row,3)).toString();
                if (sum_this_member == sum_next_member && min_this_member == min_next_member && max_this_member == max_next_member)
                {
                    last_place_check=true;
                    if (was_first_add==false)
                    {

                        query.prepare("SELECT rowid FROM "+competition_key+" WHERE Фамилия=:last AND Имя=:first AND ДатаРождения=:data");
                        query.bindValue(":last",last_name_this_member);
                        query.bindValue(":first",first_name_this_member);
                        query.bindValue(":data",data_this_member);
                        query.exec();
                        while(query.next())
                        {
                            second.append(query.value(0).toInt());
                        }
                    }
                    query.prepare("SELECT rowid FROM "+competition_key+" WHERE Фамилия=:last AND Имя=:first AND ДатаРождения=:data");
                    query.bindValue(":last",last_name_next_member);
                    query.bindValue(":first",first_name_next_member);
                    query.bindValue(":data",data_next_member);
                    query.exec();
                    while(query.next())
                    {
                        second.append(query.value(0).toInt());
                    }
                    was_first_add= true;
                    add_k=0;
                } else{
                    last_place_check = false;
                    if (row==0)
                    {
                        query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND "
                                                               "ДатаРождения=:data AND Категория=:category;");
                        if (second_tour==false)
                        {
                            query.bindValue(":place",1);
                        } else{
                            int place = check_the_place();
                            query.bindValue(":place",place);
                        }
                        query.bindValue(":first_name",first_name_this_member);
                        query.bindValue(":last_name",last_name_this_member);
                        query.bindValue(":data", data_this_member);
                        query.bindValue(":category",category);
                        query.exec();
                    }
                    add_k +=1;
                    if (add_k==2)
                    {
                        query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND "
                                                               "ДатаРождения=:data AND Категория=:category;");
                        if (next_toure==false)
                        {
                            query.bindValue(":place",row+1);
                        } else{
                            int place = check_the_place();
                            query.bindValue(":place",place);
                        }
                        query.bindValue(":first_name",first_name_this_member);
                        query.bindValue(":last_name",last_name_this_member);
                        query.bindValue(":data", data_this_member);
                        query.bindValue(":category",category);
                        query.exec();
                        add_k = 1;
                    }


                        if (!second.isEmpty())
                        {
                            crying_members.append(second);
                            second.clear();
                        }
                    was_first_add = false;

                }
            }


        if (last_place_check==false) //СТАВИТЬ МЕСТО ПОСЛЕДНЕМУ ИЛИ НЕ СТАВИТЬ?
        {
            //indeh
            QString last_name_this_member= ui->view_fighters->model()->data(ui->view_fighters->model()->index(indeh,0)).toString();
            QString first_name_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(indeh,1)).toString();
            QString data_this_member = ui->view_fighters->model()->data(ui->view_fighters->model()->index(indeh,3)).toString();
            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND "
                                                   "ДатаРождения=:data AND Категория=:category;");
            if (second_tour==true && next_toure==true)
            {
                int place = check_the_place();
                query.bindValue(":place",place);
            } else if (second_tour==true && next_toure==false){
                query.bindValue(":place",indeh+1);
            } else{
                query.bindValue(":place",indeh+1);
            }
            query.bindValue(":first_name",first_name_this_member);
            query.bindValue(":last_name",last_name_this_member);
            query.bindValue(":data", data_this_member);
            query.bindValue(":category",category);
            query.exec();
        }

        if (!second.isEmpty())
        {
            crying_members.append(second);
        }


        QList<double> middle_balls;
        QList<double> min_balls;
        QList<double>max_balls;
        QString check_first_loop;
        next_toure=false;
        if (!crying_members.isEmpty())
        {
            for (int i=0;i<crying_members.count();i++) {
                QString check;
                 int cr = crying_members.at(i).count();


                 if (second_tour==false)
                 {
                     QMessageBox::StandardButton baton = QMessageBox::question(this,"Одинаковые баллы","У некоторых участников совпадают баллы выступления.\n"
                                                                                                       "Провести дополнительный тур?", QMessageBox::Yes | QMessageBox::No);
                     if (baton == QMessageBox::Yes)
                     {
                         next_toure = true;
                     } else if(baton == QMessageBox::No)
                     {
                         QMessageBox::warning(this,"Одинаковые баллы","Места не будут расставлены. Расставьте их вручную во вкладке  'Участники и категории'");
                         next_toure = false;
                     }



                 } else if (second_tour==true)
                 {
                     for (int j=0;j<cr;j++)
                     {
                         QStringList last_middle_balls;
                         QStringList last_max_balls;
                         QStringList last_min_balls;
                         query.prepare("SELECT СреднийБалл, Мин_Балл, Макс_Балл FROM " +competition_key+" WHERE rowid=:row");
                         query.bindValue(":row",crying_members[i][j]);
                         query.exec();
                         while (query.next())
                         {
                             check = query.value(0).toString();

                             last_middle_balls = query.value(0).toString().split("_");
                             last_min_balls = query.value(1).toString().split("_");
                             last_max_balls = query.value(2).toString().split("_");
                         }
                         middle_balls.append(last_middle_balls.at(last_middle_balls.count()-2).toDouble());
                         min_balls.append(last_min_balls.at(last_min_balls.count()-2).toDouble()); //ДОБАВЛЯЕМ СРЕДНИЕ МИН И МАКС БАЛЛЫ В МАССИВЫ
                         max_balls.append(last_max_balls.at(last_max_balls.count()-2).toDouble());

                         }


                if (middle_balls[0]==middle_balls[1])
                {
                    if(min_balls[0]==min_balls[1])
                    {
                        if(max_balls[0]==max_balls[1])
                        {
                            QString out_stroke="Программа не может расставить места участникам в связи с тем,\n"
                                               "что в текущем и предыдущем круге у этих бойцов были одинаковые баллы\n"
                                               "Участники с одинаковыми баллами:\n";
                            for (int w=0;w<crying_members[i].count();w++) {
                                query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                                query.bindValue(":row",crying_members[i][w]);
                                query.exec();
                                while (query.next())
                                {
                                    out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                                }
                            }
                            QMessageBox::critical(this,"Критическая ситуация",out_stroke);
                            QMessageBox::warning(this,"Места","Места для этих учатников НЕ были расставлены. Расставьте их вручную во вкладке 'Участники и категории' ");
                            continue;
                        } else if (max_balls[0]>max_balls[1]) {
                            QString out_stroke="У этих участников в этом круге были одинаковые баллы, места будут расставлены с учётом предыдущего круга\n"
                                               "Участники:\n";
                            for (int w=0;w<crying_members[i].count();w++) {
                                query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                                query.bindValue(":row",crying_members[i][w]);
                                query.exec();
                                while (query.next())
                                {
                                    out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                                }
                            }
                            int c = check_the_place();
                            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                            query.bindValue(":row",crying_members[i][0]);
                            query.bindValue(":place",c);
                            query.exec();


                            c = check_the_place();
                            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                            query.bindValue(":row",crying_members[i][1]);
                            query.bindValue(":place",c);
                            query.exec();

                            QMessageBox::information(this,"Критическая ситуация",out_stroke);
                        } else{
                            QString out_stroke="У этих участников в этом круге были одинаковые баллы, места будут расставлены с учётом предыдущего круга\n"
                                               "Участники:\n";
                            for (int w=0;w<crying_members[i].count();w++) {
                                query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                                query.bindValue(":row",crying_members[i][w]);
                                query.exec();

                                while (query.next())
                                {
                                    out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                                }
                            }
                            int c = check_the_place();
                            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                            query.bindValue(":row",crying_members[i][1]);
                            query.bindValue(":place",c);
                            query.exec();


                            c = check_the_place();
                            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                            query.bindValue(":row",crying_members[i][0]);
                            query.bindValue(":place",c);
                            query.exec();

                            QMessageBox::information(this,"Критическая ситуация",out_stroke);
                        }
                    } else if (min_balls[0]>min_balls[1])
                    {
                        QString out_stroke="У этих участников в этом круге были одинаковые баллы, места будут расставлены с учётом предыдущего круга\n"
                                           "Участники:\n";
                        for (int w=0;w<crying_members[i].count();w++) {
                            query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                            query.bindValue(":row",crying_members[i][w]);
                            query.exec();
                            while (query.next())
                            {
                                out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                            }
                        }
                        int c = check_the_place();
                        query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                        query.bindValue(":row",crying_members[i][0]);
                        query.bindValue(":place",c);
                        query.exec();


                        c = check_the_place();
                        query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                        query.bindValue(":row",crying_members[i][1]);
                        query.bindValue(":place",c);
                        query.exec();

                        QMessageBox::information(this,"Критическая ситуация",out_stroke);
                    } else{
                        QString out_stroke="У этих участников в этом круге были одинаковые баллы, места будут расставлены с учётом предыдущего круга\n"
                                           "Участники:\n";
                        for (int w=0;w<crying_members[i].count();w++) {
                            query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                            query.bindValue(":row",crying_members[i][w]);
                            query.exec();
                            while (query.next())
                            {
                                out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                            }
                        }
                        int c = check_the_place();
                        query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                        query.bindValue(":row",crying_members[i][1]);
                        query.bindValue(":place",c);
                        query.exec();


                        c = check_the_place();
                        query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                        query.bindValue(":row",crying_members[i][0]);
                        query.bindValue(":place",c);
                        query.exec();

                        QMessageBox::information(this,"Критическая ситуация",out_stroke);
                    }
                } else if (middle_balls[0]>middle_balls[1]) {
                    QString out_stroke="У этих участников в этом круге были одинаковые баллы, места будут расставлены с учётом предыдущего круга\n"
                                       "Участники:\n";
                    for (int w=0;w<crying_members[i].count();w++) {
                        query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                        query.bindValue(":row",crying_members[i][w]);
                        query.exec();
                        while (query.next())
                        {
                            out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                        }
                    }
                    int c = check_the_place();
                    query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                    query.bindValue(":row",crying_members[i][0]);
                    query.bindValue(":place",c);
                    query.exec();


                    c = check_the_place();
                    query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                    query.bindValue(":row",crying_members[i][1]);
                    query.bindValue(":place",c);
                    query.exec();

                    QMessageBox::information(this,"Критическая ситуация",out_stroke);
                } else{
                    QString out_stroke="У этих участников в этом круге были одинаковые баллы, места будут расставлены с учётом предыдущего круга\n"
                                       "Участники:\n";
                    for (int w=0;w<crying_members[i].count();w++) {
                        query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE rowid=:row");
                        query.bindValue(":row",crying_members[i][w]);
                        query.exec();
                        while (query.next())
                        {
                            out_stroke += query.value(0).toString() + " "+ query.value(1).toString() + " "+query.value(2).toString()+"\n";
                        }
                    }
                    int c = check_the_place();
                    query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                    query.bindValue(":row",crying_members[i][1]);
                    query.bindValue(":place",c);
                    query.exec();

                    c = check_the_place();
                    query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE rowid=:row");
                    query.bindValue(":row",crying_members[i][0]);
                    query.bindValue(":place",c);
                    query.exec();
                    QMessageBox::information(this,"Критическая ситуация",out_stroke);
                }
            }
        }
}
        //END ALGORITM


        int count = ui->view_fighters->model()->rowCount();
        for (int i = 6; i < count; i++) {
            QString last_name  = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,0)).toString();
            QString first_name  = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,1)).toString();
            QString patronymic_name  = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,2)).toString();
            QString data  = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,3)).toString();
            query.prepare("UPDATE "+competition_key+" SET Место=:place WHERE Фамилия=:last_name AND Имя=:first_name AND " //РАССТАНОВКА ОСТАТКА
                                                   "ДатаРождения=:data AND Категория=:category");
            query.bindValue(":place",i+1);
            query.bindValue(":first_name",first_name);
            query.bindValue(":last_name",last_name);
            query.bindValue(":data", data);
            query.bindValue(":category",category);

            query.exec();
        }
            if (next_toure==false)
            {

        query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE Место=1 AND Категория=:categ");
        query.bindValue(":categ",category);
                query.exec();
        while(query.next())
        {
            winners+="1 место: "+query.value(0).toString()+" "+ query.value(1).toString()+" "+query.value(2).toString()+"\n";
        }

        query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE Место=2  AND Категория=:categ");
        query.bindValue(":categ",category);
        query.exec();
        while(query.next())
        {
            winners+="2 место: "+query.value(0).toString()+" "+ query.value(1).toString()+" "+query.value(2).toString()+"\n";
        }

        query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE Место=3  AND Категория=:categ");
        query.bindValue(":categ",category);
                query.exec();
        while(query.next())
        {
            winners+="3 место: "+query.value(0).toString()+" "+ query.value(1).toString()+" "+query.value(2).toString()+"\n";
        }

        query.prepare("SELECT Фамилия, Имя, Отчество FROM "+competition_key+" WHERE Место=4  AND Категория=:categ");
        query.bindValue(":categ",category);
                query.exec();
        while(query.next())
        {
            winners+="4 место: "+query.value(0).toString()+" "+ query.value(1).toString()+" "+query.value(2).toString()+"\n";
        }


            ui->categories->removeItem(index_category);

        QMessageBox::information(this,"Завершение категории",winners);
        ui->end_loop->setEnabled(false);
        ui->end_category->setEnabled(false);
        ui->count_member->setEnabled(false);
        ui->categories->setEnabled(true);
        ui->start_loop->setEnabled(true);
        ui->out_member->setEnabled(false);
            }

    on_categories_currentIndexChanged(category);
    repeat_view_fighters();
    ui->label_FIO->setText("Фамилия Имя Отчество");
}
}

void Fight::on_categories_activated(int index)
{
    index_category = index;
}

void Fight::on_sorting_box_activated(const QString &arg1)
{
    if (arg1=="Без сортировки")
    {
        ui->desc_asc_box->setEnabled(false);
    } else {
        ui->desc_asc_box->setEnabled(true);
}
    sorting = arg1;
    repeat_view_fighters();
}

void Fight::on_categories_box_activated(const QString &arg1)
{

    categorys1 = arg1;
    repeat_view_fighters();
}

void Fight::repeat_view_fighters()
{

    model_for_fight->clear();

    model_for_fight->setTable(competition_key);
    model_for_fight->setEditStrategy(QSqlTableModel::OnFieldChange);
    QStringList dop;
    dop<<"Без сортировки"<<"По местам"<<"По фамилии"<<"По имени"<<"По возрасту";
    int index_sorting=0;
    switch (dop.indexOf(sorting)) {
    case (0):{
        break;
    }
    case(1):{
        index_sorting=13;
        break;
    }
    case(2):{
        index_sorting=0;
        break;
    }
    case(3):{
        index_sorting=1;
        break;
    }
    case(4):{
        index_sorting=4;
        break;
    }
    }
    if (sorting=="Без сортировки" && categorys1 !="Все"){
       model_for_fight->setFilter("Категория = '"+categorys1+"'");

    } else if (sorting != "Без сортировки" && categorys1=="Все" ) {
        if (asc_desc==true)
        {
            model_for_fight->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            model_for_fight->setSort(index_sorting, Qt::DescendingOrder);
        }
    }
 else if (sorting != "Без сортировки" && categorys1 != "Все") {
        model_for_fight->setFilter("Категория = '"+categorys1+"'");
        if (asc_desc==true)
        {
            model_for_fight->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            model_for_fight->setSort(index_sorting, Qt::DescendingOrder);
        }
    }

    model_for_fight->select();
    ui->view_members->setModel(model_for_fight);
    ui->view_members->resizeColumnsToContents();
    ui->view_members->resizeRowsToContents();

    last_name = "";
}

void Fight::on_desc_asc_box_activated(const QString &arg1)
{
    if (arg1=="По возрастанию")
    {
        asc_desc=true;
    } else {
        asc_desc=false;
}
    repeat_view_fighters();
}

void Fight::on_view_members_clicked(const QModelIndex &index)
{
    history_member = index;
}

void Fight::on_history_member_clicked()
{
    if (history_fight==false)
    {
        history_fight = true;
        ui->history_member->setText("Сбросить");
    } else {
        history_fight = false;
        ui->history_member->setText("История участника");
        repeat_view_fighters();
        return;
}
    QString last_name =  ui->view_members->model()->data(ui->view_members->model()->index(ui->view_members->currentIndex().row(), 0)).toString();

    if (last_name == "")
    {
        QMessageBox::critical(this,"История участника", "Выберите участника для просмотра истории\nКликните по его клетке в таблице или выберите полную строку");
        return;
    }

    history_fighter->removeRows(0,history_fighter->rowCount());

    int row_hist_mem = history_member.row();
    QString judge_1 = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,14)).toString();
    QString judge_2 = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,15)).toString();
    QString judge_3 = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,16)).toString();
    QString judge_4 = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,17)).toString();
    QString judge_5 = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,18)).toString();

    QString middle_balls = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,19)).toString();
    QString min_balls = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,20)).toString();
    QString max_balls = ui->view_members->model()->data(ui->view_members->model()->index(row_hist_mem,21)).toString();


    QStringList judge_1_arr = judge_1.split("_");
    QStringList judge_2_arr = judge_2.split("_");
    QStringList judge_3_arr = judge_3.split("_");
    QStringList judge_4_arr = judge_4.split("_");
    QStringList judge_5_arr = judge_5.split("_");
    QStringList middle_balls_arr = middle_balls.split("_");
    QStringList min_balls_arr = min_balls.split("_");
    QStringList max_balls_arr = max_balls.split("_");

    QStringList circles;
    for (int i=0;i<judge_1_arr.count();i++) {
        QString num;
        num.setNum(i+1);
        circles.append(num+" круг ");
        QStandardItem *middle = new QStandardItem(middle_balls_arr.at(i));
        QStandardItem *min = new QStandardItem(min_balls_arr.at(i));
        QStandardItem *max = new QStandardItem(max_balls_arr.at(i));

        QStandardItem *ju_1 = new QStandardItem(judge_1_arr.at(i));
        QStandardItem *ju_2 = new QStandardItem(judge_2_arr.at(i));
        QStandardItem *ju_3 = new QStandardItem(judge_3_arr.at(i));
        QStandardItem *ju_4 = new QStandardItem(judge_4_arr.at(i));
        QStandardItem *ju_5 = new QStandardItem(judge_5_arr.at(i));

        history_fighter->appendRow(QList<QStandardItem*>()<<middle<<min<<max<<ju_1<<ju_2<<ju_3<<ju_4<<ju_5);
    }
    history_fighter->setVerticalHeaderLabels(circles);
    ui->view_members->setModel(history_fighter);
    ui->view_members->resizeColumnsToContents();
    ui->view_members->resizeRowsToContents();
}

void Fight::save_data_count_member()
{
    int  count = ui->view_fighters->model()->rowCount();
   for (int i=0; i<count;i++)
   {
       QString last_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,0)).toString();
       QString first_name = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,1)).toString();
       QString data = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,3)).toString();

      QString judge_1 = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,8)).toString();
      QString judge_2 = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,9)).toString();
      QString judge_3 = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,10)).toString();
      QString judge_4 = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,11)).toString();
      QString judge_5 = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,12)).toString();

      QString midle_bal = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,13)).toString();
      QString min_bal = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,14)).toString();
      QString max_bal = ui->view_fighters->model()->data(ui->view_fighters->model()->index(i,15)).toString();

       query.prepare("SELECT СреднийБалл, Мин_Балл, Макс_Балл, Судья_1,Судья_2,Судья_3,Судья_4,Судья_5 FROM "+competition_key+" WHERE Фамилия=:last_name AND Имя=:first_name  AND "
                                                            "ДатаРождения=:data AND Категория=:category;");

       query.bindValue(":first_name",first_name);
       query.bindValue(":last_name",last_name);
       query.bindValue(":data", data);
       query.bindValue(":category",category);

       query.exec();
       QString judge_1_l;
       QString judge_2_l;
       QString judge_3_l;
       QString judge_4_l;
       QString judge_5_l;

       QString min_ball_l;
       QString max_ball_l;
       QString middle_ball_l;
       while (query.next())
       {
           middle_ball_l = query.value(0).toString();
           min_ball_l = query.value(1).toString();
           max_ball_l = query.value(2).toString();

           judge_1_l = query.value(3).toString();
           judge_2_l = query.value(4).toString();
           judge_3_l = query.value(5).toString();
           judge_4_l = query.value(6).toString();
           judge_5_l = query.value(7).toString();
       }
       if (middle_ball_l=="0")
       {
           middle_ball_l = midle_bal;
           min_ball_l = min_bal;
           max_ball_l = max_bal;
           judge_1_l = judge_1;
           judge_2_l = judge_2;
           judge_3_l = judge_3;
           judge_4_l = judge_4;
           judge_5_l = judge_5;
       } else {
           middle_ball_l += "_"+midle_bal;
           min_ball_l +="_"+ min_bal;
           max_ball_l +="_"+ max_bal;
           judge_1_l += "_"+judge_1;
           judge_2_l += "_"+judge_2;
           judge_3_l += "_"+judge_3;
           judge_4_l += "_"+judge_4;
           judge_5_l += "_"+judge_5;
};
       query.prepare("UPDATE "+competition_key+" SET СреднийБалл=:middle_ball_l, Мин_Балл=:min_ball_l, Макс_Балл=:max_ball_l,"
                                               " Судья_1=:judge_1_l, Судья_2=:judge_2_l, Судья_3=:judge_3_l, Судья_4=:judge_4_l, Судья_5=:judge_5_l "
                                               "WHERE Фамилия=:last_name AND Имя=:first_name  AND "
                                               "ДатаРождения=:data AND Категория=:category;");
       query.bindValue(":first_name",first_name);
       query.bindValue(":last_name",last_name);
       query.bindValue(":data", data);
       query.bindValue(":category",category);

       query.bindValue(":middle_ball_l",middle_ball_l);
       query.bindValue(":min_ball_l",min_ball_l);
       query.bindValue(":max_ball_l",max_ball_l);
       query.bindValue(":judge_1_l",judge_1_l);
       query.bindValue(":judge_2_l",judge_2_l);
       query.bindValue(":judge_3_l",judge_3_l);
       query.bindValue(":judge_4_l",judge_4_l);
       query.bindValue(":judge_5_l",judge_5_l);

       query.exec();

}
}

void Fight::on_end_competition_clicked()
{
    QMessageBox::StandardButton end = QMessageBox::question(this,"Это конец?","Закончить соревнования \n(Вернуться к проведению будет нельзя)",QMessageBox::Yes | QMessageBox::No);

    if (end==QMessageBox::No)
    {
        return;
    } else if(end == QMessageBox::Yes)
    {
        query.exec("SELECT Фамилия FROM "+competition_key+" WHERE Место=0 LIMIT 1");
        if(query.first())
        {
            QMessageBox::critical(this,"Участники","Не все участники закончили соревнования");
            return;
        }

        query.prepare("UPDATE competitions SET end_competition=:end WHERE PK=:pk");
        query.bindValue(":pk",PK);
        query.bindValue(":end",true);
        query.exec();
        emit show_main();
        this->close();
    }
}

int Fight::check_the_place()
{
    for (int i=1;i<6;i++) {
        sup_query.prepare("SELECT Фамилия FROM "+competition_key+" WHERE Категория=:cat AND Место = :place");
        sup_query.bindValue(":place",i);
        sup_query.bindValue(":cat",category);
        sup_query.exec();
        if(!sup_query.first())
        {
                return i;
        }
        }

    return -1;
}

void Fight::on_create_ended_category_clicked()
{
    QMessageBox::StandardButton ok =QMessageBox::question(this,"Конец проведения","Закончить проведение соревнований на этом татами и сформировать окончательный файл?");
    if (ok ==QMessageBox::Yes)
    {
        query.exec("SELECT Фамилия FROM categories_mode WHERE Место=0");
        if (query.first())
        {
            QMessageBox::critical(this,"Места","Какие-то участники не получили своего места. Проверьте вкладку 'Участники и категории'");
            return;
        }
        QString save_file_route = QFileDialog::getSaveFileName(this,"Сохранение категорий","ЗаконченныеКатегории","*.json");

        if (save_file_route=="")
        {
            return;
        }



        QJsonObject MainObject;

        QStringList categories;
        query.exec("SELECT DISTINCT(Категория) FROM categories_mode");
        while (query.next())
        {
            categories.append(query.value(0).toString());
        }

        for (int i=0;i<categories.count();i++)
        {
            QJsonObject categoriesObject;
            query.prepare("SELECT * FROM categories_mode WHERE Категория=:ca");
            query.bindValue(":ca",categories[i]);
            query.exec();
            int row = 0;

            while (query.next())
            {
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
                member.insert("City",query.value(11).toString());
                member.insert("Place",query.value(13).toString());
                member.insert("Judge_1",query.value(14).toString());
                member.insert("Judge_2",query.value(15).toString());
                member.insert("Judge_3",query.value(16).toString());
                member.insert("Judge_4",query.value(17).toString());
                member.insert("Judge_5",query.value(18).toString());
                member.insert("sum",query.value(19).toString());
                member.insert("min",query.value(20).toString());
                member.insert("max",query.value(21).toString());
                categoriesObject.insert(QString::number(row),member);
                row++;
            }
            MainObject.insert(categories[i],categoriesObject);
        }
        MainObject.insert("WAS_OPENED","FALSE");
        MainObject.insert("ENDED_TEMPLATE","TRUE");
        QFileInfo info(save_file_route);
        QDir::setCurrent(info.path());

        QFile Json_file(save_file_route);

        if(!Json_file.open(QIODevice::WriteOnly))
        {
            return;
        }

        Json_file.write(QJsonDocument(MainObject).toJson(QJsonDocument::Indented));
        Json_file.close();
        QMessageBox::information(this,"Категории сохранены.","Окончательный файл сформирован успешно. Не теряйте его, восстановить файл будет невозможно\n"
                                                             "Далее на компьютере, где создавалось мероприятие откройте вкладку 'разделение категорий', нажмите кнопку 'загрузить законченные категории' и выберите этот файл");

    } else if (ok==QMessageBox::No) {
        return;
}
    query.exec("DELETE  FROM categories_mode");
    emit show_main();
    this->close();
}

void Fight::on_load_ended_category_clicked()
{
    QString root;
    root = QFileDialog::getOpenFileName(this,"Выберите Категории", "","json (*.json)");
if (root==""){
    return;
}
QFile File;
File.setFileName(root);
File.open(QIODevice::ReadOnly|QFile::Text);
QJsonDocument doc;
if (File.isOpen()){
    doc = QJsonDocument::fromJson(QByteArray(File.readAll()));
} else{
    return;
}

QString checking = doc.object().value("ENDED_TEMPLATE").toString();
QString opened = doc.object().value("WAS_OPENED").toString();
if (opened == "TRUE")
{
    QMessageBox::critical(this,"Не тот файл","Этот файл уже был загружен в программу");
    return;
} else if (opened=="FALSE") {
    QJsonObject copy = doc.object();
    copy.remove("WAS_OPENED");
    copy.insert("WAS_OPENED","TRUE");
}
File.close();
if (checking !="TRUE")
{
    QMessageBox::critical(this,"Не тот файл?","Программа заметила, что вы загрузили не тот файл");
    return;
}

QStringList categorys = doc.object().keys();
bool checking_file  = false;
for (int i=0;i<categorys.count();i++)
{
    if (categorys[i]=="ENDED_TEMPLATE" || categorys[i]=="WAS_OPENED")
    {
        continue;
    }
    QJsonObject one_category = doc.object().value(categorys[i]).toObject();
    QStringList keys_members = one_category.keys();

    for (int j=0;j<keys_members.count();j++)
    {
        QJsonObject member = one_category.value(keys_members[j]).toObject();
        query.prepare("INSERT INTO "+competition_key+" (Фамилия, Имя, Отчество, ДатаРождения, Возраст, Пол, Квалификация, СтепеньКвалификации, Разряд, Руководитель, Организация, Город, Категория,"
                                                     "Место, Судья_1, Судья_2, Судья_3, Судья_4, Судья_5, СреднийБалл, Мин_Балл, Макс_Балл)"
                                                     " VALUES (:Last, :First,:Patron,:Data, :Age, :Gender, :TypeKval,:ValKval,:Razor,:Trainer,:Org, :City,:Categ,:Place, :J1,:J2,:J3,:J4,:J5, :Sum,:Min, :Max)");
        query.bindValue(":Last",member.value("LastName").toString());
        query.bindValue(":First",member.value("FirstName").toString());
        query.bindValue(":Patron",member.value("PatronName").toString());
        query.bindValue(":Data",member.value("Data").toString());
        query.bindValue(":Age",member.value("Age").toString());
        query.bindValue(":Gender",member.value("Gender").toString());
        query.bindValue(":TypeKval",member.value("TypeKval").toString());
        query.bindValue(":ValKval",member.value("PosKval").toString());
        query.bindValue(":Razor",member.value("Razor").toString());
        query.bindValue(":Trainer",member.value("Trainer").toString());
        query.bindValue(":Org",member.value("Organization").toString());
        query.bindValue(":City",member.value("City").toString());
        query.bindValue(":Categ",categorys[i]);
        query.bindValue(":Place",member.value("Place").toString());
        query.bindValue(":J1",member.value("Judge_1").toString());
        query.bindValue(":J2",member.value("Judge_2").toString());
        query.bindValue(":J3",member.value("Judge_2").toString());
        query.bindValue(":J4",member.value("Judge_3").toString());
        query.bindValue(":J5",member.value("Judge_5").toString());
        query.bindValue(":Sum",member.value("sum").toString());
        query.bindValue(":Min",member.value("min").toString());
        query.bindValue(":Max",member.value("max").toString());

        query.exec();


    }
    ui->categories_box->addItem(categorys[i]);

}
if (opened=="FALSE")
{

    QJsonObject copy = doc.object();
    copy.remove("WAS_OPENED");
    copy.insert("WAS_OPENED","TRUE");

    QFileInfo info(root);
    QDir::setCurrent(info.path());

    QFile Json_file(root);

    if(!Json_file.open(QIODevice::WriteOnly))
    {
        return;
    }

    Json_file.write(QJsonDocument(copy).toJson(QJsonDocument::Indented));
    Json_file.close();
}
QMessageBox::information(this,"Категории загружены","Законченные категории загружены успешно :)");
}

