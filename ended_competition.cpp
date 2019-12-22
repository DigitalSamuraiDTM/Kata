#include "ended_competition.h"
#include "ui_ended_competition.h"
#include "QDebug"
#include "QMessageBox"
#include "QSqlError"
#include <QAxObject>
#include <QInputDialog>
ended_competition::ended_competition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ended_competition)
{
    members_model = new QSqlTableModel(this,db);
    judges_model = new QSqlTableModel(this, db);
    ui->setupUi(this);
    history_fighter = new QStandardItemModel;
    history_fighter->setHorizontalHeaderLabels(QStringList()<<"Сумма"<<"Мин_Балл"<<"Макс_Балл"<<"Судья_1"
                                               <<"Судья_2"<<"Судья_3"<<"Судья_4"<<"Судья_5");
    categorys_model = new QStandardItemModel;
    categorys_model->setHorizontalHeaderLabels(QStringList()<<"Пол"<<"Возраст от"<<"До (включительно)"<<"Квалификация"<<"Кю от"<<"Кю до(включительно)"<<"Категория");
    ui->categorys_view->setModel(categorys_model);
}

ended_competition::~ended_competition()
{
    delete ui;
}

void ended_competition::get_name_comp(QString name, QSettings* pyk)
{
   Settings = pyk;

   Settings->beginGroup("Geometry");
   setGeometry(Settings->value("GeometryEnded",QRect(500,500,600,600)).toRect());
   Settings->endGroup();
   Settings->beginGroup("Font");
   int size = Settings->value("Size",12).toInt();
   Settings->endGroup();
   ui->tabWidget->setFont(QFont("Calibri",size));
   ui->DELETE->setFont(QFont("Calibri",size));

   //TAB_1
   ui->groupBox->setFont(QFont("Calibri",size));
   ui->data_copetition->setFont(QFont("Calibri",size));
   ui->deputy_main_judge_competition->setFont(QFont("Calibri",size));
   ui->main_judge_competition->setFont(QFont("Calibri",size));
   ui->main_secretary_competiotion->setFont(QFont("Calibri",size));
   ui->name_competition->setFont(QFont("Calibri",size));
   ui->oldes_judge_competition->setFont(QFont("Calibri",size));
   ui->place_competition->setFont(QFont("Calibri",size));
   ui->groupBox_2->setFont(QFont("Calibri",size));
   ui->judges_count->setFont(QFont("Calibri",size));
   ui->mem_count->setFont(QFont("Calibri",size));
   ui->citys_box->setFont(QFont("Calibri",size));
   ui->citys->setFont(QFont("Calibri",size));
   ui->subjects_box->setFont(QFont("Calibri",size));
   ui->subjetcts->setFont(QFont("Calibri",size));

   //TAB_2
   ui->asc_desc_mem_box->setFont(QFont("Calibri",size));
   ui->categorys_box->setFont(QFont("Calibri",size));
   ui->generate_all_members->setFont(QFont("Calibri",size));
   ui->generate_out_members->setFont(QFont("Calibri",size));
   ui->history_member->setFont(QFont("Calibri",size));
   ui->sorting_mem_box->setFont(QFont("Calibri",size));
   ui->members_view->setFont(QFont("Calibri",size));
   //TAB_3
   ui->asc_desc_judge->setFont(QFont("Calibri",size));
   ui->comboBox->setFont(QFont("Calibri",size));
   ui->comboBox_2->setFont(QFont("Calibri",size));
   ui->generate_out_judges->setFont(QFont("Calibri",size));
   ui->judges_view->setFont(QFont("Calibri",size));
   //TAB_4
   ui->categorys_view->setFont(QFont("Calibri",size));
   query.prepare("SELECT * FROM competitions WHERE НазваниеСоревнований=:name");
   query.bindValue(":name", name);
   query.exec();
   QString cat;
   QString pos;
   while (query.next())
   {
       name_c = name;
       data_c = query.value(1).toString();
       place_c = query.value(2).toString();

       main_j_c = query.value(3).toString().split("_");
       oldest_j_c = query.value(4).toString().split("_");
       main_s_c = query.value(5).toString().split("_");
       deputy_m_j_c = query.value(6).toString().split("_");

       number_s_c = query.value(7).toInt();
       subjects_c = query.value(8).toString();
       number_c_c = query.value(9).toInt();
       citys_c = query.value(10).toString();
       members_key = query.value(14).toString();
       comp_name = "competition_"+query.value(14).toString();
       judges_key = "judges_"+query.value(14).toString();
      cat = query.value(12).toString();
      pos = query.value(15).toString();
   }
   poses  = pos.split("_");
   all_categorys = cat.split("_");
   for (int i=0;i<all_categorys.count();i++)
   {
       QStringList one_category = all_categorys.at(i).split(",");
       QString gender = one_category.at(0);
       QStringList age = one_category.at(1).split("-");
       int age_from =  age.at(0).toInt();
       int age_to =age.at(1).toInt();
       QStringList kval = one_category.at(3).split("-");
       int kval_from = kval.at(0).toInt();
       int kval_to = kval.at(1).toInt();
       QString type_kval = one_category.at(4);
       QString cat =all_categorys.at(i);

       QList<QStandardItem*> list;
       list<<new QStandardItem(gender)<<new QStandardItem(QString::number(age_from))<<new QStandardItem(QString::number(age_to))<<new QStandardItem(type_kval)
          << new QStandardItem(QString::number(kval_from))<<new QStandardItem(QString::number(kval_to))<<new QStandardItem(cat);
       int count = ui->categorys_view->model()->rowCount();
       if (count ==0)
       {
           categorys_model->appendRow(list);
           continue;
       }
       bool was_insert = false;
       for (int i=0;i<count;i++) {
           QString gender_view = ui->categorys_view->model()->data(ui->categorys_view->model()->index(i,0)).toString();
           int age_from_view = ui->categorys_view->model()->data(ui->categorys_view->model()->index(i,1)).toInt();
           int kval_from_view = ui->categorys_view->model()->data(ui->categorys_view->model()->index(i,13)).toInt();
           QString type_kval_view = ui->categorys_view->model()->data(ui->categorys_view->model()->index(i,5)).toString();
           if (kval_from==0)
           {
               kval_from==11;
           }
           if (kval_from_view==0)
           {
               kval_from_view=11;
           }
           if(age_from<age_from_view)
           {
               if (gender==gender_view)
               {
                   if (type_kval==type_kval_view)
                   {
                       if (type_kval=="дан")
                       {
                           if (kval_from<kval_from_view)
                           {
                               categorys_model->insertRow(i,list);
                               was_insert = true;
                               break;
                           }
                       } else{
                       if (kval_from>kval_from_view)
                       {
                           categorys_model->insertRow(i,list);
                           was_insert = true;
                           break;
                       }
                       }
                   }

               }
           }
       }
       ui->categorys_view->resizeColumnsToContents();
       if (was_insert==false)
       {
           categorys_model->appendRow(list);
       }


   }


   members_key="competition_"+members_key;
   QString niam;
   ui->name_competition->setText("Название соревнований: "+name_c);
   ui->data_copetition->setText("Дата проведения: "+data_c);
   ui->place_competition->setText("Место проведения: "+place_c);
   ui->main_judge_competition->setText("Главный судья: "+main_j_c[0]);
   ui->oldes_judge_competition->setText("Старший судья: "+oldest_j_c[0]);
   ui->main_secretary_competiotion->setText("Главный секретарь: "+main_s_c[0]);
   ui->deputy_main_judge_competition->setText("Заместитель главного судьи: "+deputy_m_j_c[0]);
   niam.setNum(number_s_c);
   ui->subjects_box->setTitle("Количество субъектов: "+niam);
   ui->subjetcts->setText(subjects_c);
   niam.clear();
   niam.setNum(number_c_c);
   ui->citys_box->setTitle("Количество городов: "+niam);
   ui->citys->setText(citys_c);

   repeat_members();

   members_count = ui->members_view->model()->rowCount();
   QString m;
   m.setNum(members_count);
   ui->mem_count->setText("Всего участников: "+m);
   repeat_judges();
   judges_count = ui->judges_view->model()->rowCount();
   m.setNum(judges_count);
   ui->judges_count->setText("Всего судей: "+m);
   for (int i=0;i<all_categorys.count();i++) {
       ui->categorys_box->addItem(all_categorys.at(i));
   }
   query.exec("SELECT Бригада FROM "+judges_key);
   imu.clear();
   while (query.next())
   {
       bool was=true;
       int brig = query.value(0).toInt();
       for (int i=0;i<imu.count();i++)
       {
           if (brig==imu[i])
           {
               was = false;
               break;
           }
       }
       if (was==true)
       {
           imu.append(brig);
       }
   }

   for (int i=0;i<imu.count();i++)
   {
       QString m;
       m.setNum(imu.at(i));
       ui->comboBox->addItem(m);
   }

}

void ended_competition::repeat_members(){
    members_model->clear();
    members_model->setTable(members_key);
    members_model->setEditStrategy(QSqlTableModel::OnFieldChange);

    QStringList dop;
    dop<<"Без сортировки"<<"По местам"<<"По фамилии"<<"По имени"<<"По возрасту";
    int index_sorting=-1;
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
       members_model->setFilter("Категория = '"+categorys1+"'");

    } else if (sorting != "Без сортировки" && categorys1=="Все" ) {
        if (asc_desc==true)
        {
            members_model->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            members_model->setSort(index_sorting, Qt::DescendingOrder);
        }
    }
 else if (sorting != "Без сортировки" && categorys1 != "Все") {
        members_model->setFilter("Категория = '"+categorys1+"'");
        if (asc_desc==true)
        {
            members_model->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            members_model->setSort(index_sorting, Qt::DescendingOrder);
        }
    }


    members_model->select();
    ui->members_view->setModel(members_model);
}

void ended_competition::repeat_judges(){
    judges_model->clear();
    judges_model->setTable(judges_key);
    judges_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    QStringList dop;
    dop<<"Без сортировки"<<"По фамилии"<<"По имени"<<"По бригаде"<<"По городу";
    int index_sorting=-1;
    switch (dop.indexOf(sorting2)) {
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
    if (sorting2=="Без сортировки" && categorys2 !="Бригада"){
       judges_model->setFilter("Бригада = '"+categorys2+"'");

    } else if (sorting2 != "Без сортировки" && categorys2=="Бригада" ) {
        if (asc_desc2==true)
        {
            judges_model->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            judges_model->setSort(index_sorting, Qt::DescendingOrder);
        }
    }
 else if (sorting2 != "Без сортировки" && categorys2 != "Бригада") {
        judges_model->setFilter("Бригада = '"+categorys2+"'");
        if (asc_desc2==true)
        {
            judges_model->setSort(index_sorting, Qt::AscendingOrder);
        } else {
            judges_model->setSort(index_sorting, Qt::DescendingOrder);
        }
    }
    judges_model->select();
    ui->judges_view->setModel(judges_model);
}

void ended_competition::on_categorys_box_activated(const QString &arg1)
{
    categorys1 = arg1;
    repeat_members();

}

void ended_competition::on_sorting_mem_box_activated(const QString &arg1)
{
    if (arg1=="Без сортировки")
    {
        ui->asc_desc_mem_box->setEnabled(false);
    } else {
        ui->asc_desc_mem_box->setEnabled(true);
}
    sorting = arg1;
    repeat_members();
}

void ended_competition::on_asc_desc_mem_box_activated(const QString &arg1)
{
    if (arg1=="По возрастанию")
    {
        asc_desc=true;
    } else {
        asc_desc=false;
}
    repeat_members();
}

void ended_competition::on_history_member_clicked()
{
    if (history_fight==false)
    {
        history_fight = true;
        ui->history_member->setText("Сбросить");
    } else {
        history_fight = false;
        ui->history_member->setText("История участника");
        repeat_members();
        return;
}
    QString last_name =  ui->members_view->model()->data(ui->members_view->model()->index(ui->members_view->currentIndex().row(), 0)).toString();

    if (last_name == "")
    {
        QMessageBox::critical(this,"История участника", "Выберите участника для просмотра истории\nКликните по его клетке в таблице или выберите полную строку");
        return;
    }

    history_fighter->removeRows(0,history_fighter->rowCount());

    int row_hist_mem = history_member.row();
    QString judge_1 = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,14)).toString();
    QString judge_2 = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,15)).toString();
    QString judge_3 = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,16)).toString();
    QString judge_4 = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,17)).toString();
    QString judge_5 = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,18)).toString();

    QString middle_balls = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,19)).toString();
    QString min_balls = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,20)).toString();
    QString max_balls = ui->members_view->model()->data(ui->members_view->model()->index(row_hist_mem,21)).toString();
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
    ui->members_view->setModel(history_fighter);
    ui->members_view->resizeColumnsToContents();
    ui->members_view->resizeRowsToContents();
}

void ended_competition::on_members_view_clicked(const QModelIndex &index)
{
    history_member = index;
}

void ended_competition::on_comboBox_activated(const QString &arg1)
{
    categorys2=arg1;
    repeat_judges();
}

void ended_competition::on_comboBox_2_activated(const QString &arg1)
{
    sorting2 = arg1;
    if (arg1=="Без сортировки")
    {
        ui->asc_desc_judge->setEnabled(false);
    } else {
        ui->asc_desc_judge->setEnabled(true);
}

    repeat_judges();
}

void ended_competition::on_asc_desc_judge_activated(const QString &arg1)
{
    if (arg1=="По возрастанию")
    {
        asc_desc2=true;
    } else {
        asc_desc2=false;
}
    repeat_judges();
}

void ended_competition::on_generate_out_judges_clicked()
{

    QAxObject *WordApp = new QAxObject("Word.Application");
    QAxObject *WordDoc = WordApp->querySubObject("Documents()");
    QAxObject *NewDoc = WordDoc->querySubObject("Add()");


    QAxObject *page_setup = NewDoc->querySubObject("PageSetup()");
    page_setup->setProperty("LeftMargin",35);
    page_setup->setProperty("RightMargin",30);
    page_setup->setProperty("TopMargin",40);
    page_setup->setProperty("BottomMargin",40);



    QAxObject *rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",0,100);                      //range ссылается на символы в документе с 0 до 100 символа
    rangeData->setProperty("Text",name_c);


    QAxObject *font = rangeData->querySubObject("Font");
    font->setProperty("Size",12);
    font->setProperty("Name","Times New Roman");
    QAxObject *paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    rangeData->dynamicCall("InsertParagraphAfter()");

    rangeData->clear();
    QAxObject *tables = NewDoc->querySubObject("Tables()");
    rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",101,200);
    QAxObject *Judge = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", rangeData->asVariant(), 1, 1, 1, 2);
    QAxObject *cell = Judge->querySubObject("Cell(Row,Column)",1,1);
    QAxObject *shade = cell->querySubObject("Shading");
    shade->setProperty("BackgroundPatternColor","wdColorGray20");
    QAxObject *range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","СУДЬИ");

    font->clear();
    rangeData->clear();
    paragraph->clear();

    rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",201,300);
    rangeData->setProperty("Text",place_c+" "+data_c);
    font = rangeData->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphLeft");
    paragraph->setProperty("SpaceAfter",0);
    rangeData->dynamicCall("InsertParagraphAfter()");
    rangeData->dynamicCall("InsertParagraphAfter()");

    rangeData->dynamicCall("SetRange(int,int)",301,400);
    QAxObject *main_table = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", rangeData->asVariant(), 5, 6, 1, 2);
    QAxObject *columns = main_table->querySubObject("Columns(Index)",1); //1
    columns->setProperty("PreferredWidthType","wdPreferredWidthPoints");
    columns->setProperty("PreferredWidth",20);
    columns = main_table->querySubObject("Columns(Index)",2);
    columns->setProperty("PreferredWidthType","wdPreferredWidthPoints"); //2
    columns->setProperty("PreferredWidth",300);
    columns = main_table->querySubObject("Columns(Index)",5);
    columns->setProperty("PreferredWidthType","wdPreferredWidthPoints"); //5
    columns->setProperty("PreferredWidth",150);

    cell = main_table->querySubObject("Cell(Row,Column)",1,1);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","№");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    for(int i=1;i<5;i++)
    {
        cell = main_table->querySubObject("Cell(Row,Column)",i+1,1);
        range_cell = cell->querySubObject("Range()");
        range_cell->setProperty("Text",i);
        font = range_cell->querySubObject("Font");
        font->setProperty("Size",10);
        font->setProperty("Name","Times New Roman");
        paragraph = range_cell->querySubObject("ParagraphFormat");
        paragraph->setProperty("Alignment","wdAlignParagraphCenter");
        paragraph->setProperty("SpaceAfter",0);
    }

    cell = main_table->querySubObject("Cell(Row,Column)",1,2);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Фамилия Имя Отчество");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",1,3);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Город");
   font = range_cell->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",1,4);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Категория");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",1,5);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Должность");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",1,6);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Оценка");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);




    //ГЛАВНЫЙ СУДЬЯ

    cell = main_table->querySubObject("Cell(Row,Column)",2,2);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",main_j_c[0]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");

    cell = main_table->querySubObject("Cell(Row,Column)",2,3);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",main_j_c[1]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",2,4);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",main_j_c[2]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",2,5);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Главный судья");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");




    //ЗАМ ГЛАВНОГО СУДЬИ

    cell = main_table->querySubObject("Cell(Row,Column)",3,2);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",deputy_m_j_c[0]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");

    cell = main_table->querySubObject("Cell(Row,Column)",3,3);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",deputy_m_j_c[1]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",3,4);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",deputy_m_j_c[2]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",3,5);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Зам. главного судьи");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");



    // ГЛАВНЫЙ СЕКРЕТАРЬ
    cell = main_table->querySubObject("Cell(Row,Column)",4,2);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",main_s_c[0]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");

    cell = main_table->querySubObject("Cell(Row,Column)",4,3);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",main_s_c[1]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",4,4);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",main_s_c[2]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",4,5);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Главный секретарь");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");



    //СТАРШИЙ СУДЬЯ
    cell = main_table->querySubObject("Cell(Row,Column)",5,2);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",oldest_j_c[0]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");

    cell = main_table->querySubObject("Cell(Row,Column)",5,3);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",oldest_j_c[1]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",5,4);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text",oldest_j_c[2]);
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");
    paragraph = range_cell->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    cell = main_table->querySubObject("Cell(Row,Column)",5,5);
    range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","Старший судья");
    font = range_cell->querySubObject("Font");
    font->setProperty("Size",10);
    font->setProperty("Name","Times New Roman");


    rangeData->dynamicCall("InsertParagraphAfter()");

    int start_range = 1001;
    int end_range = 1100;

    Judge = nullptr;
    main_table = nullptr;
    cell=nullptr;
    delete main_table;
    delete cell;
    delete Judge;

    for (int brigada=0;brigada<imu.count();brigada++) {
        QAxObject *rangeData = NewDoc->querySubObject("Range()");
        rangeData->dynamicCall("SetRange(int,int)",start_range,end_range);
        QString br;
        br.setNum(brigada+1);
        rangeData->setProperty("Text","Бригада №"+br);
        QAxObject *paragraph = rangeData->querySubObject("ParagraphFormat");
        paragraph->setProperty("Alignment","wdAlignParagraphCenter");
        rangeData->dynamicCall("InsertParagraphAfter()");
        QAxObject *font = rangeData->querySubObject("Font");
        font->setProperty("Size",10);
        font->setProperty("Name","Times New Roman");
        start_range+=100;
        end_range+=100;

        query.prepare("SELECT COUNT(*) FROM "+judges_key+" WHERE Бригада=:br");
        query.bindValue(":br",imu[brigada]);
        query.exec();
        int count_brig=0;
        while(query.next())
        {
            count_brig=query.value(0).toInt();

        }
        rangeData = NewDoc->querySubObject("Range()");
        rangeData->dynamicCall("SetRange(int,int)",start_range,end_range);
       QAxObject *table_crew = new QAxObject();
        table_crew = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", rangeData->asVariant(), count_brig, 6, 1, 2);
       QAxObject *columns = new QAxObject();
        columns = table_crew->querySubObject("Columns(Index)",1); //1
        columns->setProperty("PreferredWidthType","wdPreferredWidthPoints");
        columns->setProperty("PreferredWidth",25);
        columns = table_crew->querySubObject("Columns(Index)",2);
        columns->setProperty("PreferredWidthType","wdPreferredWidthPoints"); //2
        columns->setProperty("PreferredWidth",300);
        columns = table_crew->querySubObject("Columns(Index)",5);
        columns->setProperty("PreferredWidthType","wdPreferredWidthPoints"); //5
       columns->setProperty("PreferredWidth",150);
        start_range+=500;
        end_range+=500;

        int row=1;

        for(int i=0;i<poses.count();i++)
        {
            QString pos = poses.at(i);


            query.prepare("SELECT * FROM "+judges_key+" WHERE Бригада=:br AND Должность=:r");
            query.bindValue(":br",imu[brigada]);
            query.bindValue(":r",pos);
            query.exec();


            while (query.next()) {
                QAxObject *cell = table_crew->querySubObject("Cell(Row,Column)",row,1);
                QAxObject *data = cell->querySubObject("Range()");
                data->dynamicCall("Text",row);
                QAxObject *font = data->querySubObject("Font");
                font->setProperty("Size",10);
                font->setProperty("Name","Times New Roman");



                QAxObject *cell2 = table_crew->querySubObject("Cell(Row,Column)",row,2);
                QAxObject *data2 = cell2->querySubObject("Range()");
                data2->dynamicCall("Text",query.value(0).toString()+" "+query.value(1).toString()+" "+query.value(2).toString());
                QAxObject *font2 = data2->querySubObject("Font");
                font2->setProperty("Size",10);
                font2->setProperty("Name","Times New Roman");
                QAxObject *paragraph = data2->querySubObject("ParagraphFormat");
                paragraph->setProperty("Alignment","wdAlignParagraphLeft");
                cell2->setProperty("WordWrap","True");


                QAxObject *cell3 = table_crew->querySubObject("Cell(Row,Column)",row,4);
                QAxObject *data3 = cell3->querySubObject("Range()");
                data3->setProperty("Text",query.value(6).toString());
                QAxObject *font3 = data3->querySubObject("Font");
                font3->setProperty("Size",10);
                font3->setProperty("Name","Times New Roman");

                QAxObject *cell4 = table_crew->querySubObject("Cell(Row,Column)",row,3);
                QAxObject *data4 = cell4->querySubObject("Range()");
                data4->setProperty("Text",query.value(3).toString());
                QAxObject *font4 = data4->querySubObject("Font");
                font4->setProperty("Size",10);
                font4->setProperty("Name","Times New Roman");

                QAxObject *cell5 = table_crew->querySubObject("Cell(Row,Column)",row,5);
                QAxObject *data5 = cell5->querySubObject("Range()");
                data5->setProperty("Text",pos);
                QAxObject *font5 = data5->querySubObject("Font");
                font5->setProperty("Size",10);
                font5->setProperty("Name","Times New Roman");
                QAxObject *paragraph5 = data5->querySubObject("ParagraphFormat");
                paragraph5->setProperty("Alignment","wdAlignParagraphLeft");
                row+=1;
            }
        }
        start_range+=100;
        end_range+=100;

  }
    QAxObject *Range = NewDoc->querySubObject("Range()");
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    QString text = "Главный судья ______________________ "+main_j_c[0] + " ("+main_j_c[3] +", "+main_j_c[2]+")";
    Range->setProperty("Text",text);
    QAxObject *font22 = Range->querySubObject("Font");
    font22->setProperty("Size",11);
    font22->setProperty("Name","Times New Roman");
    QAxObject *align = Range->querySubObject("ParagraphFormat");
    align->setProperty("Alignment","wdAlignParagraphLeft");

    start_range+=100;
    end_range+=100;

    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");


    QAxObject *Range2 = NewDoc->querySubObject("Range()");
    Range2->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Зам. главного судьи __________________ "+deputy_m_j_c[0] + " ("+deputy_m_j_c[3] +", "+deputy_m_j_c[2]+")";
    Range2->setProperty("Text",text);
    QAxObject *font23 = Range2->querySubObject("Font");
    font23->setProperty("Size",11);
    font23->setProperty("Name","Times New Roman");
    QAxObject *align2 = Range2->querySubObject("ParagraphFormat");
    align2->setProperty("Alignment","wdAlignParagraphLeft");

    start_range+=100;
    end_range+=100;

    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");
     Range2->dynamicCall("InsertParagraphAfter()");


    QAxObject *Range3 = NewDoc->querySubObject("Range()");
    Range3->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Главный секретарь  ___________________ "+main_s_c[0] + " ("+main_s_c[3] +", "+main_s_c[2]+")";
    Range3->setProperty("Text",text);
    QAxObject *font33 = Range3->querySubObject("Font");
    font33->setProperty("Size",11);
    font33->setProperty("Name","Times New Roman");
    QAxObject *align3 = Range3->querySubObject("ParagraphFormat");
    align3->setProperty("Alignment","wdAlignParagraphLeft");



    WordApp->setProperty("Visible",true);

}

void ended_competition::on_generate_out_members_clicked()
{
    QString count_teams;
    query.exec("SELECT COUNT(DISTINCT Организация) FROM "+members_key);
    while (query.next()) {
        count_teams = query.value(0).toString();
    }
    QAxObject *WordApp = new QAxObject("Word.Application");
    QAxObject *WordDoc = WordApp->querySubObject("Documents()");
    QAxObject *NewDoc = WordDoc->querySubObject("Add()");

    QAxObject *page_setup = NewDoc->querySubObject("PageSetup()");
    page_setup->setProperty("LeftMargin",35);
    page_setup->setProperty("RightMargin",30);
    page_setup->setProperty("TopMargin",40);
    page_setup->setProperty("BottomMargin",40);

    QAxObject *rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",0,100);
    rangeData->setProperty("Text",name_c);

    QAxObject *font = rangeData->querySubObject("Font");
    font->setProperty("Size",12);
    font->setProperty("Name","Times New Roman");
    QAxObject *paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    rangeData->dynamicCall("InsertParagraphAfter()");

    rangeData->clear();
    QAxObject *tables = NewDoc->querySubObject("Tables()");
    rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",101,200);
    QAxObject *Judge = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", rangeData->asVariant(), 1, 1, 1, 2);
    QAxObject *cell = Judge->querySubObject("Cell(Row,Column)",1,1);
    QAxObject *shade = cell->querySubObject("Shading");
    shade->setProperty("BackgroundPatternColor","wdColorGray20");
    QAxObject *range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","СПРАВКА ПО ТУРНИРУ");
    font = range_cell->querySubObject("Font");
    font->setProperty("Name","Times New Roman");
    font->setProperty("Size",11);
    font->setProperty("Bold",true);

    font->clear();
    rangeData->clear();
    paragraph->clear();

    rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",201,300);
    rangeData->setProperty("Text",place_c+" "+data_c);
    font = rangeData->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphLeft");
    paragraph->setProperty("SpaceAfter",0);
    rangeData->dynamicCall("InsertParagraphAfter()");
    rangeData->dynamicCall("InsertParagraphAfter()");


    QAxObject *range = NewDoc->querySubObject("Range()");
    range->dynamicCall("SetRange(int,int)",301,400);
    QString text = "Главный судья: "+main_j_c[0]+" ("+main_j_c[3]+", "+main_j_c[2]+")";
    range->setProperty("Text",text);
    QAxObject *fon = range->querySubObject("Font");
    fon->setProperty("Size",11);
    fon->setProperty("Name","Times New Roman");
    range->dynamicCall("InsertParagraphAfter()");
    range->dynamicCall("InsertParagraphAfter()");

    QAxObject *sec_range = NewDoc->querySubObject("Range()");
    sec_range->dynamicCall("SetRange(int,int)",401,500);
    QString text2 = "Главный секретарь: "+main_s_c[0]+" ("+main_s_c[3]+", "+main_s_c[2]+")";
    sec_range->setProperty("Text",text2);
    QAxObject *sec_font = sec_range->querySubObject("Font");
    sec_font->setProperty("Name","Times New Roman");
    sec_font->setProperty("Size",11);

    sec_range->dynamicCall("InsertParagraphAfter()");
    sec_range->dynamicCall("InsertParagraphAfter()");


    QAxObject *table_range = NewDoc->querySubObject("Range()");
    table_range->dynamicCall("SetRange(int,int)",401,500);
    QAxObject *table_inf = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", table_range->asVariant(), 5, 2, 1, 1);

    QAxObject *column = table_inf->querySubObject("Columns(Index)",1);
    column->setProperty("PreferredWidthType","wdPreferredWidthPoints");
    column->setProperty("PreferredWidth",80);

    column = table_inf->querySubObject("Columns(Index)",2);
    column->setProperty("PreferredWidthType","wdPreferredWidthPoints");
    column->setProperty("PreferredWidth",100);

    QAxObject *cell_inf = table_inf->querySubObject("Cell(Row,Column)",1,2);
    QAxObject *range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Всего");
    QAxObject *cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",2,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Участников");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",3,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Регионов");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",4,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Городов");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",5,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Судей");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",2,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",members_count);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",3,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",number_s_c);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",4,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",number_c_c);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",5,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",judges_count);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    QAxObject *range_after_inf = NewDoc->querySubObject("Range()");
    range_after_inf->dynamicCall("SetRange(int,int)",501,600);
    range_after_inf->setProperty("Text","Регионы: "+subjects_c);
    QAxObject *font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Name","Times New Roman");

    range_after_inf->dynamicCall("InsertParagraphAfter()");

    range_after_inf->dynamicCall("SetRange(int,int)",601,700);
    range_after_inf->setProperty("Text","Города: "+citys_c);
    font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Name","Times New Roman");

    range_after_inf->dynamicCall("InsertParagraphAfter()");

    range_after_inf->dynamicCall("SetRange(int,int)",701,800);
    range_after_inf->setProperty("Text","Команд: "+count_teams);
    font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Name","Times New Roman");

    range_after_inf->dynamicCall("InsertParagraphAfter()");
    range_after_inf->dynamicCall("InsertParagraphAfter()");

    range_after_inf->dynamicCall("SetRange(int,int)",701,800);
    range_after_inf->setProperty("Text","Результаты:");
    font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Bold",true);
    font_after_inf->setProperty("Name","Times New Roman");

    QAxObject *range_winn = NewDoc->querySubObject("Range()");
    range_winn->dynamicCall("SetRange(int,int)",801,900);
    QAxObject *table_winn = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_winn->asVariant(), 1, 4, 1, 2);

    QAxObject *cell_win = table_winn->querySubObject("Cell(Row,Column)",1,1);
    QAxObject *range_win = cell_win->querySubObject("Range()");
    range_win->setProperty("Text","ПРИЗЕРЫ");
    QAxObject *par = range_win->querySubObject("ParagraphFormat");
    par->setProperty("Alignment","wdAlignParagraphCenter");
    QAxObject *font_win = range_win->querySubObject("Font");
    font_win->setProperty("Bold",true);
    font_win->setProperty("Size",11);
    font_win->setProperty("Name","Times New Roman");
    QAxObject *shade_win = cell_win->querySubObject("Shading");
    shade_win->setProperty("BackgroundPatternColor","wdColorGray20");

    cell_win = table_winn->querySubObject("Cell(Row,Column)",1,2);
    range_win = cell_win->querySubObject("Range()");
    range_win->setProperty("Text","1 место");
    par = range_win->querySubObject("ParagraphFormat");
    par->setProperty("Alignment","wdAlignParagraphCenter");
    font_win = range_win->querySubObject("Font");
    font_win->setProperty("Bold",true);
    font_win->setProperty("Size",11);
    font_win->setProperty("Name","Times New Roman");
    shade_win = cell_win->querySubObject("Shading");
    shade_win->setProperty("BackgroundPatternColor","wdColorGray20");

    cell_win = table_winn->querySubObject("Cell(Row,Column)",1,3);
    range_win = cell_win->querySubObject("Range()");
    range_win->setProperty("Text","2 место");
    par = range_win->querySubObject("ParagraphFormat");
    par->setProperty("Alignment","wdAlignParagraphCenter");
    font_win = range_win->querySubObject("Font");
    font_win->setProperty("Bold",true);
    font_win->setProperty("Size",11);
    font_win->setProperty("Name","Times New Roman");
    shade_win = cell_win->querySubObject("Shading");
    shade_win->setProperty("BackgroundPatternColor","wdColorGray20");

    cell_win = table_winn->querySubObject("Cell(Row,Column)",1,4);
    range_win = cell_win->querySubObject("Range()");
    range_win->setProperty("Text","3 место");
    par = range_win->querySubObject("ParagraphFormat");
    par->setProperty("Alignment","wdAlignParagraphCenter");
    font_win = range_win->querySubObject("Font");
    font_win->setProperty("Bold",true);
    font_win->setProperty("Size",11);
    font_win->setProperty("Name","Times New Roman");
    shade_win = cell_win->querySubObject("Shading");
    shade_win->setProperty("BackgroundPatternColor","wdColorGray20");






    int count_cat = ui->categorys_view->model()->rowCount();

    int start_range = 901;
    int end_range = 900+(count_cat*100);

    QAxObject *range_for_table_w = NewDoc->querySubObject("Range()");
    range_for_table_w->dynamicCall("SetRange(int,int)",start_range,end_range);
    QAxObject *table_for_winner = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_for_table_w->asVariant(), ui->categorys_view->model()->rowCount(), 4, 1, 2);

    QAxObject *column_winn = table_for_winner->querySubObject("Columns(Index)",1);
    column_winn->setProperty("PreferredWidthType","wdPreferredWidthPoints");
    column_winn->setProperty("PreferredWidth",80);
    for (int row=0;row<ui->categorys_view->model()->rowCount();row++) {
        QAxObject *cell_cat = table_for_winner->querySubObject("Cell(Row,Column)",row+1,1);
        QAxObject *range_cat = cell_cat->querySubObject("Range()");
        QAxObject *font_cat = range_cat->querySubObject("Font");
        font_cat->setProperty("Size",10);
        font_cat->setProperty("Name","Times New Roman");
        QAxObject *par_cat = range_cat->querySubObject("ParagraphFormat");
        par_cat->setProperty("Alignment","wdAlignParagraphCenter");
        range_cat->setProperty("Text",ui->categorys_view->model()->data(ui->categorys_view->model()->index(row,6)).toString());

        query.prepare("SELECT * FROM "+members_key+" WHERE Категория=:cat AND Место=:place");
        query.bindValue(":cat",ui->categorys_view->model()->data(ui->categorys_view->model()->index(row,6)).toString());
        query.bindValue(":place",1);
        query.exec();
        QString last_name;
        QString first_name;
        QString patron_name;
        QString city;
        QString trainer;
        while(query.next())
        {
            last_name = query.value(0).toString();
            first_name = query.value(1).toString();
            patron_name = query.value(2).toString();
            city = query.value(11).toString();
            trainer = query.value(9).toString();
        }

        QAxObject *cell = table_for_winner->querySubObject("Cell(Row,Column)",row+1,2);
        QAxObject *range_cell = cell->querySubObject("Range()");
        QAxObject *font = range_cell->querySubObject("Font");
        font->setProperty("Size",10);
        font->setProperty("Name","Times New Roman");
        QAxObject *par_cell = range_cell->querySubObject("ParagraphFormat");
        par_cell->setProperty("Alignment","wdAlignParagraphCenter");
        QString text = last_name+" "+first_name+" "+patron_name +"\n"+city+"\n"+trainer;
        range_cell->setProperty("Text",text);

        last_name.clear();
        first_name.clear();
        patron_name.clear();
        city.clear();
        trainer.clear();

        query.prepare("SELECT * FROM "+members_key+" WHERE Категория=:cat AND Место=:place");
        query.bindValue(":cat",ui->categorys_view->model()->data(ui->categorys_view->model()->index(row,6)).toString());
        query.bindValue(":place",2);
        query.exec();
        while(query.next())
        {
            last_name = query.value(0).toString();
            first_name = query.value(1).toString();
            patron_name = query.value(2).toString();
            city = query.value(11).toString();
            trainer = query.value(9).toString();
        }

        cell = table_for_winner->querySubObject("Cell(Row,Column)",row+1,3);
        range_cell = cell->querySubObject("Range()");
        font = range_cell->querySubObject("Font");
        font->setProperty("Size",10);
        font->setProperty("Name","Times New Roman");
        par_cell = range_cell->querySubObject("ParagraphFormat");
        par_cell->setProperty("Alignment","wdAlignParagraphCenter");
        text = last_name+" "+first_name+" "+patron_name +"\n"+city+"\n"+trainer;
        range_cell->setProperty("Text",text);


        last_name.clear();
        first_name.clear();
        patron_name.clear();
        city.clear();
        trainer.clear();

        query.prepare("SELECT * FROM "+members_key+" WHERE Категория=:cat AND Место=:place");
        query.bindValue(":cat",ui->categorys_view->model()->data(ui->categorys_view->model()->index(row,6)).toString());
        query.bindValue(":place",3);
        query.exec();
        while(query.next())
        {
            last_name = query.value(0).toString();
            first_name = query.value(1).toString();
            patron_name = query.value(2).toString();
            city = query.value(11).toString();
            trainer = query.value(9).toString();
        }

        cell = table_for_winner->querySubObject("Cell(Row,Column)",row+1,4);
        range_cell = cell->querySubObject("Range()");
        font = range_cell->querySubObject("Font");
        font->setProperty("Size",10);
        font->setProperty("Name","Times New Roman");
        par_cell = range_cell->querySubObject("ParagraphFormat");
        par_cell->setProperty("Alignment","wdAlignParagraphCenter");
        text = last_name+" "+first_name+" "+patron_name +"\n"+city+"\n"+trainer;
        range_cell->setProperty("Text",text);
    }


    start_range+=400;
    end_range+=400;





    QAxObject *Range = NewDoc->querySubObject("Range()");
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Главный судья ______________________ "+main_j_c[0] + " ("+main_j_c[3] +", "+main_j_c[2]+")";
    Range->setProperty("Text",text);
    QAxObject *font22 = Range->querySubObject("Font");
    font22->setProperty("Size",11);
    font22->setProperty("Name","Times New Roman");
    QAxObject *align = Range->querySubObject("ParagraphFormat");
    align->setProperty("Alignment","wdAlignParagraphLeft");

    start_range+=100;
    end_range+=100;

    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");


    QAxObject *Range2 = NewDoc->querySubObject("Range()");
    Range2->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Зам. главного судьи __________________ "+deputy_m_j_c[0] + " ("+deputy_m_j_c[3] +", "+deputy_m_j_c[2]+")";
    Range2->setProperty("Text",text);
    QAxObject *font23 = Range2->querySubObject("Font");
    font23->setProperty("Size",11);
    font23->setProperty("Name","Times New Roman");
    QAxObject *align2 = Range2->querySubObject("ParagraphFormat");
    align2->setProperty("Alignment","wdAlignParagraphLeft");

    start_range+=100;
    end_range+=100;

    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");
     Range2->dynamicCall("InsertParagraphAfter()");


    QAxObject *Range3 = NewDoc->querySubObject("Range()");
    Range3->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Главный секретарь  ___________________ "+main_s_c[0] + " ("+main_s_c[3] +", "+main_s_c[2]+")";
    Range3->setProperty("Text",text);
    QAxObject *font33 = Range3->querySubObject("Font");
    font33->setProperty("Size",11);
    font33->setProperty("Name","Times New Roman");
    QAxObject *align3 = Range3->querySubObject("ParagraphFormat");
    align3->setProperty("Alignment","wdAlignParagraphLeft");


     WordApp->setProperty("Visible",true);

}

void ended_competition::on_generate_all_members_clicked()
{

    QString count_teams;
    query.exec("SELECT COUNT(DISTINCT Организация) FROM "+members_key);
    while (query.next()) {
        count_teams = query.value(0).toString();
    }
    QAxObject *WordApp = new QAxObject("Word.Application");
    QAxObject *WordDoc = WordApp->querySubObject("Documents()");
    QAxObject *NewDoc = WordDoc->querySubObject("Add()");

    QAxObject *page_setup = NewDoc->querySubObject("PageSetup()");
    page_setup->setProperty("LeftMargin",35);
    page_setup->setProperty("RightMargin",30);
    page_setup->setProperty("TopMargin",40);
    page_setup->setProperty("BottomMargin",40);

    QAxObject *rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",0,100);
    rangeData->setProperty("Text",name_c);

    QAxObject *font = rangeData->querySubObject("Font");
    font->setProperty("Size",12);
    font->setProperty("Name","Times New Roman");
    QAxObject *paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);

    rangeData->dynamicCall("InsertParagraphAfter()");


    rangeData->clear();
    QAxObject *tables = NewDoc->querySubObject("Tables()");
    rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",101,200);
    QAxObject *Judge = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", rangeData->asVariant(), 1, 1, 1, 2);
    QAxObject *cell = Judge->querySubObject("Cell(Row,Column)",1,1);
    QAxObject *shade = cell->querySubObject("Shading");
    shade->setProperty("BackgroundPatternColor","wdColorGray20");
    QAxObject *range_cell = cell->querySubObject("Range()");
    range_cell->setProperty("Text","СПРАВКА ПО ТУРНИРУ");
    font = range_cell->querySubObject("Font");
    font->setProperty("Name","Times New Roman");
    font->setProperty("Size",11);
    font->setProperty("Bold",true);

    font->clear();
    rangeData->clear();
    paragraph->clear();

    rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",201,300);
    rangeData->setProperty("Text",place_c+" "+data_c);
    font = rangeData->querySubObject("Font");
    font->setProperty("Size",11);
    font->setProperty("Name","Times New Roman");
    paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphLeft");
    paragraph->setProperty("SpaceAfter",0);
    rangeData->dynamicCall("InsertParagraphAfter()");
    rangeData->dynamicCall("InsertParagraphAfter()");


    QAxObject *range = NewDoc->querySubObject("Range()");
    range->dynamicCall("SetRange(int,int)",301,400);
    QString text = "Главный судья: "+main_j_c[0]+" ("+main_j_c[3]+", "+main_j_c[2]+")";
    range->setProperty("Text",text);
    QAxObject *fon = range->querySubObject("Font");
    fon->setProperty("Size",11);
    fon->setProperty("Name","Times New Roman");
    range->dynamicCall("InsertParagraphAfter()");
    range->dynamicCall("InsertParagraphAfter()");

    QAxObject *sec_range = NewDoc->querySubObject("Range()");
    sec_range->dynamicCall("SetRange(int,int)",401,500);
    QString text2 = "Главный секретарь: "+main_s_c[0]+" ("+main_s_c[3]+", "+main_s_c[2]+")";
    sec_range->setProperty("Text",text2);
    QAxObject *sec_font = sec_range->querySubObject("Font");
    sec_font->setProperty("Name","Times New Roman");
    sec_font->setProperty("Size",11);

    sec_range->dynamicCall("InsertParagraphAfter()");
    sec_range->dynamicCall("InsertParagraphAfter()");


    QAxObject *table_range = NewDoc->querySubObject("Range()");
    table_range->dynamicCall("SetRange(int,int)",401,500);
    QAxObject *table_inf = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", table_range->asVariant(), 5, 2, 1, 1);

    QAxObject *column = table_inf->querySubObject("Columns(Index)",1);
    column->setProperty("PreferredWidthType","wdPreferredWidthPoints");
    column->setProperty("PreferredWidth",80);

    column = table_inf->querySubObject("Columns(Index)",2);
    column->setProperty("PreferredWidthType","wdPreferredWidthPoints");
    column->setProperty("PreferredWidth",100);

    QAxObject *cell_inf = table_inf->querySubObject("Cell(Row,Column)",1,2);
    QAxObject *range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Всего");
    QAxObject *cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",2,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Участников");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",3,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Регионов");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",4,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Городов");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",5,1);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text","Судей");
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",2,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",members_count);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",3,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",number_s_c);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",4,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",number_c_c);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    cell_inf = table_inf->querySubObject("Cell(Row,Column)",5,2);
    range_cell_inf = cell_inf->querySubObject("Range()");
    range_cell_inf->setProperty("Text",judges_count);
    cell_font = range_cell_inf->querySubObject("Font");
    cell_font->setProperty("Size",11);
    cell_font->setProperty("Name","Times New Roman");

    QAxObject *range_after_inf = NewDoc->querySubObject("Range()");
    range_after_inf->dynamicCall("SetRange(int,int)",501,600);
    range_after_inf->setProperty("Text","Регионы: "+subjects_c);
    QAxObject *font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Name","Times New Roman");

    range_after_inf->dynamicCall("InsertParagraphAfter()");

    range_after_inf->dynamicCall("SetRange(int,int)",601,700);
    range_after_inf->setProperty("Text","Города: "+citys_c);
    font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Name","Times New Roman");

    range_after_inf->dynamicCall("InsertParagraphAfter()");

    range_after_inf->dynamicCall("SetRange(int,int)",701,800);
    range_after_inf->setProperty("Text","Команд: "+count_teams);
    font_after_inf = range_after_inf->querySubObject("Font");
    font_after_inf->setProperty("Size",11);
    font_after_inf->setProperty("Name","Times New Roman");

    range_after_inf->dynamicCall("InsertParagraphAfter()");
    range_after_inf->dynamicCall("InsertParagraphAfter()");

    QAxObject *range_table_main = NewDoc->querySubObject("Range()");
    range_table_main->dynamicCall("SetRange(int,int)",801,900);
    QAxObject *table_main = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_table_main->asVariant(),1, 1, 1, 2);
    QAxObject *cell_table_main = table_main->querySubObject("Cell(Row,Column)",1,1);
    QAxObject *shading_cell_table_main = cell_table_main->querySubObject("Shading");
    shading_cell_table_main->setProperty("BackgroundPatternColor","wdColorGray20");
    QAxObject *range_cell_table_main = cell_table_main->querySubObject("Range()");
    range_cell_table_main->setProperty("Text","УЧАСТНИКИ");
    QAxObject *par_r_c_t_m = range_cell_table_main->querySubObject("ParagraphFormat");
    par_r_c_t_m->setProperty("Alignment","wdAlignParagraphCenter");
    QAxObject *font_r_c_t_m = range_cell_table_main->querySubObject("Font");
    font_r_c_t_m->setProperty("Size",11);
    font_r_c_t_m->setProperty("Bold",true);
    font_r_c_t_m->setProperty("Name","TimesNewRoman");

    int start_range = 901;
    int end_range = 1000;

    bool first_table_was_generate = false;
    for (int cat = 0; cat < ui->categorys_view->model()->rowCount(); cat++) {

        query.prepare("SELECT COUNT(*) FROM "+members_key+" WHERE Категория=:categ");
        query.bindValue(":categ",ui->categorys_view->model()->data(ui->categorys_view->model()->index(cat,6)).toString());
        query.exec();
        int count_mem=0;
        while (query.next())
        {
            count_mem = query.value(0).toInt();
        }

        QAxObject *categoria = NewDoc->querySubObject("Range()");
        categoria->dynamicCall("SetRange(int,int)",start_range,end_range);
        categoria->setProperty("Text",ui->categorys_view->model()->data(ui->categorys_view->model()->index(cat,6)).toString());
        QAxObject *font_categoria = categoria->querySubObject("Font");
        font_categoria->setProperty("Size",11);
        font_categoria->setProperty("Name","Times New Roman");
        QAxObject *par_categoria = categoria->querySubObject("ParagraphFormat");
        par_categoria->setProperty("Alignment","wdAlignParagraphCenter");

        categoria->dynamicCall("InsertParagraphAfter()");

        start_range+=100;
        end_range+=100;

        if (first_table_was_generate==false)
        {
            QAxObject *range_table_mem = NewDoc->querySubObject("Range()");
            range_table_mem->dynamicCall("SetRange(int,int)",start_range,end_range);
            QAxObject *table_member = new QAxObject;
            table_member = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_table_mem->asVariant(),1, 6, 1, 2);

            QAxObject *cell = table_member->querySubObject("Cell(Row,Column)",1,1);
            QAxObject *range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text","\n№");
            QAxObject *font = range_cell->querySubObject("Font");
            font->setProperty("Size",11);
            font->setProperty("Name","Times New Roman");
            QAxObject *paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",1,2);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text","Фамилия");
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",11);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",1,3);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text","Имя");
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",11);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",1,4);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text","Отчество");
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",11);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",1,5);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text","Город");
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",11);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",1,6);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text","Руководитель");
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",11);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);










            first_table_was_generate=true;
        }

        start_range+=50*count_mem;
        end_range+=50*count_mem;
        QAxObject *range_table_mem = NewDoc->querySubObject("Range()");
        range_table_mem->dynamicCall("SetRange(int,int)",start_range,end_range);
        QAxObject *table_member = new QAxObject;
        table_member = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_table_mem->asVariant(),count_mem, 6, 1, 2);
        QAxObject *columns = table_member->querySubObject("Columns(Index)",1); //1
        columns->setProperty("PreferredWidthType","wdPreferredWidthPoints");
        columns->setProperty("PreferredWidth",25);






        query.prepare("SELECT * FROM "+members_key+" WHERE Категория=:cat");
        query.bindValue(":cat",ui->categorys_view->model()->data(ui->categorys_view->model()->index(cat,6)).toString());
        query.exec();
        int row = 1;
        while(query.next())
        {
            QAxObject *cell = table_member->querySubObject("Cell(Row,Column)",row,1);
            QAxObject *range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text",row);
            QAxObject *font = range_cell->querySubObject("Font");
            font->setProperty("Size",10);
            font->setProperty("Name","Times New Roman");
            QAxObject *paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);


            cell = table_member->querySubObject("Cell(Row,Column)",row,2);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text",query.value(0).toString());
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",10);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",row,3);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text",query.value(1).toString());
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",10);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",row,4);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text",query.value(2).toString());
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",10);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",row,5);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text",query.value(11).toString());
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",10);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);

            cell = table_member->querySubObject("Cell(Row,Column)",row,6);
            range_cell = cell->querySubObject("Range()");
            range_cell->setProperty("Text",query.value(9).toString());
            font = range_cell->querySubObject("Font");
            font->setProperty("Size",10);
            font->setProperty("Name","Times New Roman");
            paragraph = range_cell->querySubObject("ParagraphFormat");
            paragraph->setProperty("Alignment","wdAlignParagraphCenter");
            paragraph->setProperty("SpaceAfter",0);


            row+=1;
        }


        start_range+=100;
        end_range+=100;
    }

    QAxObject *Range = NewDoc->querySubObject("Range()");
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    Range->dynamicCall("InsertParagraph()");
    start_range+=100;
    end_range+=100;
    Range->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Главный судья ______________________ "+main_j_c[0] + " ("+main_j_c[3] +", "+main_j_c[2]+")";
    Range->setProperty("Text",text);
    QAxObject *font22 = Range->querySubObject("Font");
    font22->setProperty("Size",11);
    font22->setProperty("Name","Times New Roman");
    QAxObject *align = Range->querySubObject("ParagraphFormat");
    align->setProperty("Alignment","wdAlignParagraphLeft");

    start_range+=100;
    end_range+=100;

    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");
    Range->dynamicCall("InsertParagraphAfter()");


    QAxObject *Range2 = NewDoc->querySubObject("Range()");
    Range2->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Зам. главного судьи __________________ "+deputy_m_j_c[0] + " ("+deputy_m_j_c[3] +", "+deputy_m_j_c[2]+")";
    Range2->setProperty("Text",text);
    QAxObject *font23 = Range2->querySubObject("Font");
    font23->setProperty("Size",11);
    font23->setProperty("Name","Times New Roman");
    QAxObject *align2 = Range2->querySubObject("ParagraphFormat");
    align2->setProperty("Alignment","wdAlignParagraphLeft");

    start_range+=100;
    end_range+=100;

    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");
    Range2->dynamicCall("InsertParagraphAfter()");


    QAxObject *Range3 = NewDoc->querySubObject("Range()");
    Range3->dynamicCall("SetRange(int,int)",start_range,end_range);
    text = "Главный секретарь  ___________________ "+main_s_c[0] + " ("+main_s_c[3] +", "+main_s_c[2]+")";
    Range3->setProperty("Text",text);
    QAxObject *font33 = Range3->querySubObject("Font");
    font33->setProperty("Size",11);
    font33->setProperty("Name","Times New Roman");
    QAxObject *align3 = Range3->querySubObject("ParagraphFormat");
    align3->setProperty("Alignment","wdAlignParagraphLeft");

        WordApp->setProperty("Visible",true);
}

void ended_competition::closeEvent(QCloseEvent *event)
{
    Settings->beginGroup("Geometry");
    Settings->setValue("GeometryEnded",geometry());
    Settings->endGroup();
	emit get_show_main();
	this->close();
    event->accept();
}

void ended_competition::on_DELETE_clicked()
{
    QMessageBox::StandardButton baton = QMessageBox::question(this,"Удалить?","Удалить мероприятие?\nВосстановить данные будет невозможно",QMessageBox::Yes | QMessageBox::No);
    if (baton==QMessageBox::Yes)
    {
        query.exec("DROP TABLE "+judges_key);
        query.exec("DROP TABLE "+comp_name);
        query.prepare("DELETE FROM competitions WHERE НазваниеСоревнований=:name");
        query.bindValue(":name",name_c);
        query.exec();
        this->close();
    } else if(baton==QMessageBox::No){
        return;
    }
}

void ended_competition::on_catgegories_out_clicked()
{
    QStringList categories;
    for (int i=0;i<ui->categorys_view->model()->rowCount();i++) {
        categories.append(ui->categorys_view->model()->data(ui->categorys_view->model()->index(i,6)).toString());
    }
    bool ok;
    QString categoria = QInputDialog::getItem(this,"Категория для отчета","Выберите категорию для отчета",categories,0,false,&ok);
    if (!ok)
    {
        return;
    }


    QAxObject *WordApp = new QAxObject("Word.Application");
    QAxObject *WordDoc = WordApp->querySubObject("Documents()");
    QAxObject *NewDoc = WordDoc->querySubObject("Add()");

    QAxObject *page_setup = NewDoc->querySubObject("PageSetup()");
    page_setup->setProperty("LeftMargin",15);
    page_setup->setProperty("RightMargin",10);
    page_setup->setProperty("TopMargin",40);
    page_setup->setProperty("BottomMargin",40);

    QAxObject *rangeData = NewDoc->querySubObject("Range()");
    rangeData->dynamicCall("SetRange(int,int)",0,100);
    rangeData->setProperty("Text",name_c);
    QAxObject *font = rangeData->querySubObject("Font");
    font->setProperty("Size",12);
    font->setProperty("Name","Times New Roman");
    QAxObject *paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);



    rangeData->dynamicCall("InsertParagraphAfter()");
    rangeData->dynamicCall("InsertParagraphAfter()");

    rangeData->dynamicCall("SetRange(int,int)",101,200);
    rangeData->setProperty("Text",place_c+" "+data_c);
    paragraph = rangeData->querySubObject("ParagraphFormat");
     paragraph->setProperty("Alignment","wdAlignParagraphLeft");
    paragraph->setProperty("SpaceAfter",0);
    font = rangeData->querySubObject("Font");
    font->setProperty("Size",12);
    font->setProperty("Name","Times New Roman");


    rangeData->dynamicCall("InsertParagraphAfter()");
    rangeData->dynamicCall("InsertParagraphAfter()");


    rangeData->dynamicCall("SetRange(int,int)",201,300);
    rangeData->setProperty("Text",categoria);
    paragraph = rangeData->querySubObject("ParagraphFormat");
    paragraph->setProperty("Alignment","wdAlignParagraphCenter");
    paragraph->setProperty("SpaceAfter",0);
    font = rangeData->querySubObject("Font");
    font->setProperty("Size",12);
    font->setProperty("Name","Times New Roman");








    query.prepare("SELECT COUNT(*) FROM "+comp_name+" WHERE Категория=:cat");
    query.bindValue(":cat",categoria);
    query.exec();

    int count_cat=0;
    while (query.next())
    {
        count_cat = query.value(0).toInt();
    }
   QAxObject *tables = NewDoc->querySubObject("Tables()");
   QAxObject *range_table = NewDoc->querySubObject("Range()");
   int end_range = 301+count_cat*200;
   int start_range =301;

   range_table->dynamicCall("SetRange(int,int)",start_range,end_range);
   QAxObject *category_table = tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", range_table->asVariant(), count_cat+1, 14, 1, 2);
{
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
   data->dynamicCall("Text","Судья 1");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,7);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Судья 2");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,8);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Судья 3");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,9);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Судья 4");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");

   cell = category_table->querySubObject("Cell(Row,Column)",1,10);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Судья 5");
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

   cell = category_table->querySubObject("Cell(Row,Column)",1,14);
   data = cell->querySubObject("Range()");
   data->dynamicCall("Text","Место");
   font = data->querySubObject("Font");
   font->setProperty("Size",10);
   font->setProperty("Name","Times New Roman");
}


  query.prepare("SELECT Фамилия, Имя, Отчество, Город, Руководитель, Судья_1, Судья_2, Судья_3, Судья_4, Судья_5, СреднийБалл, Мин_Балл, Макс_Балл, Место "
                " FROM "+comp_name+" WHERE Категория=:cat ORDER BY Место");

   query.bindValue(":cat",categoria);
   query.exec();
   int row = 2;
   while(query.next())
   {

       QAxObject *cell = category_table->querySubObject("Cell(Row,Column)",row,1);
       QAxObject *data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(0).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,2);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(1).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,3);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(2).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,4);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(3).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,5);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(4).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,6);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(5).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,7);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(6).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,8);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(7).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,9);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(8).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,10);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(9).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,11);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(10).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,12);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(11).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,13);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(12).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");

       cell = category_table->querySubObject("Cell(Row,Column)",row,14);
       data = cell->querySubObject("Range()");
       data->dynamicCall("Text",query.value(13).toString());
       font = data->querySubObject("Font");
       font->setProperty("Size",10);
       font->setProperty("Name","Times New Roman");


       row++;
   }

   start_range = end_range+1;
   end_range+=100;

   QString text;

   QAxObject *Range = NewDoc->querySubObject("Range()");
   Range->dynamicCall("SetRange(int,int)",start_range,end_range);
   Range->dynamicCall("InsertParagraph()");
   start_range+=100;
   end_range+=100;
   Range->dynamicCall("SetRange(int,int)",start_range,end_range);
   Range->dynamicCall("InsertParagraph()");
   start_range+=100;
   end_range+=100;
   Range->dynamicCall("SetRange(int,int)",start_range,end_range);
   Range->dynamicCall("InsertParagraph()");
   start_range+=100;
   end_range+=100;
   Range->dynamicCall("SetRange(int,int)",start_range,end_range);
   text = "Главный судья ______________________ "+main_j_c[0] + " ("+main_j_c[3] +", "+main_j_c[2]+")";
   Range->setProperty("Text",text);
   QAxObject *font22 = Range->querySubObject("Font");
   font22->setProperty("Size",11);
   font22->setProperty("Name","Times New Roman");
   QAxObject *align = Range->querySubObject("ParagraphFormat");
   align->setProperty("Alignment","wdAlignParagraphLeft");

   start_range+=100;
   end_range+=100;

   Range->dynamicCall("InsertParagraphAfter()");
   Range->dynamicCall("InsertParagraphAfter()");
   Range->dynamicCall("InsertParagraphAfter()");
   Range->dynamicCall("InsertParagraphAfter()");


   QAxObject *Range2 = NewDoc->querySubObject("Range()");
   Range2->dynamicCall("SetRange(int,int)",start_range,end_range);
   text = "Зам. главного судьи __________________ "+deputy_m_j_c[0] + " ("+deputy_m_j_c[3] +", "+deputy_m_j_c[2]+")";
   Range2->setProperty("Text",text);
   QAxObject *font23 = Range2->querySubObject("Font");
   font23->setProperty("Size",11);
   font23->setProperty("Name","Times New Roman");
   QAxObject *align2 = Range2->querySubObject("ParagraphFormat");
   align2->setProperty("Alignment","wdAlignParagraphLeft");

   start_range+=100;
   end_range+=100;

   Range2->dynamicCall("InsertParagraphAfter()");
   Range2->dynamicCall("InsertParagraphAfter()");
   Range2->dynamicCall("InsertParagraphAfter()");
   Range2->dynamicCall("InsertParagraphAfter()");


   QAxObject *Range3 = NewDoc->querySubObject("Range()");
   Range3->dynamicCall("SetRange(int,int)",start_range,end_range);
   text = "Главный секретарь  ___________________ "+main_s_c[0] + " ("+main_s_c[3] +", "+main_s_c[2]+")";
   Range3->setProperty("Text",text);
   QAxObject *font33 = Range3->querySubObject("Font");
   font33->setProperty("Size",11);
   font33->setProperty("Name","Times New Roman");
   QAxObject *align3 = Range3->querySubObject("ParagraphFormat");
   align3->setProperty("Alignment","wdAlignParagraphLeft");



        WordApp->setProperty("Visible",true);
}
