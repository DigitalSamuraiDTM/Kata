#include "table.h"
#include "ui_table.h"
#include "QDebug"
#include "QSettings"
Table::Table(QWidget *parent) :
    QWidget (parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);
    Settings = new QSettings("settings.ini",QSettings::IniFormat);
    Settings->beginGroup("Geometry");
    setGeometry(Settings->value("GeometryTable",QRect(500,500,600,600)).toRect());
    Settings->endGroup();
}

Table::~Table()
{
    delete ui;
}

void Table::open_count()
{
    ui->Save_result_2->setEnabled(true);
}

void Table::closeEvent(QCloseEvent *event)
{
    Settings->beginGroup("Geometry");
    Settings->setValue("GeometryTable",geometry());
    Settings->endGroup();
    event->accept();
}

void Table::get_data(double step, int start, int end)
{
        QLayout* lays[5]; //массив элементов layout
        lays[0]=ui->judge_1_l;
        lays[1]=ui->judge_2_l;
        lays[2]=ui->judge_3_l;
        lays[3]=ui->judge_4_l;
        lays[4]=ui->judge_5_l;

        int range = lays[0]->count();
        for (int j=0;j<5;j++) {
            for (int i = 0;i <range ;i++) { //заходим в цикл длинной в подсчитанный layout
                QdynamicsButton *button = qobject_cast<QdynamicsButton*>(lays[j]->itemAt(0)->widget()); //создаем указатель кнопки на которой находится цикл
                button->hide();
                delete button; //удаляем её из памяти
            }
        }

    double repeat = (end-start)*(1/step)+1; //рассчитываем сколько кнопок будет создано в каждом layout'е
    for (int i=0;i<5;i++){
        qdynamicsbutton->down_to_zero(end); //перед каждым layout обновляем коэффициент id кнопки
        for (int j=0;j<repeat;j++) {
            QdynamicsButton *button = new QdynamicsButton(step);
            button->setText(QString::number(button->getID()));
            button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);   //добавляем типаж, чтобы кнопка занимала максимум места
            lays[i]->addWidget(button);                                                                           //добавляем кнопку на layout

            switch (i) {
            case 0:{
                connect(button, SIGNAL(clicked()), this, SLOT(judge_1_baton()));
                break;
            }
            case 1:{
                connect(button, SIGNAL(clicked()), this, SLOT(judge_2_baton())); //накидываем сигнал в зависимости от цикла layout'а
                break;
            }
            case 2:{
                connect(button, SIGNAL(clicked()), this, SLOT(judge_3_baton()));
                break;
            }
            case 3:{
                connect(button, SIGNAL(clicked()), this, SLOT(judge_4_baton()));
                break;
            }
            case 4:{
                connect(button, SIGNAL(clicked()), this, SLOT(judge_5_baton()));
                break;
            }
            }
        }
    }
}

void Table::on_count_button_2_clicked()
{
   all_judge[0] =judge_1;
   all_judge[1]= judge_2;
   all_judge[2]=judge_3;
   all_judge[3]= judge_4;
   all_judge[4]=judge_5;
    min_ball=1000.0;
    max_ball=-1000.0;
    middle_ball=0.0;
    for(int i=0;i<5;i++) //цикл поиска максимума и минимума
    {
        if (min_ball>all_judge[i])
        {
            min_ball=all_judge[i];
        }
        if (max_ball<all_judge[i])
        {
                max_ball=all_judge[i];
        }
    }
    middle_ball=(all_judge[1]+all_judge[2]+all_judge[3]+all_judge[0]+all_judge[4]-min_ball-max_ball); //рассчитываем
    ui->result_label->setNum(middle_ball);
}

void Table::on_break_button_2_clicked()
    {
        QLayout* lays[5]; //такой же массив всех layout
        lays[0]=ui->judge_1_l;
        lays[1]=ui->judge_2_l;
        lays[2]=ui->judge_3_l;
        lays[3]=ui->judge_4_l;
        lays[4]=ui->judge_5_l;
        for (int j=0;j<5;j++) { //в двойном цикле перебираем все кнопки во всех layou
        for (int i = 0;i < ui->judge_5_l->count();i++) //и сбрасываем все кнопки в начальный стиль
        {
            QdynamicsButton *destr_button = qobject_cast<QdynamicsButton*>(lays[j]->itemAt(i)->widget());
            destr_button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                                  "background-color: #e2e2e2;"
                                  "border:1px solid #afafaf}"
                                  "QdynamicsButton:hover{background-color:#FEFEEC;"
                                  "border-color: #FFE900;}"
                                  "QdynamicsButton:pressed{background-color:#F8F8A0;"
                                  "border-color: #FFE900;};");
        }
        }

        ui->result_label->setText("-"); //не забываем вернуть текст на label
}

void Table::judge_1_baton()
    {
        for (int i = 0;i < ui->judge_1_l->count();i++) //цикл по поиску уже нажатой кнопки
        {
            QdynamicsButton *destr_button = qobject_cast<QdynamicsButton*>(ui->judge_1_l->itemAt(i)->widget()); //сбрасываем все кнопки в начальный стиль
            destr_button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                                  "background-color: #e2e2e2;"
                                  "border:1px solid #afafaf}"
                                  "QdynamicsButton:hover{background-color:#FEFEEC;"
                                  "border-color: #FFE900;}"
                                  "QdynamicsButton:pressed{background-color:#F8F8A0;"
                                  "border-color: #FFE900;};");
        }
        QdynamicsButton* button = static_cast<QdynamicsButton*>(sender()); //и накидываем стиль нажатой кнопки на только что нажатую кнопку
        judge_1=button->getID();
        button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                              "background-color: #FEFEEC;"
                              "border:1px solid #FFE900}");
    }

void Table::judge_2_baton()
    {
        for (int i = 0;i < ui->judge_2_l->count();i++)
        {
            QdynamicsButton *destr_button = qobject_cast<QdynamicsButton*>(ui->judge_2_l->itemAt(i)->widget());
            destr_button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                                  "background-color: #e2e2e2;"
                                  "border:1px solid #afafaf}"
                                  "QdynamicsButton:hover{background-color:#FEFEEC;"
                                  "border-color: #FFE900;}"
                                  "QdynamicsButton:pressed{background-color:#F8F8A0;"
                                  "border-color: #FFE900;};");
        }
        QdynamicsButton* button = static_cast<QdynamicsButton*>(sender());
        judge_2=button->getID();
        button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                              "background-color: #FEFEEC;"
                              "border:1px solid #FFE900}");
    }

void Table::judge_3_baton()
    {
        for (int i = 0;i < ui->judge_3_l->count();i++)
        {
            QdynamicsButton *destr_button = qobject_cast<QdynamicsButton*>(ui->judge_3_l->itemAt(i)->widget());
            destr_button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                                  "background-color: #e2e2e2;"
                                  "border:1px solid #afafaf}"
                                  "QdynamicsButton:hover{background-color:#FEFEEC;"
                                  "border-color: #FFE900;}"
                                  "QdynamicsButton:pressed{background-color:#F8F8A0;"
                                  "border-color: #FFE900;};");
        }
        QdynamicsButton* button = static_cast<QdynamicsButton*>(sender());
        judge_3=button->getID();
        button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                              "background-color: #FEFEEC;"
                              "border:1px solid #FFE900}");
    }

void Table::judge_4_baton()
    {
        for (int i = 0;i < ui->judge_4_l->count();i++)
        {
            QdynamicsButton *destr_button = qobject_cast<QdynamicsButton*>(ui->judge_4_l->itemAt(i)->widget());
            destr_button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                                  "background-color: #e2e2e2;"
                                  "border:1px solid #afafaf}"
                                  "QdynamicsButton:hover{background-color:#FEFEEC;"
                                  "border-color: #FFE900;}"
                                  "QdynamicsButton:pressed{background-color:#F8F8A0;"
                                  "border-color: #FFE900;};");
        }
        QdynamicsButton* button = static_cast<QdynamicsButton*>(sender());
        judge_4=button->getID();
        button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                              "background-color: #FEFEEC;"
                              "border:1px solid #FFE900}");
    }

void Table::judge_5_baton()
    {

        for (int i = 0;i < ui->judge_5_l->count();i++)
        {
            QdynamicsButton *destr_button = qobject_cast<QdynamicsButton*>(ui->judge_5_l->itemAt(i)->widget());
            destr_button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                                  "background-color: #e2e2e2;"
                                  "border:1px solid #afafaf}"
                                  "QdynamicsButton:hover{background-color:#FEFEEC;"
                                  "border-color: #FFE900;}"
                                  "QdynamicsButton:pressed{background-color:#F8F8A0;"
                                  "border-color: #FFE900;};");
        }
        QdynamicsButton* button = static_cast<QdynamicsButton*>(sender());
        judge_5=button->getID();
        button->setStyleSheet("QdynamicsButton{font-size: 18px;"
                              "background-color: #FEFEEC;"
                              "border:1px solid #FFE900}");
    }

void Table::on_Save_result_2_clicked()
{

   double *set =all_judge;
   emit push_count_kata( set, min_ball,max_ball,middle_ball);

   on_break_button_2_clicked();
   this->close();
}
