#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSqlQuery"
#include "registration.h"
#include "fight.h"
#include "ended_competition.h"
#include "options.h"
#include "QSettings"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlQuery query;

signals:
    void open_not_end_comp(QString);
    void open_ended_comp(QString, QSettings*);
    void push_options(QSettings*);
    void open_categories_mod(QJsonDocument*);
    void categories_mode();
public slots:
    void show_main();
    void repeat_fonts();
private slots:
    void on_pushButton_2_clicked();

    void on_select_not_end_comp_clicked();

    void on_ended_compettition_clicked();

    void on_go_to_options_clicked();

    void check_count_comp();

    void on_categories_mode_clicked();

    void SaveGeometry();
    void on_open_instructions_clicked();

    void on_delete_not_ended_comp_clicked();

private:
    MainWindow *main_window;
    Ui::MainWindow *ui;
    Fight *fight;
    Options *options_table;
    Registration *registr;
    ended_competition *end;
    bool new_competition=false;
    QSettings *Settings;
};

#endif // MAINWINDOW_H
