#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include "mylabel.h"
#include <QSet>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void verileriGoster();

    void Sifirla();

    bool birKelimeMi(QString);

private slots:
    void on_pushButtonEkle_pressed();

    void on_tableView_pressed(const QModelIndex &index);

    void on_pushButtonDegistir_pressed();

    void on_pushButtonSil_pressed();

    void on_pushButtonBasla_pressed();

    void on_pushButtonTahmin_pressed();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQueryModel *model;
    QString kelime_no = "";
    int X = 300, indis = 0, sayac = 0;
    QList <QLabel*> labelList;
    QList <MyLabel*> mylabList;
    QSet<QString> harfList;
    bool kontrol = true;
};

#endif // MAINWINDOW_H
