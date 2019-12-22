#include "mainwindow.h"
#include <QApplication>
#include "QtSql"
#include "QMessageBox"
#include "QSqlQuery"
#include "QErrorMessage"
#include "QSettings"
int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("SannariumDTM");
    QApplication::setApplicationName("Kata");
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion"); //устанавливаем основной стиль Fusion
    QSqlDatabase db;//создали переменную базы данных
    db = QSqlDatabase::addDatabase("QSQLITE"); //вызываем функцию добавления типа бд
    db.setDatabaseName("data.db");//создаем бд
    db.open(); //открываем бд
    if (!db.isOpen()){
        QMessageBox::warning(nullptr,"База данных", "Что-то пошло не так \n Нет подключения к базе данных");

    }

    MainWindow w;
    w.show();
    a.setWindowIcon(QIcon("main.ico"));

    return a.exec();
}

//ВОЗРАСТ В JSON НЕ ПРИНИМАЕТ
//ИНСТРУКЦИЯ
