#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "QSqlQuery"
#include <QSettings>
#include <QWidget>
#include "QStandardItemModel"
#include "table.h"
#include "fight.h"
#include "QCloseEvent"
#include "data_dialog.h"
#include "dialogwithcategory.h"
namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;
public:
    explicit Registration(QSettings*,bool,Fight*,QWidget *parent = nullptr);
    ~Registration();

public slots:
    void get_data_competition(QDate*);

private slots:
    void on_load_template_clicked();

    void on_save_template_clicked();

    void on_delete_category_clicked();

    void on_delete_all_category_clicked();

    void on_add_category_clicked();

    void on_kval_dan_clicked();

    void on_kval_ku_clicked();

    void on_gender_M_clicked();

    void on_gender_J_clicked();

    void on_load_members_clicked();

    void on_generate_table_clicked();

    void on_save_data_clicked();

    void on_push_category_to_members_clicked();

    void on_step_01_clicked();

    void on_step_025_clicked();

    void on_step_05_clicked();

    void on_step_1_clicked();

    void on_start_competition_clicked();

    void repeat_data();

    void on_sorting_box_activated(const QString &arg1);

    void on_categories_box_activated(const QString &arg1);

    void on_asc_desc_box_activated(const QString &arg1);

    void get_open_not_end_comp(QString);

    void on_get_competiton_data_clicked();

    void on_add_judge_clicked();

    void on_type_kval_judge_KU_clicked();

    void on_type_kval_judge_DAN_clicked();

    void repeat_judges();

    void on_add_crew_judges_clicked();

    void on_delete_judge_clicked();

    void on_change_position_crew_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_crew_box_activated(const QString &arg1);

    void on_desc_asc_box_activated(const QString &arg1);

    void on_delete_this_member_clicked();

    void on_add_custom_member_clicked();

    void on_gender_M_member_clicked();

    void on_gender_J_member_clicked();

    void on_KU_member_clicked();

    void on_Dan_member_clicked();

    void on_create_category_clicked();

    void check_out_members();

    void on_push_category_to_tatami_clicked();

    void set_enabled_to_push_cat_to_tatami();

    void on_teams_box_activated(const QString &arg1);

    void repeat_teams_box();

    void SaveGeometry();
signals:
    void recieve_data(double ,int , int );
    void go_to_competition(QStringList*, QString, Table*,int);
    void open_save_member();
    void get_open_main();

private:
    Ui::Registration *ui;

    QSqlTableModel *model_for_judges;
    QSqlTableModel *model_for_all_members;
    QSqlQuery query;
    QSqlDatabase db;
    QStandardItemModel *model_for_categorys;
    QStandardItemModel *model_loading_judges;
    QStandardItemModel* model;

    QSettings *Settings;

    QString teams="Все команды";
    QString categorys1="Бригада";
    QString judges_type_kval;
    QString gender;
    QString kvalifications;
    QStringList all_categorys;
    QString sorting_box="Без сортировки";
    QString categories_box="Все";
    QString sorting="Без сортировки";
    QString kval_member ="";
    QString gender_member = "";
    QStringList positions;
    bool asc_desc2 = true;
    bool asc_desc=true;
    bool whos_load = false;
    bool was_started = false;


    int PK;
    QString judges_key;             //JUDGES_KEY
    QString competition_key;   //MAIN KEY

    int from_le=-1;
    int to_le=-1;
    int end_rows;
    double step = 0.0;
    bool desc_asc=true;
    bool was_generate = false;
    bool all_members_with_category = false;


    Data_dialog *dialog;
    Table *table;
    Fight *fight;
};

#endif // REGISTRATION_H
