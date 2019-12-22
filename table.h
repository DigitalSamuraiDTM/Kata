#ifndef TABLE_H
#define TABLE_H
#include "qdynamicsbutton.h"
#include <QWidget>
#include "QDialog"
#include "QSettings"
#include "QCloseEvent"
namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();

    Ui::Table *ui;
signals:
    void push_count_kata(double*,double,double,double);
public slots:
    void get_data(double step_pos, int start_pos, int end_pos); //получаем данные
    void open_count();

private slots:

    void closeEvent(QCloseEvent *event) override;
    void on_count_button_2_clicked();

    void on_break_button_2_clicked();

    void on_Save_result_2_clicked();

    void judge_1_baton();
    void judge_2_baton();
    void judge_3_baton();
    void judge_4_baton();
    void judge_5_baton();

private:
    QSettings *Settings;
    QdynamicsButton *qdynamicsbutton; //указатель на динамические кнопки
    double judge_1=0.0;
    double judge_2=0.0; //все наши судьи
    double judge_3=0.0;
    double judge_4=0.0;
    double judge_5=0.0;
    double all_judge[5];
    double middle_ball;
    double max_ball;
    double min_ball;
};

#endif // TABLE_H
