#ifndef DIALOGWITHCATEGORY_H
#define DIALOGWITHCATEGORY_H

#include <QDialog>
#include <QSettings>
#include <QSqlQuery>
#include <QStandardItemModel>

namespace Ui {
class DialogWithCategory;
}

class DialogWithCategory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWithCategory(QString,QWidget *parent = nullptr);
    ~DialogWithCategory();

    QStandardItemModel* return_model();
private slots:
    void on_to_other_tatami_clicked();

    void on_to_main_tatami_clicked();


private:
    Ui::DialogWithCategory *ui;

    QSettings *Settings;
    QStandardItemModel *model_main_tatami;
    QStandardItemModel *model_other_tatami;
    QSqlQuery query;
};

#endif // DIALOGWITHCATEGORY_H
