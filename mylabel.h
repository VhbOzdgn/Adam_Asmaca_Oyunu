#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPainter>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QString,QWidget *parent = nullptr);
    QString harf = "";

signals:

public slots:
};

#endif // MYLABEL_H
