#ifndef OPTIONS_H
#define OPTIONS_H

#include <QSettings>
#include <QWidget>
#include "QStandardItemModel"
#include "QCloseEvent"
namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent* event) override;

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();
signals:
    void get_open_main();
    void repeat_font();
private slots:
    void get_options(QSettings*);

    void on_load_template_2_clicked();

    void on_save_template_2_clicked();

    void on_delete_category_2_clicked();

    void on_delete_all_category_2_clicked();

    void on_create_category_2_clicked();

    void on_gender_M_2_clicked();

    void on_gender_J_2_clicked();

    void on_kval_dan_2_clicked();

    void on_kval_ku_2_clicked();

    void on_add_cause_clicked();

    void on_delete_cause_clicked();

    void on_add_position_clicked();

    void on_delete_position_clicked();

    void on_FontSize_SpinBox_valueChanged(int arg1);

private:
    Ui::Options *ui;
    QString gender;
    QString kvalifications;
    QSettings *Settings;
    QStandardItemModel *model_for_categorys;
    QStandardItemModel *model_causes;
    QStandardItemModel *model_positions;
};

#endif // OPTIONS_H
