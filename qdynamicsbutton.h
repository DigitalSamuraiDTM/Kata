#ifndef QDYNAMICS_H
#define QDYNAMICS_H
#include <QPushButton> //подключаем стандартную кнопку
class QdynamicsButton : public QPushButton //класс динамической кнопки наследованный от обычной кнопки
{
    Q_OBJECT
public: //конструктор класса
    explicit QdynamicsButton(double,QWidget *parent=nullptr); //Неконвертирующаяся (explicit) кнопка, чьим родителем является  Qwidget
    ~QdynamicsButton();
    static double resID; //статическая переменная
    double getID(); //функция взятия id у кнопки
public slots:
    void down_to_zero(double min);
private:
    double plus_id=0.0;
    double buttonID=0.0; //приватная переменная id кнопки



};
#endif // QDYNAMICS_H
