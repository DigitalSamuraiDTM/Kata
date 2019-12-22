#include "qdynamicsbutton.h"

QdynamicsButton::QdynamicsButton(double plus_id,QWidget *parent): //слева область видимости :: уточняемое имя
    QPushButton(parent) //конструктор
{
    setStyleSheet("QdynamicsButton{font-size: 18px;"                      //накидываем css стиль
                           "background-color: #e2e2e2;"
                           "border:1px solid #afafaf}"
                           "QdynamicsButton:hover{background-color:#FEFEEC;"
                           "border-color: #FFE900;}"
                           "QdynamicsButton:pressed{background-color:#F8F8A0;"
                           "border-color: #FFE900;};");
    buttonID=resID; //присваеваем id  ктекущей кнопки
    resID-=plus_id; //уменьшаем id
}

QdynamicsButton::~QdynamicsButton()
{

}

double QdynamicsButton::getID() //возврат id кнопки
{
    return buttonID;
}

double QdynamicsButton::resID=0.0; //обозначаем стартовый id

void QdynamicsButton::down_to_zero(double max) //функция возвращения id кнопки в нужное состояние
{
    resID=max;
}

