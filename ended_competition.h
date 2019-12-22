#ifndef ENDED_COMPETITION_H
#define ENDED_COMPETITION_H

#include <QSettings>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QWidget>
#include "QCloseEvent"

namespace Ui {
class ended_competition;
}

class ended_competition : public QWidget
{
    Q_OBJECT

signals:
    void get_show_main();
protected:
    void closeEvent(QCloseEvent* event);

public slots:
    void get_name_comp(QString,QSettings*);

private slots:
    void repeat_members();

    void repeat_judges();
    void on_categorys_box_activated(const QString &arg1);

    void on_sorting_mem_box_activated(const QString &arg1);

    void on_asc_desc_mem_box_activated(const QString &arg1);

    void on_history_member_clicked();

    void on_members_view_clicked(const QModelIndex &index);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_asc_desc_judge_activated(const QString &arg1);

    void on_generate_out_judges_clicked();

    void on_generate_out_members_clicked();

    void on_generate_all_members_clicked();

    void on_DELETE_clicked();

    void on_catgegories_out_clicked();

public:
    explicit ended_competition(QWidget *parent = nullptr);
    ~ended_competition();

private:
    Ui::ended_competition *ui;
    QSqlQuery query;
    QList<int> imu;
    QString name_c;
    QString data_c;
    QString members_key;
    QString judges_key;
    QString place_c;
    QStringList main_j_c;
    QStringList oldest_j_c;
    QStringList main_s_c;
    QStringList deputy_m_j_c;
    QString categorys2="Бригада";
    QString sorting2="Без сортировки";
    bool asc_desc2=true;
    int number_s_c;
    int number_c_c;
    bool history_fight=false;
    QModelIndex history_member;
    QString subjects_c;
    QString citys_c;
    QSqlTableModel* members_model;
    QSqlTableModel* judges_model;
    QSqlDatabase db;
    QStringList all_categorys;
    QStandardItemModel *history_fighter;
    QStandardItemModel *categorys_model;
    int judges_count;
    int members_count;
    QString categorys1="Все";
    QString sorting="Без сортировки";
    bool asc_desc=true;
    QSettings *Settings;
    QString comp_name;
    QStringList poses;
};



#endif // ENDED_COMPETITION_H
