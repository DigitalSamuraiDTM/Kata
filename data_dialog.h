#ifndef DATA_DIALOG_H
#define DATA_DIALOG_H

#include <QDialog>
#include <QSettings>


namespace Ui {
class Data_dialog;
}

class Data_dialog : public QDialog
{
    Q_OBJECT
signals:
    void push_data(QDate*);
public:
    explicit Data_dialog(QWidget *parent = nullptr);
    ~Data_dialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    QSettings *Settings;
    Ui::Data_dialog *ui;
};

#endif // DATA_DIALOG_H
