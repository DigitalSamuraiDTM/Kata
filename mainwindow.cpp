#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QSqlError"
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonArray>
#include "QJsonObject"
#include <QJsonDocument>
#include <QMessageBox>
#include "QAxObject"
#include "QCryptographicHash"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QSettings Settings_system_cpu("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", QSettings::NativeFormat);
//    QString name_CPU = Settings_system_cpu.value("ProcessorNameString", "error").toString();
//    if (name_CPU=="error")
//    {
//        QMessageBox::critical(this,"ошибка","Ошибка идентификации приложения \n Код ошибки: 1");
//        this->close();
//        return;
//    }
//    QSettings name_motherBoard("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\BIOS", QSettings::NativeFormat);
//    QString name_mother = name_motherBoard.value("BaseBoardProduct","error").toString();
//    if (name_mother=="error")
//    {
//        QMessageBox::critical(this,"ошибка","Ошибка идентификации приложения \n Код ошибки: 2");
//        this->close();
//        return;
//    }
//    QSettings *check_id = new QSettings("store.ini", QSettings::IniFormat, this);
//    QString hashing_wor = name_CPU+name_mother;
//    QString hash  = QString(QCryptographicHash::hash(hashing_wor.toUtf8(),QCryptographicHash::Sha3_512).toHex());



//        QString hash_dop = check_id->value("Smile").toString();
//        if (hash != hash_dop)

//        {
//            QMessageBox::critical(this, "ошибка", "Ошибка идентификации приложения \n Код ошибки: 3");
    //         this->close();
//            return;
//        }


    ui->setupUi(this);
    Settings = new QSettings("settings.ini",QSettings::IniFormat,this);
    Settings->beginGroup("Geometry");
    setGeometry(Settings->value("GeometryMain").toRect());
    Settings->endGroup();
    main_window = this;
    QPixmap myPix("logo.png");
    ui->pict->setPixmap(myPix);

    Settings->beginGroup("Font");
    int font = Settings->value("Size",12).toInt();
    Settings->endGroup();
    QApplication::setFont(QFont("Calibri",font));

    check_count_comp();

    //QMessageBox::information(this,"пробная версия","Добро пожаловать в пробную версию\n Присутствуют ограничения на вводимость участников в размере 10");


}

MainWindow::~MainWindow()
{
    SaveGeometry();
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    fight = new Fight(false,Settings);
        connect(fight, SIGNAL(show_main()), this, SLOT(show_main()));
        new_competition=true;
        registr = new Registration(Settings,new_competition,fight);
        connect(registr, SIGNAL(get_open_main()), this, SLOT(show_main()));
        this->close();
        registr->show();

}

void MainWindow::on_select_not_end_comp_clicked()
{

    QStringList not_end_comp;
    query.exec("SELECT НазваниеСоревнований FROM competitions WHERE end_competition=false");
    while (query.next())
    {
        not_end_comp.append(query.value(0).toString());
    }
    if (not_end_comp.isEmpty())
    {
        QMessageBox::information(this,"Незаконченые мероприятия","Незаконченых мероприятий нет");
        return;
    }
    bool ok;
    QString name_comp = QInputDialog::getItem(this,"Выберите незаконченое мероприятие","Незаконченые мероприятия",not_end_comp,0,false,&ok);
   if (!ok)
   {
       return;
   }
   fight = new Fight(false,Settings);
   new_competition=false;
   registr = new Registration(Settings,new_competition,fight);
  connect(registr, SIGNAL(get_open_main()), this, SLOT(show_main()));
  connect(this, SIGNAL(open_not_end_comp(QString)), registr, SLOT(get_open_not_end_comp(QString)));
   emit open_not_end_comp(name_comp);
   this->close();
   registr->showMaximized();
}

void MainWindow::show_main()
{
    this->show();
    check_count_comp();
}

void MainWindow::repeat_fonts()
{
    Settings->beginGroup("Font");
    ui->categories_mode->setFont(QFont("Calibri",Settings->value("Size").toInt()));
    ui->ended_compettition->setFont(QFont("Calibri",Settings->value("Size").toInt()));
    ui->go_to_options->setFont(QFont("Calibri",Settings->value("Size").toInt()));
    ui->pushButton_2->setFont(QFont("Calibri",Settings->value("Size").toInt()));
    ui->select_not_end_comp->setFont(QFont("Calibri",Settings->value("Size").toInt()));
    Settings->endGroup();
}

void MainWindow::on_ended_compettition_clicked()
{
    QStringList not_end_comp;
    query.exec("SELECT НазваниеСоревнований FROM competitions WHERE end_competition=true");
    while (query.next())
    {
        not_end_comp.append(query.value(0).toString());
    }
    if (not_end_comp.isEmpty())
    {
        QMessageBox::information(this,"Законченые мероприятия","Законченых мероприятий нет");
        return;
    }
    bool ok;
    QString name_comp = QInputDialog::getItem(this,"Выберите проведенное мероприятие","Проведенные мероприятия",not_end_comp,0,false,&ok);
   if (!ok)
   {
       return;
   }
    end = new ended_competition();
    connect(this, SIGNAL(open_ended_comp(QString,QSettings*)), end, SLOT(get_name_comp(QString, QSettings*)));
    connect(end, SIGNAL(get_show_main()), this, SLOT(show_main()));
    emit open_ended_comp(name_comp, Settings);
    this->close();
    end->show();
}

void MainWindow::on_go_to_options_clicked()
{
    options_table = new Options;
    connect(this,SIGNAL(push_options(QSettings*)), options_table, SLOT(get_options(QSettings*)));
    connect(options_table, SIGNAL(get_open_main()), this, SLOT(show_main()));
    connect(options_table, SIGNAL(repeat_font()),this,SLOT(repeat_fonts()));
    emit push_options(Settings);
    this->close();
    options_table->show();
}

void MainWindow::check_count_comp()
{

    query.prepare("SELECT COUNT(*) FROM competitions WHERE end_competition=:end");
    query.bindValue(":end",false);
    query.exec();
    int c=0;
    while(query.next())
    {
        c = query.value(0).toInt();
    }
    if (c>0)
    {
        ui->go_to_options->setEnabled(false);
    }else{
        ui->go_to_options->setEnabled(true);
    }
}

void MainWindow::on_categories_mode_clicked()
{
    query.exec("SELECT Фамилия FROM categories_mode LIMIT 1");

    if (query.first())
    {
        fight = new Fight(true,Settings);
        connect(this, SIGNAL(categories_mode()), fight, SLOT(not_new_cat_mode()));
        emit categories_mode();
        this->close();
        return;
    }
    QString root;
    root = QFileDialog::getOpenFileName(this,"Выберите Категории", "","json (*.json)");
if (root==""){
    return;
}
QFile File;
File.setFileName(root);
File.open(QIODevice::ReadOnly|QFile::Text);
QJsonDocument doc;
if (File.isOpen()){
    doc = QJsonDocument::fromJson(QByteArray(File.readAll()));
} else{
    return;
}
File.close();

QString checking = doc.object().value("WHAT_THIS").toString();

if (checking !="ITSME")
{
    QMessageBox::critical(this,"Не тот файл?","Программа заметила, что вы загружаете не тот файл");
    return;
}
QString opened = doc.object().value("WAS_OPENED").toString();
if (opened == "TRUE")
{
    QMessageBox::critical(this,"Не тот файл","Этот файл уже был загружен в программу");
    return;
} else if (opened=="FALSE") {

    QJsonObject copy = doc.object();
    copy.remove("WAS_OPENED");


    copy.insert("WAS_OPENED","TRUE");

    QFileInfo info(root);
    QDir::setCurrent(info.path());

    QFile Json_file(root);

    if(!Json_file.open(QIODevice::WriteOnly))
    {
        return;
    }

    Json_file.write(QJsonDocument(copy).toJson(QJsonDocument::Indented));
    Json_file.close();
}
fight = new Fight(true,Settings);
connect(this, SIGNAL(open_categories_mod(QJsonDocument*)), fight, SLOT(categories_mod(QJsonDocument*)));
connect(fight, SIGNAL(show_main()), this, SLOT(show_main()));
emit open_categories_mod(&doc);
this->close();
}

void MainWindow::SaveGeometry()
{
    Settings->beginGroup("Geometry");
    Settings->setValue("GeometryMain",geometry());
    Settings->endGroup();
}

void MainWindow::on_open_instructions_clicked()
{
    QStringList list = {"Инструкция версия 1","Инструкция версия 2","Схема версия 1","Схема версия 2"};
    QString out = QInputDialog::getItem(this,"Что вы хотите открыть?","Инструкции и схемы",list);
    if (out=="Инструкция версия 1"){
        system("start Instructions_V1.pdf");
    } else if (out == "Инструкция версия 2"){
        system("start Instructions_V2.pdf");
    } else if (out=="Схема версия 1"){
        system("start Chema_V1.pdf");
    } else if (out=="Схема версия 2") {
        system("start Chema_V2.pdf");
    } else{

    }
}

void MainWindow::on_delete_not_ended_comp_clicked()
{
    QStringList not_end_comp;
    query.exec("SELECT НазваниеСоревнований FROM competitions WHERE end_competition=false");
    while (query.next())
    {
        not_end_comp.append(query.value(0).toString());
    }
    if (not_end_comp.isEmpty())
    {
        QMessageBox::information(this,"Незаконченые мероприятия","Незаконченых мероприятий нет");
        return;
    }
    bool ok;
    QString name_comp = QInputDialog::getItem(this,"Выберите незаконченное мероприятие","Мероприятия",not_end_comp,0,false,&ok);
   if (!ok)
   {
       return;
   }
   query.prepare("SELECT rowid FROM competitions WHERE НазваниеСоревнований=:name");
   query.bindValue(":name",name_comp);
   query.exec();
   int id = -1;
   while(query.next())
   {
       id = query.value(0).toInt();
   }
   qDebug()<<id;
   query.prepare("DELETE FROM competitions WHERE НазваниеСоревнований=:name");
   query.bindValue(":name",name_comp);
   query.exec();
   query.clear();
   query.exec("DROP TABLE competition_"+QString::number(id));
   query.clear();
   query.exec("DROP TABLE judges_"+QString::number(id));
}
