#include "mylabel.h"

MyLabel::MyLabel(QString letter,QWidget *parent) : QLabel(parent)
{
    harf = letter;
    setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px;");
}

