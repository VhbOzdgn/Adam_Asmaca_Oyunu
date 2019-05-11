#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/eulerpi/Belgeler/QT/Adam_Asmaca_Oyunu/kelimeler.db");
    if(!db.open()){
        QMessageBox::critical(this,"ERROR",db.lastError().text());
    }
    query = new QSqlQuery(db);
    model = new QSqlQueryModel();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    verileriGoster();
    labelList.push_back(ui->label1);
    labelList.push_back(ui->label2);
    labelList.push_back(ui->label3);
    labelList.push_back(ui->label4);
    labelList.push_back(ui->label5);
    labelList.push_back(ui->label6);
    labelList.push_back(ui->label7);
    labelList.push_back(ui->label8);
    labelList.push_back(ui->label9);
    labelList.push_back(ui->label10);
    for(int i = 0; i < labelList.length(); i++){
        labelList[i]->setVisible(false);
    }
    ui->pushButtonTahmin->setEnabled(false);
    ui->lineEditHarf->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::verileriGoster()
{
    if(!query->exec("SELECT * FROM kelime_tablosu")){
        QMessageBox::critical(this,"ERROR",query->lastError().text());
    }
    model->setQuery(*query);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(1,122);
}



void MainWindow::Sifirla()
{
    X = 300; indis = 0; sayac = 0;
    for(int i = 0; i < labelList.length(); i++){
        labelList[i]->setVisible(false);
    }

    for(int i = 0; i < mylabList.length(); i++){
        delete mylabList[i];
    }
    mylabList.clear();
    harfList.clear();
    ui->listWidget->clear();
    ui->lineEditHarf->clear();
    ui->pushButtonTahmin->setEnabled(false);
    ui->lineEditHarf->setEnabled(false);
    ui->pushButtonBasla->setEnabled(true);
}

bool MainWindow::birKelimeMi(QString kelime)
{
    if(kelime == ""){
        return false;
    }
    QStringList kelimeler = kelime.split(' ');
    if(kelimeler.length() == 1){
        return true;
    }
    else {
        return false;
    }
}




void MainWindow::on_pushButtonEkle_pressed()
{
    if(!birKelimeMi(ui->lineEdit_kelime->text())){
        QMessageBox::critical(this,"ERROR","Bir kelime girebilirsiniz!\n"
                                           "Boşluk karakteri olmadığından emin olun!");
        return;
    }
    query->prepare("INSERT INTO kelime_tablosu(kelime)VALUES(?)");
    query->addBindValue(ui->lineEdit_kelime->text());
    if(!query->exec()){
        QMessageBox::critical(this,"ERROR",query->lastError().text());
    }
    ui->lineEdit_kelime->clear();
    verileriGoster();
}




void MainWindow::on_tableView_pressed(const QModelIndex &index)
{
    kelime_no = model->index(index.row(),0).data().toString();
    ui->lineEdit_kelime->setText(model->index(index.row(),1).data().toString());
}





void MainWindow::on_pushButtonDegistir_pressed()
{
    if(!birKelimeMi(ui->lineEdit_kelime->text())){
        QMessageBox::critical(this,"ERROR","Bir kelime girebilirsiniz!\n"
                                           "Boşluk karakteri olmadığından emin olun!");
        return;
    }
    query->prepare("UPDATE kelime_tablosu SET kelime = ? WHERE kelime_no = ?");
    query->addBindValue(ui->lineEdit_kelime->text());
    query->addBindValue(kelime_no);
    if(!query->exec()){
        QMessageBox::critical(this,"ERROR",query->lastError().text());
    }
    ui->lineEdit_kelime->clear();
    verileriGoster();
}




void MainWindow::on_pushButtonSil_pressed()
{
    QMessageBox::StandardButton cevap;
    cevap = QMessageBox::question(this, "Uyarı!", kelime_no + " nolu kelimeyi silmek istiyor musunuz?",
                                  QMessageBox::Yes|QMessageBox::No);
    if(cevap == QMessageBox::Yes){
        if(!query->exec("DELETE FROM kelime_tablosu WHERE kelime_no = " + kelime_no)){
            QMessageBox::critical(this,"ERROR",query->lastError().text());
        }
        verileriGoster();
        ui->lineEdit_kelime->clear();
        kelime_no = "";
    }

}





void MainWindow::on_pushButtonBasla_pressed()
{
    QString kelime = model->index(rand()%model->rowCount(),1).data().toString();
    for(int i = 0; i < kelime.length(); i++){
        MyLabel *mylabel = new MyLabel(kelime.at(i),this);
        mylabel->setGeometry(X,430,10,15);
        mylabel->show();
        X += 14;
        mylabList.push_back(mylabel);

    }
    ui->pushButtonTahmin->setEnabled(true);
    ui->lineEditHarf->setEnabled(true);
    ui->lineEditHarf->setFocus();
    ui->pushButtonBasla->setEnabled(false);
}






void MainWindow::on_pushButtonTahmin_pressed()
{
    ui->lineEditHarf->setFocus();
    kontrol = true;
    if(ui->lineEditHarf->text().length() != 1){
        QMessageBox::information(this,"Uyarı","Bir harf girmelisiniz!");
        ui->lineEditHarf->clear();
        return;
    }

    if(harfList.contains(ui->lineEditHarf->text())){
        QMessageBox::information(this,"Bilgi","Bu harfi kullandınız...");
        ui->lineEditHarf->clear();
        return;
    }
    for(int i = 0; i < mylabList.length(); i++){
        if(mylabList[i]->harf == ui->lineEditHarf->text()){
            mylabList[i]->setText(mylabList[i]->harf);
            mylabList[i]->setStyleSheet("");
            kontrol = false;
            sayac++;
            if(sayac == mylabList.length()){
                QMessageBox::information(this,"Bilgi","Tebrikler kazandınız...");
                Sifirla();
                return;
            }
        }
     }
     if(kontrol){
        ui->listWidget->addItem(ui->lineEditHarf->text());
        labelList[indis]->setVisible(true);
        indis++;
        if(indis == labelList.length()){
            QMessageBox::information(this,"Bilgi","Oyun Bitti...");
            Sifirla();
            return;
        }
     }
    harfList << ui->lineEditHarf->text();
    ui->lineEditHarf->clear();

}
