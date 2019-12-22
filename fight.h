#ifndef FIGHT_H
#define FIGHT_H
#include "QSqlDatabase"
#include <QSettings>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QWidget>
#include "table.h"
#include "dialogwithcategory.h"
#include "QCloseEvent"
namespace Ui {
class Fight;
}

class Fight : public QWidget
{
    Q_OBJECT

public:
    explicit Fight( bool,QSettings*,QWidget *parent = nullptr);

    ~Fight();
signals:
    void show_main();
    void recieve_data(double,int,int);
    void open_save_member();
public slots:
    void start_competition(QStringList*, QString, Table*,int);
    void get_count_kata(double*,double,double,double);
    void categories_mod(QJsonDocument*);
    void not_new_cat_mode();
private slots:

    void closeEvent(QCloseEvent *event) override;

    void SaveGeometry();

    void on_categories_currentIndexChanged(const QString &arg1);

    void on_start_loop_clicked();

    void on_end_loop_clicked();

    void on_count_member_clicked();

    void on_view_fighters_clicked(const QModelIndex &index);

    void on_out_member_clicked();

    void on_end_category_clicked();

    void on_categories_activated(int index);

    void on_sorting_box_activated(const QString &arg1);

    void on_categories_box_activated(const QString &arg1);

    void repeat_view_fighters();

    void on_desc_asc_box_activated(const QString &arg1);

    void on_history_member_clicked();

    void on_view_members_clicked(const QModelIndex &index);

    void save_data_count_member();

    void on_end_competition_clicked();

    int check_the_place();




    void on_create_ended_category_clicked();

    void on_load_ended_category_clicked();


private:
    QStandardItemModel *model_fighters;
    QStandardItemModel *history_fighter;
    Table *table;

    QSqlQuery bind_q;
    QSqlQuery sup_query;
    QSqlQuery query;
    QSqlDatabase db;
    QSqlTableModel *model_for_fight;
    QString competition_key; //MAIN KEY
    QString last_name;
    QString first_name;
    QString patronymic_name;
    QString date_of_birthday;
    QString category;
    QModelIndex sel_mem;
    QModelIndex history_member;

    QSettings *Settings;

    int PK;
    int selected_member;
    int index_category;
    bool next_toure = false;
    bool history_fight=false;
    bool asc_desc=true;
    bool second_tour = false;
    QString sorting = "Без сортировки";
    QString categorys1 = "Все";

    QMap<int,QString> causes;
    QStringList list_causes;

    Ui::Fight *ui;
};

#endif // FIGHT_H
